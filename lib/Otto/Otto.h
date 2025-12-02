/**
 * @file Otto.h
 * @brief Otto DIY Robot Library Header
 * @version 1.0.0
 * 
 * Simplified Otto library for SBot project.
 * Based on the original OttoDIYLib.
 * 
 * @see https://github.com/OttoDIY/OttoDIYLib
 */

#ifndef OTTO_H
#define OTTO_H

#include <Arduino.h>
#include <Servo.h>

// =============================================================================
// SOUND DEFINITIONS
// =============================================================================

// Otto sounds
#define S_connection    0
#define S_disconnection 1
#define S_buttonPushed  2
#define S_mode1         3
#define S_mode2         4
#define S_mode3         5
#define S_surprise      6
#define S_OhOoh         7
#define S_OhOoh2        8
#define S_cuddly        9
#define S_sleeping      10
#define S_happy         11
#define S_superHappy    12
#define S_happy_short   13
#define S_sad           14
#define S_confused      15
#define S_fart1         16
#define S_fart2         17
#define S_fart3         18

// Otto gestures
#define OttoHappy       0
#define OttoSuperHappy  1
#define OttoSad         2
#define OttoSleeping    3
#define OttoFart        4
#define OttoConfused    5
#define OttoLove        6
#define OttoAngry       7
#define OttoFretful     8
#define OttoMagic       9
#define OttoWave        10
#define OttoVictory     11
#define OttoFail        12

// =============================================================================
// OTTO CLASS
// =============================================================================

class Otto {
public:
    Otto();
    
    /**
     * @brief Initialize Otto with servo pins
     * @param LL Left leg pin
     * @param RL Right leg pin
     * @param LF Left foot pin
     * @param RF Right foot pin
     * @param load_calibration Load stored calibration
     * @param Buzzer Buzzer pin
     */
    void init(int LL, int RL, int LF, int RF, bool load_calibration, int Buzzer);
    
    /**
     * @brief Attach all servos
     */
    void attachServos();
    
    /**
     * @brief Detach all servos
     */
    void detachServos();
    
    /**
     * @brief Move to home/neutral position
     */
    void home();
    
    /**
     * @brief Play a sound
     * @param soundName Sound ID
     */
    void sing(int soundName);
    
    /**
     * @brief Play a gesture animation
     * @param gesture Gesture ID
     */
    void playGesture(int gesture);
    
    /**
     * @brief Walk forward/backward
     * @param steps Number of steps
     * @param T Period in ms
     * @param dir Direction (1=forward, -1=backward)
     */
    void walk(int steps, int T, int dir);
    
    /**
     * @brief Turn left/right
     * @param steps Number of steps
     * @param T Period in ms
     * @param dir Direction (1=left, -1=right)
     */
    void turn(int steps, int T, int dir);
    
    /**
     * @brief Moonwalk dance move
     * @param steps Number of steps
     * @param T Period in ms
     * @param h Height
     * @param dir Direction
     */
    void moonwalker(int steps, int T, int h, int dir);
    
    /**
     * @brief Crusaito dance move
     * @param steps Number of steps
     * @param T Period in ms
     * @param h Height
     * @param dir Direction
     */
    void crusaito(int steps, int T, int h, int dir);
    
    /**
     * @brief Up-down bounce
     * @param steps Number of bounces
     * @param T Period in ms
     * @param h Height
     */
    void updown(int steps, int T, int h);
    
    /**
     * @brief Swing movement
     * @param steps Number of swings
     * @param T Period in ms
     * @param h Height
     */
    void swing(int steps, int T, int h);
    
    /**
     * @brief Shake leg
     * @param steps Number of shakes
     * @param T Period in ms
     * @param dir Direction (1=left, -1=right)
     */
    void shakeLeg(int steps, int T, int dir);
    
    /**
     * @brief Jump movement
     */
    void jump(int steps, int T);

private:
    Servo _servo[4];
    int _servo_pins[4];
    int _servo_position[4];
    int _servo_trim[4];
    int _buzzer_pin;
    
    void _moveServos(int time, int target[4]);
    void _oscillate(int A[4], int O[4], int T, double phase_diff[4]);
    void _execute(int A[4], int O[4], int T, double phase_diff[4], float steps);
    unsigned long _finalTime;
    unsigned long _partialTime;
    float _increment[4];
    
    // Sound generation
    void _tone(float noteFrequency, long noteDuration, int silentDuration);
    void _bendTones(float initFrequency, float finalFrequency, float prop, long noteDuration, int silentDuration);
};

#endif // OTTO_H
