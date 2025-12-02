/**
 * @file melodies.h
 * @brief RTTTL melodies and sound definitions for SBot
 * @version 1.0.0
 * 
 * RTTTL (Ring Tone Text Transfer Language) format melodies
 * for playback through the piezo buzzer.
 */

#ifndef SBOT_MELODIES_H
#define SBOT_MELODIES_H

#include <avr/pgmspace.h>

// =============================================================================
// RTTTL MELODIES (Stored in PROGMEM to save RAM)
// =============================================================================

/**
 * @brief "Della" melody - Main celebration tune
 */
const char MELODY_DELLA[] PROGMEM = 
    "Della:d=8,o=5,b=125:b4,c,d,4d,p,4g,4f#,4g,4a,b,1g,p,p,p,f#,g,4d6.,g,1g,"
    "p,p,g,g,2g,p,a,g,1f#,p,4b4.,p,b4,a4,g4,2d,p,4g,4a,4c6.,b,2b.,p,p,4d6,4c6,"
    "b,c6,b,4g,4d.,p,a,g,f#,e,4f#,p,4g,p,4g,p,1g";

/**
 * @brief Startup melody - Short happy tune
 */
const char MELODY_STARTUP[] PROGMEM = 
    "Startup:d=16,o=5,b=180:c,e,g,8c6";

/**
 * @brief Success melody - Achievement sound
 */
const char MELODY_SUCCESS[] PROGMEM = 
    "Success:d=8,o=5,b=200:c,e,g,4c6";

/**
 * @brief Error melody - Warning sound
 */
const char MELODY_ERROR[] PROGMEM = 
    "Error:d=8,o=4,b=120:c,p,c,p,c";

/**
 * @brief Alert melody - Attention getter
 */
const char MELODY_ALERT[] PROGMEM = 
    "Alert:d=16,o=5,b=200:g,p,g,p,g,p,4g";

/**
 * @brief Happy melody - Short cheerful tune
 */
const char MELODY_HAPPY[] PROGMEM = 
    "Happy:d=8,o=5,b=160:c,d,e,f,4g,4g,a,a,a,a,4g";

/**
 * @brief Sleep melody - Calming tune
 */
const char MELODY_SLEEP[] PROGMEM = 
    "Sleep:d=4,o=4,b=80:c,e,g,2c5";

// =============================================================================
// TONE FREQUENCIES (for simple beeps)
// =============================================================================

namespace Tones {
    const uint16_t NOTE_C4  = 262;
    const uint16_t NOTE_D4  = 294;
    const uint16_t NOTE_E4  = 330;
    const uint16_t NOTE_F4  = 349;
    const uint16_t NOTE_G4  = 392;
    const uint16_t NOTE_A4  = 440;
    const uint16_t NOTE_B4  = 494;
    const uint16_t NOTE_C5  = 523;
    const uint16_t NOTE_D5  = 587;
    const uint16_t NOTE_E5  = 659;
    const uint16_t NOTE_F5  = 698;
    const uint16_t NOTE_G5  = 784;
    const uint16_t NOTE_A5  = 880;
    const uint16_t NOTE_B5  = 988;
    const uint16_t NOTE_C6  = 1047;
}

#endif // SBOT_MELODIES_H
