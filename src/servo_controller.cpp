/**
 * @file servo_controller.cpp
 * @brief Implementation of servo controller for SBot
 * @version 1.0.0
 */

#include "servo_controller.h"
#include <Arduino.h>

ArmController::ArmController(uint8_t leftPin, uint8_t rightPin)
    : _leftPin(leftPin)
    , _rightPin(rightPin)
    , _leftAngle(ARM_LEFT_HOME)
    , _rightAngle(ARM_RIGHT_HOME) {
}

void ArmController::begin() {
    _leftArm.attach(_leftPin);
    _rightArm.attach(_rightPin);
    home();
    
    DEBUG_PRINTLN(F("Arm Controller initialized"));
}

void ArmController::detach() {
    _leftArm.detach();
    _rightArm.detach();
}

void ArmController::home() {
    setPosition(ARM_LEFT_HOME, ARM_RIGHT_HOME);
    delay(SERVO_MOVE_DELAY);
}

void ArmController::raise() {
    setPosition(ARM_LEFT_RAISED, ARM_RIGHT_RAISED);
    delay(SERVO_MOVE_DELAY);
}

void ArmController::lower() {
    home();
}

void ArmController::setLeft(uint8_t angle) {
    _leftAngle = constrain(angle, 0, 180);
    _leftArm.write(_leftAngle);
}

void ArmController::setRight(uint8_t angle) {
    _rightAngle = constrain(angle, 0, 180);
    _rightArm.write(_rightAngle);
}

void ArmController::setPosition(uint8_t leftAngle, uint8_t rightAngle) {
    setLeft(leftAngle);
    setRight(rightAngle);
}

void ArmController::smoothMove(uint8_t leftTarget, uint8_t rightTarget, uint8_t speed) {
    // Calculate steps needed
    int8_t leftDiff = leftTarget - _leftAngle;
    int8_t rightDiff = rightTarget - _rightAngle;
    int8_t maxSteps = max(abs(leftDiff), abs(rightDiff));
    
    if (maxSteps == 0) return;
    
    float leftStep = (float)leftDiff / maxSteps;
    float rightStep = (float)rightDiff / maxSteps;
    
    float currentLeft = _leftAngle;
    float currentRight = _rightAngle;
    
    for (int8_t i = 0; i < maxSteps; i++) {
        currentLeft += leftStep;
        currentRight += rightStep;
        
        setLeft((uint8_t)currentLeft);
        setRight((uint8_t)currentRight);
        delay(speed);
    }
    
    // Ensure we reach exact target
    setPosition(leftTarget, rightTarget);
}

void ArmController::wave(uint8_t waves) {
    // Raise right arm
    smoothMove(_leftAngle, 90, 10);
    delay(200);
    
    // Wave motion
    for (uint8_t i = 0; i < waves; i++) {
        setRight(60);
        delay(200);
        setRight(120);
        delay(200);
    }
    
    // Return to neutral
    smoothMove(ARM_LEFT_HOME, ARM_RIGHT_HOME, 10);
}

void ArmController::celebrate() {
    // Raise both arms
    smoothMove(ARM_LEFT_RAISED, ARM_RIGHT_RAISED, 8);
    delay(200);
    
    // Wiggle
    for (uint8_t i = 0; i < 3; i++) {
        setPosition(ARM_LEFT_RAISED - 20, ARM_RIGHT_RAISED + 20);
        delay(150);
        setPosition(ARM_LEFT_RAISED + 20, ARM_RIGHT_RAISED - 20);
        delay(150);
    }
    
    // Hold raised
    setPosition(ARM_LEFT_RAISED, ARM_RIGHT_RAISED);
    delay(500);
    
    // Lower
    smoothMove(ARM_LEFT_HOME, ARM_RIGHT_HOME, 10);
}
