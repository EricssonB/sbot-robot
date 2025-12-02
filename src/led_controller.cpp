/**
 * @file led_controller.cpp
 * @brief Implementation of NeoPixel LED controller for SBot
 * @version 1.0.0
 */

#include "led_controller.h"
#include <Arduino.h>

LEDController::LEDController(uint8_t pin1, uint8_t pin2, uint8_t numPixels)
    : _strip1(numPixels, pin1, NEO_GRB + NEO_KHZ800)
    , _strip2(numPixels, pin2, NEO_GRB + NEO_KHZ800)
    , _numPixels(numPixels)
    , _currentColor(0, 0, 0) {
}

void LEDController::begin() {
    _strip1.begin();
    _strip2.begin();
    _strip1.setBrightness(255);
    _strip2.setBrightness(255);
    off();
    
    DEBUG_PRINTLN(F("LED Controller initialized"));
}

void LEDController::setColor(const RGBColor& color) {
    setColor(color.r, color.g, color.b);
}

void LEDController::setColor(uint8_t r, uint8_t g, uint8_t b) {
    _currentColor = RGBColor(r, g, b);
    
    for (uint8_t i = 0; i < _numPixels; i++) {
        _strip1.setPixelColor(i, _strip1.Color(r, g, b));
        _strip2.setPixelColor(i, _strip2.Color(r, g, b));
    }
    _update();
}

void LEDController::off() {
    setColor(0, 0, 0);
}

void LEDController::fadeIn(const RGBColor& color, uint16_t duration) {
    uint8_t steps = 51;  // 255 / 5
    uint16_t stepDelay = duration / steps;
    
    for (uint16_t i = 0; i <= 255; i += 5) {
        uint8_t r = (color.r * i) / 255;
        uint8_t g = (color.g * i) / 255;
        uint8_t b = (color.b * i) / 255;
        setColor(r, g, b);
        delay(stepDelay);
    }
    
    // Ensure we end exactly on target color
    setColor(color);
}

void LEDController::fadeOut(uint16_t duration) {
    RGBColor startColor = _currentColor;
    uint8_t steps = 51;
    uint16_t stepDelay = duration / steps;
    
    for (int16_t i = 255; i >= 0; i -= 5) {
        uint8_t r = (startColor.r * i) / 255;
        uint8_t g = (startColor.g * i) / 255;
        uint8_t b = (startColor.b * i) / 255;
        setColor(r, g, b);
        delay(stepDelay);
    }
    
    off();
}

void LEDController::crossfade(const RGBColor& from, const RGBColor& to, uint8_t stepDelay) {
    for (uint16_t i = 0; i <= 255; i += 5) {
        uint8_t r = map(i, 0, 255, from.r, to.r);
        uint8_t g = map(i, 0, 255, from.g, to.g);
        uint8_t b = map(i, 0, 255, from.b, to.b);
        setColor(r, g, b);
        delay(stepDelay);
    }
    
    // Ensure we end exactly on target color
    setColor(to);
}

void LEDController::rainbow(uint8_t cycles, uint8_t speed) {
    for (uint8_t c = 0; c < cycles; c++) {
        for (uint16_t hue = 0; hue < 256; hue++) {
            RGBColor color = _wheel(hue);
            setColor(color);
            delay(speed);
        }
    }
}

void LEDController::breathe(const RGBColor& color, uint8_t cycles) {
    for (uint8_t c = 0; c < cycles; c++) {
        // Breathe in
        for (uint16_t i = 0; i <= 255; i += 5) {
            uint8_t r = (color.r * i) / 255;
            uint8_t g = (color.g * i) / 255;
            uint8_t b = (color.b * i) / 255;
            setColor(r, g, b);
            delay(10);
        }
        
        // Breathe out
        for (int16_t i = 255; i >= 0; i -= 5) {
            uint8_t r = (color.r * i) / 255;
            uint8_t g = (color.g * i) / 255;
            uint8_t b = (color.b * i) / 255;
            setColor(r, g, b);
            delay(10);
        }
        
        delay(200);  // Pause between breaths
    }
}

void LEDController::setBrightness(uint8_t brightness) {
    _strip1.setBrightness(brightness);
    _strip2.setBrightness(brightness);
    _update();
}

void LEDController::_update() {
    _strip1.show();
    _strip2.show();
}

RGBColor LEDController::_wheel(uint8_t hue) {
    if (hue < 85) {
        return RGBColor(hue * 3, 255 - hue * 3, 0);
    } else if (hue < 170) {
        hue -= 85;
        return RGBColor(255 - hue * 3, 0, hue * 3);
    } else {
        hue -= 170;
        return RGBColor(0, hue * 3, 255 - hue * 3);
    }
}
