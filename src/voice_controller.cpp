/**
 * @file voice_controller.cpp
 * @brief Implementation of voice recognition controller
 * @version 1.0.0
 */

#include "voice_controller.h"
#include <Arduino.h>

VoiceController::VoiceController()
    : _available(false) {
}

bool VoiceController::begin() {
    DEBUG_PRINTLN(F("Initializing Voice Recognition..."));
    
    // Try to initialize with retries
    uint8_t retries = 3;
    while (retries > 0) {
        if (_asr.begin()) {
            _available = true;
            DEBUG_PRINTLN(F("Voice Recognition initialized successfully"));
            
            // Default configuration
            setVolume(7);       // Max volume
            setMute(false);     // Unmuted
            setWakeTime(255);   // Max wake time
            
            return true;
        }
        
        DEBUG_PRINTLN(F("Voice module not responding, retrying..."));
        delay(1000);
        retries--;
    }
    
    DEBUG_PRINTLN(F("WARNING: Voice Recognition module not available"));
    _available = false;
    return false;
}

uint8_t VoiceController::getCommand() {
    if (!_available) {
        return 0;
    }
    
    return _asr.getCMDID();
}

void VoiceController::setVolume(uint8_t volume) {
    if (!_available) return;
    
    volume = constrain(volume, 1, 7);
    _asr.setVolume(volume);
    
    DEBUG_PRINT(F("Voice volume set to: "));
    DEBUG_PRINTLN(volume);
}

void VoiceController::setMute(bool muted) {
    if (!_available) return;
    
    _asr.setMuteMode(muted ? 1 : 0);
}

void VoiceController::setWakeTime(uint8_t duration) {
    if (!_available) return;
    
    _asr.setWakeTime(duration);
}

uint8_t VoiceController::getWakeTime() {
    if (!_available) return 0;
    
    return _asr.getWakeTime();
}

void VoiceController::playAudio(uint8_t cmdId) {
    if (!_available) return;
    
    _asr.playByCMDID(cmdId);
}
