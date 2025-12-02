/**
 * @file voice_controller.h
 * @brief Voice recognition controller using DFRobot DF2301Q
 * @version 1.0.0
 */

#ifndef SBOT_VOICE_CONTROLLER_H
#define SBOT_VOICE_CONTROLLER_H

#include "DFRobot_DF2301Q.h"
#include "config.h"

/**
 * @class VoiceController
 * @brief Manages voice recognition using DFRobot DF2301Q module
 */
class VoiceController {
public:
    /**
     * @brief Default constructor using I2C
     */
    VoiceController();
    
    /**
     * @brief Initialize the voice recognition module
     * @return true if initialization successful
     */
    bool begin();
    
    /**
     * @brief Check for and return command ID
     * @return Command ID (0 if no command detected)
     */
    uint8_t getCommand();
    
    /**
     * @brief Set the speaker volume
     * @param volume Volume level (1-7)
     */
    void setVolume(uint8_t volume);
    
    /**
     * @brief Set mute mode
     * @param muted true to mute, false to unmute
     */
    void setMute(bool muted);
    
    /**
     * @brief Set wake-up duration
     * @param duration Duration value (0-255)
     */
    void setWakeTime(uint8_t duration);
    
    /**
     * @brief Get current wake-up duration
     * @return Wake-up duration value
     */
    uint8_t getWakeTime();
    
    /**
     * @brief Play audio by command ID
     * @param cmdId Command ID to play
     */
    void playAudio(uint8_t cmdId);
    
    /**
     * @brief Check if module is available
     * @return true if module is responding
     */
    bool isAvailable() const { return _available; }

private:
    DFRobot_DF2301Q_I2C _asr;
    bool _available;
};

#endif // SBOT_VOICE_CONTROLLER_H
