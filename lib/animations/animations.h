#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>

enum class animType : uint8_t {
    BLINK,
    OPEN,
    IDLE,
    RIGHT,
    LEFT,
    UP,
    DOWN,
    WIDE,
    HUH
};

enum class signType : uint8_t {
    NONE = 0,
    SIGN_QST = 1,
    SIGN_EXL = 2
};

typedef struct amination {
    const unsigned char* const* frames;
    uint8_t frameCount;
    uint16_t frameRate;
    uint8_t width;
    uint8_t height;
} animation;

typedef struct signs {
    const unsigned char* bitmap;
    uint8_t width;
    uint8_t height;
} signs;

class animationPlayer {
   public:
    void begin(Adafruit_SSD1306* display);
    void play(animType type, uint8_t signcoCode = 0, bool restart = true);
    void update();
    void draw(int16_t x, int16_t y, uint16_t color = SSD1306_WHITE);

   private:
    Adafruit_SSD1306* _display = nullptr;
    const animation* _current = nullptr;
    uint8_t _frameIndex = 0;
    unsigned long _lastFrameTime = 0;

    const signs* _currentSign = nullptr;
    const animation* resolveAnim(animType type);
    const signs* resolveSign(uint8_t code);
};
