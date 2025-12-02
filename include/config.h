/**
 * @file config.h
 * @brief SBot Configuration - Pin definitions and system constants
 * @version 1.0.0
 * @date 2025-12-02
 * 
 * This file contains all hardware pin mappings and system configuration
 * for the SBot robot. Modify these values to match your hardware setup.
 */

#ifndef SBOT_CONFIG_H
#define SBOT_CONFIG_H

// =============================================================================
// VERSION INFO
// =============================================================================
#ifndef SBOT_VERSION
#define SBOT_VERSION "1.0.0"
#endif

// =============================================================================
// SERVO PIN DEFINITIONS (Digital Pins D2-D7)
// =============================================================================

// Otto DIY Leg Servos (for walking)
#define PIN_LEFT_LEG      2   // D2 - Left leg servo
#define PIN_RIGHT_LEG     3   // D3 - Right leg servo
#define PIN_LEFT_FOOT     4   // D4 - Left foot servo
#define PIN_RIGHT_FOOT    5   // D5 - Right foot servo

// Arm Servos
#define PIN_LEFT_ARM      6   // D6 - Left arm servo
#define PIN_RIGHT_ARM     7   // D7 - Right arm servo

// =============================================================================
// LED PIN DEFINITIONS (Digital Pins D9-D10)
// =============================================================================

#define PIN_NEOPIXEL_1    9   // D9 - Primary NeoPixel strip (left arm)
#define PIN_NEOPIXEL_2    10  // D10 - Secondary NeoPixel strip (right arm)
#define NUM_PIXELS        7   // Number of LEDs per strip

// =============================================================================
// SENSOR PIN DEFINITIONS
// =============================================================================

// Ultrasonic Sensor (HC-SR04)
#define PIN_ULTRASONIC_ECHO     8   // D8 - Echo pin
#define PIN_ULTRASONIC_TRIGGER  11  // D11 - Trigger pin

// Sound/Audio
#define PIN_BUZZER        13  // D13 - Piezo buzzer
#define PIN_MIC_DIGITAL   12  // D12 - Digital microphone

// Analog Sensors
#define PIN_IR_RECEIVER   A0  // Infrared receiver
#define PIN_TEMP_HUMIDITY A1  // DHT sensor
#define PIN_LIGHT_SENSOR  A2  // Light dependent resistor
#define PIN_TOUCH_SENSOR  A3  // Capacitive touch
#define PIN_MOTION_SENSOR A6  // PIR motion sensor
#define PIN_MIC_ANALOG    A7  // Analog microphone

// I2C (A4/A5 reserved for I2C bus)
// Voice Recognition Module & OLED Display use I2C
// SDA = A4, SCL = A5

// =============================================================================
// SERVO POSITION CONSTANTS
// =============================================================================

// Arm neutral/home positions
#define ARM_LEFT_HOME     0
#define ARM_RIGHT_HOME    190
#define ARM_LEFT_RAISED   130
#define ARM_RIGHT_RAISED  60

// =============================================================================
// TIMING CONSTANTS (in milliseconds)
// =============================================================================

#define SERVO_MOVE_DELAY      500   // Delay after servo movements
#define LED_FADE_STEP_DELAY   10    // Delay between LED fade steps
#define MAIN_LOOP_DELAY       300   // Main loop iteration delay

// =============================================================================
// VOICE COMMAND IDs (DFRobot DF2301Q)
// =============================================================================

#define CMD_WAKE_WORD     1   // Wake word detected
#define CMD_DOPE_STATE    5   // Trigger dope state
#define CMD_CHILL_STATE   6   // Trigger chill state

// =============================================================================
// SERIAL CONFIGURATION
// =============================================================================

#define SERIAL_BAUD_RATE  115200

// =============================================================================
// FEATURE FLAGS (Enable/Disable features at compile time)
// =============================================================================

#define ENABLE_VOICE_CONTROL    1   // Enable voice recognition
#define ENABLE_SERIAL_CONTROL   1   // Enable serial monitor commands
#define ENABLE_LED_ANIMATIONS   1   // Enable NeoPixel animations
#define ENABLE_SOUND_EFFECTS    1   // Enable buzzer sounds
#define ENABLE_DEBUG_OUTPUT     1   // Enable debug messages

// Debug macro
#if ENABLE_DEBUG_OUTPUT
#define DEBUG_PRINT(x)    Serial.print(x)
#define DEBUG_PRINTLN(x)  Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

#endif // SBOT_CONFIG_H
