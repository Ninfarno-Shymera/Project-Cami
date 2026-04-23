#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Configuración de la pantalla
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // El ESP32 no suele usar pin de reset dedicado
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- TUS SPRITES (Convertidos de Krita/image2cpp) ---
// Aquí pones el frame que te pasé antes o los que tú dibujes
const unsigned char fox_frame1[] PROGMEM = {
    0xe0, 0x01, 0x00, 0xfc, 0x07, 0x00, 0x86, 0x0e, 0x00, 0x82, 0x1c, 0x00,
    0x02, 0x3c, 0x00, 0x02, 0xfc, 0x00, 0x02, 0x7c, 0x00, 0x06, 0x7e, 0x00,
    0x0c, 0x3e, 0x00, 0x0c, 0x3e, 0x00, 0x1c, 0x1f, 0x00, 0x3c, 0x1e, 0x00,
    0x3c, 0x0c, 0x00, 0x78, 0x0c, 0x00, 0x78, 0x0c, 0x00, 0xf0, 0x0e, 0x00,
    0xe0, 0x07, 0x00, 0xe0, 0x03, 0x00, 0xc0, 0x01, 0x00, 0x80, 0x00, 0x00};

// Imagina que tienes un segundo frame dibujado
const unsigned char fox_frame2[] PROGMEM = {/* ... datos del frame 2 ... */};

// Array para manejar la animación fácilmente
const unsigned char* animation_idle[] = {fox_frame1, fox_frame2};
int totalFrames = 1;  // Por ahora solo tenemos uno definido arriba
int currentFrame = 0;

// Temporizador para la animación
unsigned long lastTime = 0;
const int frameDuration = 200;  // El zorro cambia cada 200ms

void setup() {
    // Inicializar comunicación serie y pantalla
    Serial.begin(115200);

    // Dirección 0x3C es la más común para estas pantallas
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("No se encontró la pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();
    display.display();
}

void actualizarPantalla() {
    display.clearDisplay();  // Limpiamos el buffer

    // Dibujar el zorro (x, y, datos, ancho, alto, color)
    // El ancho es 21 y alto 20 según el sprite que te pasé
    display.drawBitmap(10, 20, animation_idle[currentFrame], 21, 20, WHITE);

    // Dibujar algo de texto al lado
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(45, 25);
    display.println("Hola! Soy Hina");

    display.display();  // Enviar todo lo dibujado a la pantalla real
}

void loop() {
    unsigned long currentTime = millis();

    // CONTROL DE ANIMACIÓN
    if (currentTime - lastTime >= frameDuration) {
        lastTime = currentTime;

        // Cambiar al siguiente frame
        currentFrame = (currentFrame + 1) % totalFrames;

        // Actualizar la pantalla
        actualizarPantalla();
    }

    // --- AQUÍ PUEDES PONER OTRA LÓGICA ---
    // Ejemplo: leer un sensor, revisar el WiFi, etc.
}
