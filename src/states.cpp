/**
 * @file states.cpp
 * @brief Implementation of SBot behavior states
 * @version 1.0.0
 */

#include "states.h"
#include "led_controller.h"
#include "servo_controller.h"
#include "colors.h"
#include "melodies.h"
#include "config.h"
#include <Arduino.h>
#include <PlayRtttl.hpp>

// State name lookup table
const char* getStateName(SBotState state) {
    switch (state) {
        case SBotState::IDLE:    return "IDLE";
        case SBotState::STARTUP: return "STARTUP";
        case SBotState::DOPE:    return "DOPE";
        case SBotState::CHILL:   return "CHILL";
        case SBotState::ALERT:   return "ALERT";
        case SBotState::SLEEP:   return "SLEEP";
        case SBotState::ERROR:   return "ERROR";
        default:                 return "UNKNOWN";
    }
}

StateManager::StateManager(LEDController& leds, ArmController& arms, uint8_t buzzerPin)
    : _leds(leds)
    , _arms(arms)
    , _buzzerPin(buzzerPin)
    , _currentState(SBotState::IDLE)
    , _previousState(SBotState::IDLE) {
}

void StateManager::setState(SBotState newState) {
    if (newState == _currentState) return;
    
    _previousState = _currentState;
    _currentState = newState;
    
    DEBUG_PRINT(F("State transition: "));
    DEBUG_PRINT(getStateName(_previousState));
    DEBUG_PRINT(F(" -> "));
    DEBUG_PRINTLN(getStateName(_currentState));
}

void StateManager::runStartup() {
    setState(SBotState::STARTUP);
    DEBUG_PRINTLN(F("🚀 Running Startup Sequence..."));
    
    // LED startup animation - rainbow crossfade
    _leds.crossfade(Colors::BLACK, Colors::RED, 5);
    _leds.crossfade(Colors::RED, Colors::GREEN, 5);
    _leds.crossfade(Colors::GREEN, Colors::BLUE, 5);
    _leds.crossfade(Colors::BLUE, Colors::WHITE, 5);
    
    // Arms initialization
    _arms.home();
    delay(200);
    _arms.raise();
    delay(200);
    _arms.lower();
    
    // Startup sound
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_STARTUP);
    #endif
    
    // Final LED state - dim white indicates ready
    _leds.crossfade(Colors::WHITE, RGBColor(50, 50, 50), 10);
    
    DEBUG_PRINTLN(F("✅ Startup Complete - SBot Ready!"));
    setState(SBotState::IDLE);
}

void StateManager::runDopeState() {
    setState(SBotState::DOPE);
    DEBUG_PRINTLN(F("🔥 Running Dope State..."));
    
    // Fade in magenta
    _leds.fadeIn(Colors::MAGENTA, 500);
    
    // Raise arms for celebration
    _arms.raise();
    delay(300);
    
    // Color sequence through warm colors
    _leds.crossfade(Colors::MAGENTA, Colors::RED, 5);
    _leds.crossfade(Colors::RED, Colors::ORANGE, 10);
    _leds.crossfade(Colors::ORANGE, Colors::YELLOW, 10);
    
    // Celebrate gesture
    _arms.celebrate();
    
    // Play celebration melody
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_DELLA);
    #endif
    
    // Final crossfade back to magenta
    _leds.crossfade(Colors::YELLOW, Colors::MAGENTA, 10);
    
    // Lower arms
    _arms.lower();
    
    DEBUG_PRINTLN(F("✅ Dope State Complete!"));
    returnToIdle();
}

void StateManager::runChillState() {
    setState(SBotState::CHILL);
    DEBUG_PRINTLN(F("😌 Running Chill State..."));
    
    // Set arms to relaxed position
    _arms.setPosition(15, 175);
    delay(300);
    
    // Fade to dim magenta (25% brightness)
    _leds.fadeIn(Colors::MAGENTA_DIM, 1000);
    
    // Breathing effect for calm atmosphere
    _leds.breathe(Colors::MAGENTA_DIM, 2);
    
    // Play calming sound
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_SLEEP);
    #endif
    
    // Return arms to home
    _arms.home();
    
    DEBUG_PRINTLN(F("✅ Chill State Complete!"));
    returnToIdle();
}

void StateManager::runAlertState() {
    setState(SBotState::ALERT);
    DEBUG_PRINTLN(F("⚠️ Running Alert State..."));
    
    // Flash orange for attention
    for (uint8_t i = 0; i < 3; i++) {
        _leds.setColor(Colors::ORANGE);
        delay(200);
        _leds.off();
        delay(200);
    }
    
    // Arms up
    _arms.raise();
    
    // Alert sound
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_ALERT);
    #endif
    
    // Hold alert color
    _leds.setColor(Colors::ORANGE);
    delay(1000);
    
    // Return to normal
    _arms.lower();
    
    DEBUG_PRINTLN(F("✅ Alert State Complete!"));
    returnToIdle();
}

void StateManager::returnToIdle() {
    // Fade to idle color (dim white)
    _leds.crossfade(_leds.getCurrentColor(), RGBColor(50, 50, 50), 15);
    _arms.home();
    setState(SBotState::IDLE);
}
