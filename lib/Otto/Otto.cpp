/**
 * @file Otto.cpp
 * @brief Otto DIY Robot Library Implementation
 * @version 1.0.0
 * 
 * Simplified implementation of the Otto library.
 * For the full library, see: https://github.com/OttoDIY/OttoDIYLib
 */

#include "Otto.h"

// Oscillation parameters
#define OSCILLATOR_PERIOD 50

// Helper macro for degree to radian conversion
#define DEG2RAD(deg) ((deg) * PI / 180.0)

Otto::Otto() {
    for (int i = 0; i < 4; i++) {
        _servo_position[i] = 90;
        _servo_trim[i] = 0;
    }
}

void Otto::init(int LL, int RL, int LF, int RF, bool load_calibration, int Buzzer) {
    _servo_pins[0] = LL;  // Left Leg
    _servo_pins[1] = RL;  // Right Leg
    _servo_pins[2] = LF;  // Left Foot
    _servo_pins[3] = RF;  // Right Foot
    _buzzer_pin = Buzzer;
    
    attachServos();
}

void Otto::attachServos() {
    for (int i = 0; i < 4; i++) {
        _servo[i].attach(_servo_pins[i]);
    }
}

void Otto::detachServos() {
    for (int i = 0; i < 4; i++) {
        _servo[i].detach();
    }
}

void Otto::home() {
    int target[4] = {90, 90, 90, 90};
    _moveServos(500, target);
}

void Otto::_moveServos(int time, int target[4]) {
    if (time > 10) {
        for (int i = 0; i < 4; i++) {
            _increment[i] = (target[i] - _servo_position[i]) / (time / 10.0);
        }
        
        _finalTime = millis() + time;
        
        while (millis() < _finalTime) {
            _partialTime = millis() + 10;
            
            for (int i = 0; i < 4; i++) {
                _servo_position[i] += _increment[i];
                _servo[i].write(_servo_position[i] + _servo_trim[i]);
            }
            
            while (millis() < _partialTime);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            _servo_position[i] = target[i];
            _servo[i].write(_servo_position[i] + _servo_trim[i]);
        }
    }
    
    for (int i = 0; i < 4; i++) {
        _servo_position[i] = target[i];
    }
}

// =============================================================================
// SOUNDS
// =============================================================================

void Otto::_tone(float noteFrequency, long noteDuration, int silentDuration) {
    if (noteFrequency > 0) {
        tone(_buzzer_pin, noteFrequency, noteDuration);
        delay(noteDuration);
    }
    noTone(_buzzer_pin);
    delay(silentDuration);
}

void Otto::_bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration) {
    if (initFrequency < finalFrequency) {
        for (float i = initFrequency; i < finalFrequency; i = i * prop) {
            _tone(i, noteDuration, silentDuration);
        }
    } else {
        for (float i = initFrequency; i > finalFrequency; i = i / prop) {
            _tone(i, noteDuration, silentDuration);
        }
    }
}

void Otto::sing(int soundName) {
    switch (soundName) {
        case S_connection:
            _tone(NOTE_E5, 50, 30);
            _tone(NOTE_E6, 55, 25);
            _tone(NOTE_A6, 60, 10);
            break;

        case S_disconnection:
            _tone(NOTE_E5, 50, 30);
            _tone(NOTE_A6, 55, 25);
            _tone(NOTE_E6, 50, 10);
            break;

        case S_buttonPushed:
            _bendTones(NOTE_E6, NOTE_G6, 1.03, 20, 2);
            delay(30);
            _bendTones(NOTE_E6, NOTE_D7, 1.04, 10, 2);
            break;

        case S_mode1:
            _bendTones(NOTE_E6, NOTE_A6, 1.02, 30, 10);
            break;

        case S_mode2:
            _bendTones(NOTE_G6, NOTE_D7, 1.03, 30, 10);
            break;

        case S_mode3:
            _tone(NOTE_E6, 50, 100);
            _tone(NOTE_G6, 50, 80);
            _tone(NOTE_D7, 300, 0);
            break;

        case S_surprise:
            _bendTones(800, 2150, 1.02, 10, 1);
            _bendTones(2149, 800, 1.01, 7, 1);
            break;

        case S_OhOoh:
            _bendTones(880, 2000, 1.04, 8, 3);
            delay(200);
            for (int i = 880; i < 2000; i = i * 1.04) {
                _tone(NOTE_B5, 5, 10);
            }
            break;

        case S_OhOoh2:
            _bendTones(1880, 3000, 1.03, 8, 3);
            delay(200);
            for (int i = 1880; i < 3000; i = i * 1.03) {
                _tone(NOTE_C6, 10, 10);
            }
            break;

        case S_cuddly:
            _bendTones(700, 900, 1.03, 16, 4);
            _bendTones(899, 650, 1.01, 18, 7);
            break;

        case S_sleeping:
            _bendTones(100, 500, 1.04, 10, 10);
            delay(500);
            _bendTones(400, 100, 1.04, 10, 1);
            break;

        case S_happy:
            _bendTones(1500, 2500, 1.05, 20, 8);
            _bendTones(2499, 1500, 1.05, 25, 8);
            break;

        case S_superHappy:
            _bendTones(2000, 6000, 1.05, 8, 3);
            delay(50);
            _bendTones(5999, 2000, 1.05, 13, 2);
            break;

        case S_happy_short:
            _bendTones(1500, 2000, 1.05, 15, 8);
            delay(100);
            _bendTones(1900, 2500, 1.05, 10, 8);
            break;

        case S_sad:
            _bendTones(880, 669, 1.02, 20, 200);
            break;

        case S_confused:
            _bendTones(1000, 1700, 1.03, 8, 2);
            _bendTones(1699, 500, 1.04, 8, 3);
            _bendTones(1000, 1700, 1.05, 9, 10);
            break;

        case S_fart1:
            _bendTones(1600, 3000, 1.02, 2, 15);
            break;

        case S_fart2:
            _bendTones(2000, 6000, 1.02, 2, 20);
            break;

        case S_fart3:
            _bendTones(1600, 4000, 1.02, 2, 20);
            _bendTones(4000, 3000, 1.02, 2, 20);
            break;
    }
}

// Note frequency definitions
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
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// =============================================================================
// GESTURES
// =============================================================================

void Otto::playGesture(int gesture) {
    switch (gesture) {
        case OttoHappy:
            sing(S_happy);
            updown(2, 500, 20);
            break;

        case OttoSuperHappy:
            sing(S_superHappy);
            updown(4, 300, 25);
            break;

        case OttoSad:
            sing(S_sad);
            int sad[4] = {110, 70, 100, 80};
            _moveServos(700, sad);
            delay(500);
            home();
            break;

        case OttoSleeping:
            for (int i = 0; i < 3; i++) {
                sing(S_sleeping);
                delay(1000);
            }
            break;

        case OttoFart:
            sing(S_fart1);
            delay(200);
            sing(S_fart2);
            delay(200);
            sing(S_fart3);
            break;

        case OttoConfused:
            sing(S_confused);
            swing(3, 800, 30);
            break;

        case OttoVictory:
            swing(4, 500, 30);
            sing(S_superHappy);
            break;

        case OttoFail:
            sing(S_sad);
            shakeLeg(3, 500, 1);
            break;

        default:
            break;
    }
}

// =============================================================================
// MOVEMENTS
// =============================================================================

void Otto::_oscillate(int A[4], int O[4], int T, double phase_diff[4]) {
    for (int i = 0; i < 4; i++) {
        _servo_position[i] = round(O[i] + A[i] * sin(phase_diff[i]));
        _servo[i].write(_servo_position[i] + _servo_trim[i]);
    }
}

void Otto::_execute(int A[4], int O[4], int T, double phase_diff[4], float steps = 1.0) {
    int cycles = (int)steps;
    if (cycles >= 1) {
        for (int i = 0; i < cycles; i++) {
            for (int t = 0; t < T; t += OSCILLATOR_PERIOD) {
                for (int j = 0; j < 4; j++) {
                    phase_diff[j] = (phase_diff[j]) + (2 * PI * OSCILLATOR_PERIOD / T);
                }
                _oscillate(A, O, T, phase_diff);
                delay(OSCILLATOR_PERIOD);
            }
        }
    }
}

void Otto::walk(int steps, int T, int dir) {
    int A[4] = {30, 30, 20, 20};
    int O[4] = {0, 0, 4, -4};
    double phase_diff[4] = {0, 0, DEG2RAD(dir * -90), DEG2RAD(dir * -90)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::turn(int steps, int T, int dir) {
    int A[4] = {30, 30, 20, 20};
    int O[4] = {0, 0, 4, -4};
    double phase_diff[4] = {0, 0, DEG2RAD(dir * 90), DEG2RAD(dir * 90)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::updown(int steps, int T, int h) {
    int A[4] = {0, 0, h, h};
    int O[4] = {0, 0, h, -h};
    double phase_diff[4] = {0, 0, DEG2RAD(-90), DEG2RAD(90)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::swing(int steps, int T, int h) {
    int A[4] = {0, 0, h, h};
    int O[4] = {0, 0, h / 2, -h / 2};
    double phase_diff[4] = {0, 0, DEG2RAD(0), DEG2RAD(0)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::moonwalker(int steps, int T, int h, int dir) {
    int A[4] = {0, 0, h, h};
    int O[4] = {0, 0, h / 2 + 2, -h / 2 - 2};
    double phase_diff[4] = {0, 0, DEG2RAD(dir * -90), DEG2RAD(dir * -90)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::crusaito(int steps, int T, int h, int dir) {
    int A[4] = {25, 25, h, h};
    int O[4] = {0, 0, h / 2 + 4, -h / 2 - 4};
    double phase_diff[4] = {90, 90, DEG2RAD(dir * -90), DEG2RAD(dir * -90)};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::shakeLeg(int steps, int T, int dir) {
    int A[4] = {25, 25, 0, 0};
    int O[4] = {dir * -15, dir * 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(-90), DEG2RAD(90), 0, 0};
    
    for (int i = 0; i < 4; i++) O[i] += 90;
    
    _execute(A, O, T, phase_diff, steps);
    home();
}

void Otto::jump(int steps, int T) {
    int up[4] = {90, 90, 150, 30};
    for (int i = 0; i < steps; i++) {
        _moveServos(T / 2, up);
        home();
    }
}
