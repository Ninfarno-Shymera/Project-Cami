#include "animations.h"

// #include "spritesA.h"  // Old concept
// #include "spritesB.h" // Old concept
#include "sprites/sprites_a.h"

static int frame_delay = 500;
static int x = 32;

/* --- Data Animations --- */
const animation animBlink = {blink, 2, frame_delay, x, x};
const animation animOpen = {open, 2, frame_delay, x, x};
const animation animIdle = {idle, 2, frame_delay, x, x};
const animation animRight = {right, 2, frame_delay, x, x};
const animation animLeft = {left, 2, frame_delay, x, x};
const animation animUp = {up, 2, frame_delay, x, x};
const animation animDown = {down, 2, frame_delay, x, x};
const animation animWide = {wide, 2, frame_delay, x, x};
const animation animHuh = {huh, 2, frame_delay, x, x};

// Signs
const signs sign_q{sign_qst, x, x};
const signs sign_e{sign_exl, x, x};

const animation* animationPlayer::resolveAnim(animType type) {
    switch (type) {
        case animType::BLINK:
            return &animBlink;
        case animType::OPEN:
            return &animOpen;
        case animType::IDLE:
            return &animIdle;
        case animType::RIGHT:
            return &animRight;
        case animType::LEFT:
            return &animLeft;
        case animType::UP:
            return &animUp;
        case animType::DOWN:
            return &animDown;
        case animType::WIDE:
            return &animWide;
        case animType::HUH:
            return &animHuh;
        default:
            return &animIdle;
    }
}

const signs* animationPlayer::resolveSign(uint8_t code) {
    switch (code) {
        case 1:
            return &sign_q;
        case 2:
            return &sign_e;
        case 0:
        default:
            return nullptr;
    }
}

void animationPlayer::begin(Adafruit_SSD1306* display) {
    _display = display;
}

void animationPlayer::play(animType type, uint8_t code, bool restart) {
    const animation* anim = resolveAnim(type);

    if (anim != _current || restart) {
        _current = anim;
        _frameIndex = 0;
        _lastFrameTime = millis();
    }

    _currentSign = resolveSign(code);
}

void animationPlayer::update(void) {
    if (!_current) return;
    if (millis() - _lastFrameTime >= _current->frameRate) {
        _frameIndex = (_frameIndex + 1) % _current->frameCount;
        _lastFrameTime = millis();
    }
}

void animationPlayer::draw(int16_t x, int16_t y, uint16_t color) {
    if (!_current || !_display) return;
    _display->drawBitmap(x, y, _current->frames[_frameIndex], _current->width, _current->height, color);

    if (_currentSign) _display->drawBitmap(x + _current->width - 10, y - 10, _currentSign->bitmap, _currentSign->width, _currentSign->height, color);
}
