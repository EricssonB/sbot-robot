/**
 * @file main.cpp
 * @brief SBot - Interactive Robot Main Program
 * @version 1.0.0
 * @date 2025-12-02
 * 
 * @details
 * SBot is an interactive robot built on the Otto DIY platform with
 * extended capabilities including:
 * - Voice recognition control (DFRobot DF2301Q)
 * - NeoPixel LED arm lighting
 * - Custom arm servos
 * - Multiple behavioral states
 * 
 * @hardware
 * - Arduino Uno/Mega
 * - Otto DIY base (4 servos)
 * - 2x Arm servos
 * - 2x NeoPixel LED strips (7 LEDs each)
 * - DFRobot DF2301Q Voice Recognition Module
 * - Piezo buzzer
 * 
 * @author Eric B
 * @see https://github.com/yourusername/sbot-robot
 */

// =============================================================================
// INCLUDES
// =============================================================================

#include <Arduino.h>
#include <Otto.h>

#include "config.h"
#include "colors.h"
#include "melodies.h"
#include "led_controller.h"
#include "servo_controller.h"
#include "voice_controller.h"
#include "states.h"

// =============================================================================
// GLOBAL OBJECTS
// =============================================================================

// Otto DIY robot instance (handles leg servos)
Otto otto;

// Custom controllers
LEDController leds(PIN_NEOPIXEL_1, PIN_NEOPIXEL_2, NUM_PIXELS);
ArmController arms(PIN_LEFT_ARM, PIN_RIGHT_ARM);
VoiceController voice;
StateManager states(leds, arms, PIN_BUZZER);

// =============================================================================
// FUNCTION PROTOTYPES
// =============================================================================

void initializeHardware();
void processVoiceCommands();
void processSerialCommands();
void printHelp();

// =============================================================================
// SETUP
// =============================================================================

/**
 * @brief Arduino setup function - runs once at startup
 */
void setup() {
    // Initialize serial communication
    Serial.begin(SERIAL_BAUD_RATE);
    while (!Serial && millis() < 3000) {
        ; // Wait for serial port (with timeout for non-USB scenarios)
    }
    
    Serial.println(F(""));
    Serial.println(F("╔═══════════════════════════════════════╗"));
    Serial.println(F("║           SBot v1.0.0                 ║"));
    Serial.println(F("║     Interactive Robot Companion       ║"));
    Serial.println(F("╚═══════════════════════════════════════╝"));
    Serial.println(F(""));
    
    // Initialize all hardware
    initializeHardware();
    
    // Run startup sequence
    states.runStartup();
    
    // Print help menu
    printHelp();
}

// =============================================================================
// MAIN LOOP
// =============================================================================

/**
 * @brief Arduino main loop - runs continuously
 */
void loop() {
    // Process voice commands (if enabled)
    #if ENABLE_VOICE_CONTROL
    processVoiceCommands();
    #endif
    
    // Process serial commands (if enabled)
    #if ENABLE_SERIAL_CONTROL
    processSerialCommands();
    #endif
    
    // Small delay to prevent overwhelming the system
    delay(MAIN_LOOP_DELAY);
}

// =============================================================================
// INITIALIZATION
// =============================================================================

/**
 * @brief Initialize all hardware components
 */
void initializeHardware() {
    DEBUG_PRINTLN(F("Initializing hardware..."));
    
    // Configure buzzer pin
    pinMode(PIN_BUZZER, OUTPUT);
    
    // Initialize LED controller
    leds.begin();
    
    // Initialize Otto DIY (leg servos)
    otto.init(PIN_LEFT_LEG, PIN_RIGHT_LEG, PIN_LEFT_FOOT, PIN_RIGHT_FOOT, true, PIN_BUZZER);
    otto.home();
    
    // Initialize arm controller
    arms.begin();
    
    // Initialize voice recognition
    #if ENABLE_VOICE_CONTROL
    if (!voice.begin()) {
        DEBUG_PRINTLN(F("Voice control unavailable - continuing without it"));
    }
    #endif
    
    DEBUG_PRINTLN(F("Hardware initialization complete!"));
}

// =============================================================================
// COMMAND PROCESSING
// =============================================================================

/**
 * @brief Process voice recognition commands
 */
void processVoiceCommands() {
    if (!voice.isAvailable()) return;
    
    uint8_t cmdId = voice.getCommand();
    
    if (cmdId == 0) return;  // No command detected
    
    DEBUG_PRINT(F("Voice command received: "));
    DEBUG_PRINTLN(cmdId);
    
    switch (cmdId) {
        case CMD_DOPE_STATE:
            Serial.println(F("🎤 Voice: Triggering Dope State!"));
            otto.sing(S_superHappy);
            states.runDopeState();
            break;
            
        case CMD_CHILL_STATE:
            Serial.println(F("🎤 Voice: Triggering Chill State!"));
            otto.sing(S_cuddly);
            states.runChillState();
            break;
            
        default:
            Serial.print(F("Unknown voice command ID: "));
            Serial.println(cmdId);
            break;
    }
}

/**
 * @brief Process serial monitor commands
 */
void processSerialCommands() {
    if (!Serial.available()) return;
    
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    
    if (command.length() == 0) return;
    
    DEBUG_PRINT(F("Serial command: "));
    DEBUG_PRINTLN(command);
    
    // Command parsing
    if (command == "dope" || command == "d") {
        Serial.println(F("🖥️ Triggering Dope State!"));
        otto.sing(S_superHappy);
        states.runDopeState();
    }
    else if (command == "chill" || command == "c") {
        Serial.println(F("🖥️ Triggering Chill State!"));
        otto.sing(S_cuddly);
        states.runChillState();
    }
    else if (command == "alert" || command == "a") {
        Serial.println(F("🖥️ Triggering Alert State!"));
        otto.sing(S_surprise);
        states.runAlertState();
    }
    else if (command == "wave" || command == "w") {
        Serial.println(F("🖥️ Waving!"));
        arms.wave();
    }
    else if (command == "home" || command == "h") {
        Serial.println(F("🖥️ Returning home..."));
        arms.home();
        otto.home();
        states.returnToIdle();
    }
    else if (command == "walk") {
        Serial.println(F("🖥️ Walking forward..."));
        otto.walk(4, 1000, 1);  // 4 steps, 1000ms period, forward
    }
    else if (command == "dance") {
        Serial.println(F("🖥️ Dancing!"));
        otto.moonwalker(3, 1000, 25, 1);
        otto.crusaito(2, 1500, 20, 1);
    }
    else if (command == "rainbow") {
        Serial.println(F("🖥️ Rainbow LEDs!"));
        leds.rainbow(2, 5);
        states.returnToIdle();
    }
    else if (command == "help" || command == "?") {
        printHelp();
    }
    else if (command == "status") {
        Serial.println(F("\n--- SBot Status ---"));
        Serial.print(F("Current State: "));
        Serial.println(getStateName(states.getCurrentState()));
        Serial.print(F("Voice Control: "));
        Serial.println(voice.isAvailable() ? "Available" : "Unavailable");
        Serial.print(F("Left Arm Angle: "));
        Serial.println(arms.getLeftAngle());
        Serial.print(F("Right Arm Angle: "));
        Serial.println(arms.getRightAngle());
        Serial.println(F("-------------------\n"));
    }
    else {
        Serial.println(F("❌ Unknown command. Type 'help' for available commands."));
    }
}

/**
 * @brief Print help menu with available commands
 */
void printHelp() {
    Serial.println(F("\n╔═══════════════════════════════════════╗"));
    Serial.println(F("║          Available Commands           ║"));
    Serial.println(F("╠═══════════════════════════════════════╣"));
    Serial.println(F("║  dope, d    - Excited state           ║"));
    Serial.println(F("║  chill, c   - Calm state              ║"));
    Serial.println(F("║  alert, a   - Alert state             ║"));
    Serial.println(F("║  wave, w    - Wave gesture            ║"));
    Serial.println(F("║  home, h    - Return to home          ║"));
    Serial.println(F("║  walk       - Walk forward            ║"));
    Serial.println(F("║  dance      - Dance moves             ║"));
    Serial.println(F("║  rainbow    - Rainbow LED effect      ║"));
    Serial.println(F("║  status     - Show system status      ║"));
    Serial.println(F("║  help, ?    - Show this menu          ║"));
    Serial.println(F("╚═══════════════════════════════════════╝\n"));
}
