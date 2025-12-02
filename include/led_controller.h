/**
 * @file led_controller.h
 * @brief NeoPixel LED controller for SBot
 * @version 1.0.0
 */

#ifndef SBOT_LED_CONTROLLER_H
#define SBOT_LED_CONTROLLER_H

#include <Adafruit_NeoPixel.h>
#include "colors.h"
#include "config.h"

/**
 * @class LEDController
 * @brief Manages dual NeoPixel LED strips for SBot's arms
 * 
 * Provides methods for solid colors, fading, crossfading,
 * and animated patterns on both LED strips simultaneously.
 */
class LEDController {
public:
    /**
     * @brief Construct LED controller with specified pins
     * @param pin1 Pin for first LED strip (left arm)
     * @param pin2 Pin for second LED strip (right arm)
     * @param numPixels Number of LEDs per strip
     */
    LEDController(uint8_t pin1, uint8_t pin2, uint8_t numPixels);
    
    /**
     * @brief Initialize the LED strips
     */
    void begin();
    
    /**
     * @brief Set all LEDs to a solid color
     * @param color RGB color to set
     */
    void setColor(const RGBColor& color);
    
    /**
     * @brief Set all LEDs using RGB values
     * @param r Red component (0-255)
     * @param g Green component (0-255)
     * @param b Blue component (0-255)
     */
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    
    /**
     * @brief Turn off all LEDs
     */
    void off();
    
    /**
     * @brief Fade from black to a target color
     * @param color Target color
     * @param duration Duration of fade in milliseconds
     */
    void fadeIn(const RGBColor& color, uint16_t duration = 500);
    
    /**
     * @brief Fade from current color to black
     * @param duration Duration of fade in milliseconds
     */
    void fadeOut(uint16_t duration = 500);
    
    /**
     * @brief Smoothly transition between two colors
     * @param from Starting color
     * @param to Ending color
     * @param stepDelay Delay between steps (controls speed)
     */
    void crossfade(const RGBColor& from, const RGBColor& to, uint8_t stepDelay = 10);
    
    /**
     * @brief Rainbow color wheel animation
     * @param cycles Number of complete cycles
     * @param speed Delay between steps
     */
    void rainbow(uint8_t cycles = 1, uint8_t speed = 10);
    
    /**
     * @brief Breathing effect (fade in/out)
     * @param color Color to breathe
     * @param cycles Number of breath cycles
     */
    void breathe(const RGBColor& color, uint8_t cycles = 3);
    
    /**
     * @brief Set individual strip brightness
     * @param brightness Brightness level (0-255)
     */
    void setBrightness(uint8_t brightness);
    
    /**
     * @brief Get current color
     * @return Current RGB color
     */
    RGBColor getCurrentColor() const { return _currentColor; }

private:
    Adafruit_NeoPixel _strip1;
    Adafruit_NeoPixel _strip2;
    uint8_t _numPixels;
    RGBColor _currentColor;
    
    /**
     * @brief Update both strips with current color
     */
    void _update();
    
    /**
     * @brief Convert hue to RGB (for rainbow)
     * @param hue Hue value (0-255)
     * @return RGB color
     */
    RGBColor _wheel(uint8_t hue);
};

#endif // SBOT_LED_CONTROLLER_H
