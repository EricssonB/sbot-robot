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
    
    // From 0002: Full initialization sequence
    // 1. Fade in Magenta
    _leds.fadeIn(Colors::MAGENTA, 500);
    
    // 2. Arms initialization - lower position first
    _arms.setPosition(15, 165);
    delay(500);
    
    // 3. Raise arms with victory gesture
    _arms.raise();
    delay(300);
    _arms.lower();
    
    // 4. Color sequence: Red -> Orange -> Yellow
    _leds.crossfade(Colors::MAGENTA, Colors::RED, 5);
    _leds.crossfade(Colors::RED, Colors::ORANGE, 10);
    _leds.crossfade(Colors::ORANGE, Colors::YELLOW, 10);
    
    // 5. Yellow hold then back to Magenta
    _leds.setColor(Colors::YELLOW);
    delay(200);
    _leds.crossfade(Colors::YELLOW, Colors::MAGENTA, 10);
    
    // 6. Arm adjustment during melody
    _arms.setPosition(_arms.getLeftAngle() + 30, _arms.getRightAngle() - 30);
    
    // 7. Play celebration melody (Della)
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_DELLA);
    #endif
    
    // 8. Final arm adjustments
    _arms.setPosition(_arms.getLeftAngle() - 22, _arms.getRightAngle() + 22);
    delay(500);
    _arms.raise();
    delay(300);
    
    // 9. Fade to half magenta-blue (chill indicator)
    _leds.crossfade(Colors::MAGENTA, RGBColor(128, 0, 64), 20);
    _arms.lower();
    
    DEBUG_PRINTLN(F("✅ Startup Sequence Complete!"));
    DEBUG_PRINTLN(F("😌 Entering Idle State..."));
    setState(SBotState::IDLE);
}

void StateManager::runDopeState() {
    setState(SBotState::DOPE);
    DEBUG_PRINTLN(F("🔥 Running Dope State..."));
    
    // From 001: dopeState() sequence
    // 1. Fade in magenta
    _leds.fadeIn(Colors::MAGENTA, 500);
    
    // 2. Raise arms with victory gesture
    _arms.raise();
    delay(300);
    _arms.lower();
    
    // 3. Color crossfade sequence: Red -> Orange -> Yellow
    _leds.crossfade(Colors::MAGENTA, Colors::RED, 5);
    _leds.crossfade(Colors::RED, Colors::ORANGE, 10);
    _leds.crossfade(Colors::ORANGE, Colors::YELLOW, 10);
    
    // 4. Hold yellow then crossfade back to magenta
    _leds.setColor(Colors::YELLOW);
    delay(100);
    _leds.crossfade(Colors::YELLOW, Colors::MAGENTA, 10);
    
    // 5. Arm movement during updown
    _arms.setPosition(_arms.getLeftAngle() + 30, _arms.getRightAngle() - 30);
    delay(300);
    
    // 6. Play the Della melody
    #if ENABLE_SOUND_EFFECTS
    playRtttlBlockingPGM(_buzzerPin, (char*)MELODY_DELLA);
    #endif
    
    // 7. Final arm adjustments
    _arms.setPosition(_arms.getLeftAngle() - 22, _arms.getRightAngle() + 22);
    delay(500);
    
    // 8. Final raise/lower with fail gesture
    _arms.raise();
    delay(300);
    _arms.lower();
    
    DEBUG_PRINTLN(F("✅ Dope State Complete!"));
    returnToIdle();
}

void StateManager::runChillState() {
    setState(SBotState::CHILL);
    DEBUG_PRINTLN(F("😌 Running Chill State..."));
    
    // From 001: chillState() sequence
    // 1. Set arms to relaxed position
    DEBUG_PRINTLN(F("🎵 Setting arms position..."));
    _arms.setPosition(15, 175);
    delay(300);
    
    // 2. Fade to 25% Magenta (64 out of 255)
    DEBUG_PRINTLN(F("💜 Fading to 25% Magenta..."));
    for (int i = 0; i <= 64; i += 2) {
        _leds.setColor(i, 0, i);  // Magenta fade (Red + Blue)
        delay(10);
    }
    
    // 3. Hold chill state
    delay(500);
    
    // 4. Return arms to home
    DEBUG_PRINTLN(F("🏡 Returning Home..."));
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
