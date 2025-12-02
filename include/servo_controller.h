/**
 * @file servo_controller.h
 * @brief Servo motor controller for SBot arms and Otto legs
 * @version 1.0.0
 */

#ifndef SBOT_SERVO_CONTROLLER_H
#define SBOT_SERVO_CONTROLLER_H

#include <Servo.h>
#include "config.h"

/**
 * @class ArmController
 * @brief Controls SBot's arm servos with smooth movements
 */
class ArmController {
public:
    /**
     * @brief Construct arm controller with specified pins
     * @param leftPin Pin for left arm servo
     * @param rightPin Pin for right arm servo
     */
    ArmController(uint8_t leftPin, uint8_t rightPin);
    
    /**
     * @brief Initialize and attach servos
     */
    void begin();
    
    /**
     * @brief Detach servos (save power, reduce jitter)
     */
    void detach();
    
    /**
     * @brief Move arms to home/neutral position
     */
    void home();
    
    /**
     * @brief Raise both arms up
     */
    void raise();
    
    /**
     * @brief Lower both arms down
     */
    void lower();
    
    /**
     * @brief Set left arm position
     * @param angle Servo angle (0-180)
     */
    void setLeft(uint8_t angle);
    
    /**
     * @brief Set right arm position
     * @param angle Servo angle (0-180)
     */
    void setRight(uint8_t angle);
    
    /**
     * @brief Move both arms to specific positions
     * @param leftAngle Left arm angle
     * @param rightAngle Right arm angle
     */
    void setPosition(uint8_t leftAngle, uint8_t rightAngle);
    
    /**
     * @brief Smoothly move arms to position
     * @param leftAngle Target left arm angle
     * @param rightAngle Target right arm angle
     * @param speed Delay between steps (lower = faster)
     */
    void smoothMove(uint8_t leftAngle, uint8_t rightAngle, uint8_t speed = 15);
    
    /**
     * @brief Wave gesture
     * @param waves Number of waves
     */
    void wave(uint8_t waves = 3);
    
    /**
     * @brief Celebrate gesture (arms up and wiggle)
     */
    void celebrate();
    
    /**
     * @brief Get current left arm angle
     */
    uint8_t getLeftAngle() const { return _leftAngle; }
    
    /**
     * @brief Get current right arm angle
     */
    uint8_t getRightAngle() const { return _rightAngle; }

private:
    Servo _leftArm;
    Servo _rightArm;
    uint8_t _leftPin;
    uint8_t _rightPin;
    uint8_t _leftAngle;
    uint8_t _rightAngle;
};

#endif // SBOT_SERVO_CONTROLLER_H
