/**
 * @file main.cpp
 * @brief SBot - Interactive Robot Main Program
 * @version 1.0.0
 * @date 2025-12-02
 * 
 * @details
 * SBot is an interactive robot built on the Otto DIY platform.
 * 
 * TWO MODES AVAILABLE (set in platformio.ini):
 * - VOICE MODE (env:voice): Uses DFRobot DF2301Q for voice-activated commands
 * - AUTOPLAY MODE (env:autoplay): Plays full sequence automatically on startup
 * 
 * @author Eric B
 * @see https://github.com/EricssonB/sbot-robot
 */

// =============================================================================
// INCLUDES
// =============================================================================

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <Otto.h>
#include <PlayRtttl.hpp>

// Only include voice module for voice mode
#ifdef SBOT_MODE_VOICE
#include "DFRobot_DF2301Q.h"
#endif

#include "melodies.h"

// =============================================================================
// PIN DEFINITIONS
// =============================================================================

#define LeftLeg     2
#define RightLeg    3
#define LeftFoot    4
#define RightFoot   5
#define PIN_AL      6   // Left Arm
#define PIN_AR      7   // Right Arm
#define PIN_LED_1   9   // NeoPixel Strip 1
#define PIN_LED_2   10  // NeoPixel Strip 2
#define Buzzer      13
#define NUM_PIXELS  7

// =============================================================================
// GLOBAL OBJECTS
// =============================================================================

Otto Otto;
Servo AL, AR;

Adafruit_NeoPixel strip1(NUM_PIXELS, PIN_LED_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(NUM_PIXELS, PIN_LED_2, NEO_GRB + NEO_KHZ800);

#ifdef SBOT_MODE_VOICE
DFRobot_DF2301Q_I2C asr;
#endif

// Color array for crossfades
int colors[][3] = {
    {255, 0, 255},  // Magenta (Start)
    {64, 0, 64},    // Magenta (Chill)
    {255, 0, 0},    // Red
    {255, 127, 0},  // Orange
    {255, 255, 0}   // Yellow
};

// =============================================================================
// LED FUNCTIONS
// =============================================================================

void setAllPixels(int r, int g, int b) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        strip1.setPixelColor(i, strip1.Color(r, g, b));
        strip2.setPixelColor(i, strip2.Color(r, g, b));
    }
    strip1.show();
    strip2.show();
}

void smoothCrossfade(int color1[3], int color2[3], int speed) {
    for (int i = 0; i <= 255; i += 5) {
        int r = map(i, 0, 255, color1[0], color2[0]);
        int g = map(i, 0, 255, color1[1], color2[1]);
        int b = map(i, 0, 255, color1[2], color2[2]);
        setAllPixels(r, g, b);
        delay(speed);
    }
}

void fadeInMagenta() {
    for (int i = 0; i <= 255; i += 5) {
        for (int j = 0; j < NUM_PIXELS; j++) {
            strip1.setPixelColor(j, strip1.Color((255 * i) / 255, 0, (255 * i) / 255));
            strip2.setPixelColor(j, strip2.Color((255 * i) / 255, 0, (255 * i) / 255));
        }
        strip1.show();
        strip2.show();
        delay(10);
    }
}

void fadeToHalfMagentaBlue() {
    for (int i = 255; i >= 128; i -= 5) {
        setAllPixels(i, 0, i / 2);
        delay(20);
    }
}

// =============================================================================
// ARM FUNCTIONS
// =============================================================================

void raiseArms() {
    AL.write(130);
    AR.write(60);
    delay(500);
}

void lowerArms() {
    AL.write(0);
    AR.write(190);
    delay(500);
}

// =============================================================================
// STATE FUNCTIONS
// =============================================================================

/**
 * @brief Dope State - Excited celebration sequence
 * Triggered by voice command (CMDID 5) or serial "dope"
 */
void dopeState() {
    Serial.println(F("🔥 Running Dope State..."));

    fadeInMagenta();
    Otto.sing(S_superHappy);
    raiseArms();
    Otto.playGesture(OttoVictory);
    lowerArms();

    for (int c = 2; c < 4; c++) {
        smoothCrossfade(colors[c], colors[c + 1], (c == 2) ? 5 : 10);
    }

    setAllPixels(255, 255, 0);
    smoothCrossfade(colors[4], colors[0], 10);
    AL.write(AL.read() + 30);
    AR.write(AR.read() - 30);
    Otto.sing(S_happy);
    Otto.updown(1, 1500, 20);
    playRtttlBlockingPGM(Buzzer, (char*)MELODY_DELLA);

    AL.write(AL.read() - 22);
    AR.write(AR.read() + 22);
    delay(500);
    raiseArms();
    Otto.playGesture(OttoFail);
    lowerArms();

    Serial.println(F("✅ Dope State Complete!"));
}

/**
 * @brief Chill State - Calm relaxed sequence
 * Triggered by voice command (CMDID 6) or serial "chill"
 */
void chillState() {
    Serial.println(F("🎵 Setting arms position..."));
    AL.write(15);
    AR.write(175);

    Serial.println(F("🎵 Playing S_cuddly..."));
    Otto.sing(S_cuddly);

    Serial.println(F("💜 Fading to 25% Magenta..."));
    for (int i = 0; i <= 64; i += 2) {
        setAllPixels(i, 0, i);
        delay(10);
    }

    Serial.println(F("🕺 Performing Crusaito Move..."));
    Otto.crusaito(2, 1500, 15, 1);

    Serial.println(F("🏡 Returning Home..."));
    Otto.home();

    Serial.println(F("🎶 Playing S_happy_short..."));
    Otto.sing(S_happy_short);

    Serial.println(F("✅ Chill State Complete!"));
}

/**
 * @brief Full Startup Sequence (for AUTOPLAY mode)
 * Runs the complete animation automatically
 */
void runFullStartupSequence() {
    Serial.println(F("🚀 Running Full Startup Sequence..."));
    
    // Fade in Magenta
    fadeInMagenta();
    Otto.sing(S_superHappy);
    raiseArms();
    Otto.playGesture(OttoVictory);
    lowerArms();
    
    // Color crossfade sequence
    for (int c = 2; c < 4; c++) {
        int speed = (c == 2) ? 5 : 10;
        smoothCrossfade(colors[c], colors[c + 1], speed);
    }
    
    setAllPixels(255, 255, 0);
    smoothCrossfade(colors[4], colors[0], 10);
    
    AL.write(AL.read() + 30);
    AR.write(AR.read() - 30);
    Otto.updown(1, 1500, 20);
    playRtttlBlockingPGM(Buzzer, (char*)MELODY_DELLA);

    AL.write(AL.read() - 22);
    AR.write(AR.read() + 22);
    delay(500);
    raiseArms();
    Otto.playGesture(OttoFail);
    fadeToHalfMagentaBlue();
    lowerArms();

    Serial.println(F("✅ Startup Sequence Complete!"));
    Serial.println(F("😌 Entering Idle State..."));
}

// =============================================================================
// SETUP
// =============================================================================

void setup() {
    Serial.begin(115200);
    
    Serial.println(F(""));
    Serial.println(F("╔═══════════════════════════════════════╗"));
    Serial.println(F("║           SBot v1.0.0                 ║"));
    #ifdef SBOT_MODE_VOICE
    Serial.println(F("║       Mode: VOICE ACTIVATED           ║"));
    #else
    Serial.println(F("║       Mode: AUTO-PLAY                 ║"));
    #endif
    Serial.println(F("╚═══════════════════════════════════════╝"));
    Serial.println(F(""));
    
    Serial.println(F("Initializing SBot..."));

    // Initialize voice module (VOICE mode only)
    #ifdef SBOT_MODE_VOICE
    while (!(asr.begin())) {
        Serial.println(F("Communication with voice module failed, retrying..."));
        delay(3000);
    }
    Serial.println(F("Voice module OK!"));
    asr.setVolume(7);
    asr.setMuteMode(0);
    asr.setWakeTime(255);
    Serial.print(F("Wake time: "));
    Serial.println(asr.getWakeTime());
    #endif

    // Initialize buzzer
    pinMode(Buzzer, OUTPUT);

    // Initialize NeoPixel strips
    strip1.begin();
    strip2.begin();
    strip1.show();
    strip2.show();

    // Initialize Otto
    Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
    Otto.home();

    // Initialize arm servos
    AL.attach(PIN_AL);
    AR.attach(PIN_AR);
    AL.write(0);
    AR.write(190);

    Serial.println(F("✅ Hardware Ready!"));

    // MODE-SPECIFIC STARTUP
    #ifdef SBOT_MODE_AUTOPLAY
    // Auto-play mode: Run full sequence automatically
    runFullStartupSequence();
    #else
    // Voice mode: Just show ready message
    Serial.println(F(""));
    Serial.println(F("Waiting for commands..."));
    Serial.println(F("  Voice: Say wake word, then command"));
    Serial.println(F("  Serial: Type 'dope' or 'chill'"));
    Serial.println(F(""));
    #endif
}

// =============================================================================
// MAIN LOOP
// =============================================================================

void loop() {
    
    // ===== VOICE COMMANDS (Voice mode only) =====
    #ifdef SBOT_MODE_VOICE
    uint8_t CMDID = asr.getCMDID();
    switch (CMDID) {
        case 5:
            Serial.println(F("🎤 CMDID 5 Received: Triggering Dope State!"));
            dopeState();
            break;

        case 6:
            Serial.println(F("🎤 CMDID 6 Received: Triggering Chill State!"));
            chillState();
            break;

        default:
            if (CMDID != 0) {
                Serial.print(F("CMDID = "));
                Serial.println(CMDID);
            }
            break;
    }
    #endif

    // ===== SERIAL COMMANDS (Both modes) =====
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command.equalsIgnoreCase("dope")) {
            Serial.println(F("🖥️ Serial Command: Triggering Dope State!"));
            dopeState();
        }
        else if (command.equalsIgnoreCase("chill")) {
            Serial.println(F("🖥️ Serial Command: Triggering Chill State!"));
            chillState();
        }
        else if (command.equalsIgnoreCase("startup") || command.equalsIgnoreCase("demo")) {
            Serial.println(F("🖥️ Serial Command: Running Full Startup Sequence!"));
            runFullStartupSequence();
        }
        else if (command.equalsIgnoreCase("home")) {
            Serial.println(F("🖥️ Returning home..."));
            Otto.home();
            AL.write(0);
            AR.write(190);
            setAllPixels(0, 0, 0);
        }
        else if (command.equalsIgnoreCase("help")) {
            Serial.println(F("\n--- Available Commands ---"));
            Serial.println(F("  dope    - Run Dope State"));
            Serial.println(F("  chill   - Run Chill State"));
            Serial.println(F("  startup - Run full startup sequence"));
            Serial.println(F("  home    - Return to home position"));
            Serial.println(F("  help    - Show this menu"));
            Serial.println(F("--------------------------\n"));
        }
        else if (command.length() > 0) {
            Serial.println(F("❌ Unknown command. Type 'help' for options."));
        }
    }

    delay(300);
}
