/**
 * @file PlayRtttl.hpp
 * @brief Simple RTTTL melody player for Arduino
 * @version 1.0.0
 * 
 * RTTTL (Ring Tone Text Transfer Language) is a text format
 * for storing melodies, originally used for Nokia phones.
 */

#ifndef PLAY_RTTTL_HPP
#define PLAY_RTTTL_HPP

#include <Arduino.h>

// Note frequencies (Hz)
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186

// Octave 4 note frequencies for RTTTL parsing
const uint16_t NOTES[] = {
    0,       // p (pause)
    NOTE_C4, // c
    NOTE_CS4,// c#
    NOTE_D4, // d
    NOTE_DS4,// d#
    NOTE_E4, // e
    NOTE_F4, // f
    NOTE_FS4,// f#
    NOTE_G4, // g
    NOTE_GS4,// g#
    NOTE_A4, // a
    NOTE_AS4,// a#
    NOTE_B4  // b
};

/**
 * @brief Play RTTTL melody from PROGMEM (blocking)
 * @param pin Buzzer pin
 * @param melody RTTTL string stored in PROGMEM
 */
inline void playRtttlBlockingPGM(uint8_t pin, const char* melody) {
    // Default values
    uint8_t defaultDuration = 4;
    uint8_t defaultOctave = 6;
    uint16_t bpm = 63;
    
    // Skip name
    while (pgm_read_byte(melody) != ':') melody++;
    melody++; // Skip ':'
    
    // Parse defaults section
    while (pgm_read_byte(melody) != ':') {
        char c = pgm_read_byte(melody);
        
        if (c == 'd' && pgm_read_byte(melody + 1) == '=') {
            melody += 2;
            defaultDuration = 0;
            while (pgm_read_byte(melody) >= '0' && pgm_read_byte(melody) <= '9') {
                defaultDuration = defaultDuration * 10 + (pgm_read_byte(melody) - '0');
                melody++;
            }
        }
        else if (c == 'o' && pgm_read_byte(melody + 1) == '=') {
            melody += 2;
            defaultOctave = pgm_read_byte(melody) - '0';
            melody++;
        }
        else if (c == 'b' && pgm_read_byte(melody + 1) == '=') {
            melody += 2;
            bpm = 0;
            while (pgm_read_byte(melody) >= '0' && pgm_read_byte(melody) <= '9') {
                bpm = bpm * 10 + (pgm_read_byte(melody) - '0');
                melody++;
            }
        }
        else {
            melody++;
        }
    }
    melody++; // Skip ':'
    
    // Calculate whole note duration in ms
    uint32_t wholeNote = (60000UL * 4) / bpm;
    
    // Parse and play notes
    while (pgm_read_byte(melody)) {
        uint8_t duration = 0;
        uint8_t note = 0;
        uint8_t octave = defaultOctave;
        bool dotted = false;
        
        // Skip whitespace and commas
        while (pgm_read_byte(melody) == ' ' || pgm_read_byte(melody) == ',') {
            melody++;
        }
        
        if (!pgm_read_byte(melody)) break;
        
        // Parse duration
        while (pgm_read_byte(melody) >= '0' && pgm_read_byte(melody) <= '9') {
            duration = duration * 10 + (pgm_read_byte(melody) - '0');
            melody++;
        }
        if (duration == 0) duration = defaultDuration;
        
        // Parse note
        char noteChar = pgm_read_byte(melody);
        melody++;
        
        switch (noteChar) {
            case 'p': note = 0; break;
            case 'c': note = 1; break;
            case 'd': note = 3; break;
            case 'e': note = 5; break;
            case 'f': note = 6; break;
            case 'g': note = 8; break;
            case 'a': note = 10; break;
            case 'b': note = 12; break;
            default: continue;
        }
        
        // Check for sharp
        if (pgm_read_byte(melody) == '#') {
            note++;
            melody++;
        }
        
        // Check for dot
        if (pgm_read_byte(melody) == '.') {
            dotted = true;
            melody++;
        }
        
        // Parse octave
        if (pgm_read_byte(melody) >= '0' && pgm_read_byte(melody) <= '9') {
            octave = pgm_read_byte(melody) - '0';
            melody++;
        }
        
        // Check for dot after octave
        if (pgm_read_byte(melody) == '.') {
            dotted = true;
            melody++;
        }
        
        // Calculate note duration
        uint32_t noteDuration = wholeNote / duration;
        if (dotted) {
            noteDuration += noteDuration / 2;
        }
        
        // Calculate frequency
        uint16_t frequency = 0;
        if (note > 0 && note <= 12) {
            frequency = NOTES[note];
            // Adjust for octave (base is octave 4)
            if (octave > 4) {
                frequency <<= (octave - 4);
            } else if (octave < 4) {
                frequency >>= (4 - octave);
            }
        }
        
        // Play note
        if (frequency > 0) {
            tone(pin, frequency, noteDuration * 0.9);
            delay(noteDuration);
        } else {
            delay(noteDuration);
        }
        
        noTone(pin);
    }
}

/**
 * @brief Play RTTTL melody from RAM (blocking)
 * @param pin Buzzer pin
 * @param melody RTTTL string in RAM
 */
inline void playRtttlBlocking(uint8_t pin, const char* melody) {
    // For RAM-based strings, we need a different implementation
    // This is a simplified version
    
    uint8_t defaultDuration = 4;
    uint8_t defaultOctave = 6;
    uint16_t bpm = 63;
    
    // Skip name
    while (*melody && *melody != ':') melody++;
    if (*melody) melody++;
    
    // Parse defaults
    while (*melody && *melody != ':') {
        if (*melody == 'd' && *(melody + 1) == '=') {
            melody += 2;
            defaultDuration = atoi(melody);
            while (*melody >= '0' && *melody <= '9') melody++;
        }
        else if (*melody == 'o' && *(melody + 1) == '=') {
            melody += 2;
            defaultOctave = *melody - '0';
            melody++;
        }
        else if (*melody == 'b' && *(melody + 1) == '=') {
            melody += 2;
            bpm = atoi(melody);
            while (*melody >= '0' && *melody <= '9') melody++;
        }
        else {
            melody++;
        }
    }
    if (*melody) melody++;
    
    uint32_t wholeNote = (60000UL * 4) / bpm;
    
    while (*melody) {
        uint8_t duration = 0;
        uint8_t note = 0;
        uint8_t octave = defaultOctave;
        bool dotted = false;
        
        while (*melody == ' ' || *melody == ',') melody++;
        if (!*melody) break;
        
        while (*melody >= '0' && *melody <= '9') {
            duration = duration * 10 + (*melody - '0');
            melody++;
        }
        if (duration == 0) duration = defaultDuration;
        
        char noteChar = *melody++;
        switch (noteChar) {
            case 'p': note = 0; break;
            case 'c': note = 1; break;
            case 'd': note = 3; break;
            case 'e': note = 5; break;
            case 'f': note = 6; break;
            case 'g': note = 8; break;
            case 'a': note = 10; break;
            case 'b': note = 12; break;
            default: continue;
        }
        
        if (*melody == '#') { note++; melody++; }
        if (*melody == '.') { dotted = true; melody++; }
        if (*melody >= '0' && *melody <= '9') { octave = *melody - '0'; melody++; }
        if (*melody == '.') { dotted = true; melody++; }
        
        uint32_t noteDuration = wholeNote / duration;
        if (dotted) noteDuration += noteDuration / 2;
        
        uint16_t frequency = 0;
        if (note > 0 && note <= 12) {
            frequency = NOTES[note];
            if (octave > 4) frequency <<= (octave - 4);
            else if (octave < 4) frequency >>= (4 - octave);
        }
        
        if (frequency > 0) {
            tone(pin, frequency, noteDuration * 0.9);
            delay(noteDuration);
        } else {
            delay(noteDuration);
        }
        noTone(pin);
    }
}

#endif // PLAY_RTTTL_HPP
