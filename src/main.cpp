#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <Wire.h>

// #include "spritesA.h"  // Old concept
// #include "spritesB.h" // Old concept
#include "sprites/sprites_a.h"

// =============================================
// Default Window
// =============================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =============================================
// Joystick (un solo joystick por ahora)
// =============================================
#define JOY_VRY 34  // vertical axe    (up/down)
#define JOY_VRX 35  // horizontal axe  (left/right)
#define JOY_BTN 32  // joystick button (SW)

// Joystick DEADZONE (0-4095, center ~2048)
#define JOY_DEAD_ZONE 600

// =============================================
// Menu
// =============================================
const char* menuItems[] = {"Juegos", "Scores", "Logros", "Sleep"};
const uint8_t MENU_COUNT = 4;
uint8_t menuIndex = 0;

// =============================================
// Joystick helpers
// =============================================
bool joyUp() { return analogRead(JOY_VRY) < (2048 - JOY_DEAD_ZONE); }
bool joyDown() { return analogRead(JOY_VRY) > (2048 + JOY_DEAD_ZONE); }
bool joyRight() { return analogRead(JOY_VRX) > (2048 + JOY_DEAD_ZONE); }
bool joyBtn() { return digitalRead(JOY_BTN) == LOW; }
