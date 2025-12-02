/**
 * @file colors.h
 * @brief Color definitions and presets for SBot LED system
 * @version 1.0.0
 */

#ifndef SBOT_COLORS_H
#define SBOT_COLORS_H

#include <stdint.h>

// =============================================================================
// COLOR STRUCTURE
// =============================================================================

/**
 * @brief RGB color structure
 */
struct RGBColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    
    RGBColor(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0)
        : r(red), g(green), b(blue) {}
};

// =============================================================================
// PRESET COLORS
// =============================================================================

namespace Colors {
    // Basic colors
    const RGBColor BLACK(0, 0, 0);
    const RGBColor WHITE(255, 255, 255);
    const RGBColor RED(255, 0, 0);
    const RGBColor GREEN(0, 255, 0);
    const RGBColor BLUE(0, 0, 255);
    
    // Extended colors
    const RGBColor MAGENTA(255, 0, 255);
    const RGBColor MAGENTA_DIM(64, 0, 64);      // 25% magenta for chill state
    const RGBColor CYAN(0, 255, 255);
    const RGBColor YELLOW(255, 255, 0);
    const RGBColor ORANGE(255, 127, 0);
    const RGBColor PURPLE(128, 0, 128);
    const RGBColor PINK(255, 105, 180);
    
    // SBot mood colors
    const RGBColor MOOD_HAPPY(255, 255, 0);     // Yellow - happy
    const RGBColor MOOD_EXCITED(255, 0, 255);   // Magenta - excited
    const RGBColor MOOD_CALM(64, 0, 64);        // Dim magenta - calm
    const RGBColor MOOD_ALERT(255, 127, 0);     // Orange - alert
    const RGBColor MOOD_ERROR(255, 0, 0);       // Red - error
}

// =============================================================================
// COLOR SEQUENCES FOR ANIMATIONS
// =============================================================================

/**
 * @brief Dope state color sequence
 */
const RGBColor DOPE_SEQUENCE[] = {
    Colors::MAGENTA,    // Start
    Colors::MAGENTA_DIM,// Chill
    Colors::RED,        // Transition
    Colors::ORANGE,     // Transition
    Colors::YELLOW      // End
};
const uint8_t DOPE_SEQUENCE_LENGTH = sizeof(DOPE_SEQUENCE) / sizeof(RGBColor);

/**
 * @brief Startup color sequence (rainbow fade)
 */
const RGBColor STARTUP_SEQUENCE[] = {
    Colors::RED,
    Colors::GREEN,
    Colors::BLUE,
    Colors::WHITE
};
const uint8_t STARTUP_SEQUENCE_LENGTH = sizeof(STARTUP_SEQUENCE) / sizeof(RGBColor);

#endif // SBOT_COLORS_H
