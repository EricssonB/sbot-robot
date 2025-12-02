/**
 * @file states.h
 * @brief SBot behavior states and state machine
 * @version 1.0.0
 */

#ifndef SBOT_STATES_H
#define SBOT_STATES_H

#include <stdint.h>

// Forward declarations
class LEDController;
class ArmController;

/**
 * @enum SBotState
 * @brief Enumeration of all possible SBot states
 */
enum class SBotState : uint8_t {
    IDLE,           // Default state, waiting for input
    STARTUP,        // Boot sequence
    DOPE,           // Excited/celebration state
    CHILL,          // Calm/relaxed state
    ALERT,          // Attention/warning state
    SLEEP,          // Low power state
    ERROR           // Error state
};

/**
 * @brief Get string name of state (for debugging)
 * @param state The state to get name for
 * @return String representation of state
 */
const char* getStateName(SBotState state);

/**
 * @class StateManager
 * @brief Manages SBot's behavioral states
 */
class StateManager {
public:
    /**
     * @brief Construct state manager with controller references
     * @param leds Reference to LED controller
     * @param arms Reference to arm controller
     * @param buzzerPin Pin for buzzer
     */
    StateManager(LEDController& leds, ArmController& arms, uint8_t buzzerPin);
    
    /**
     * @brief Get current state
     * @return Current SBot state
     */
    SBotState getCurrentState() const { return _currentState; }
    
    /**
     * @brief Transition to a new state
     * @param newState State to transition to
     */
    void setState(SBotState newState);
    
    /**
     * @brief Execute startup sequence
     */
    void runStartup();
    
    /**
     * @brief Execute dope/excited state sequence
     */
    void runDopeState();
    
    /**
     * @brief Execute chill/calm state sequence
     */
    void runChillState();
    
    /**
     * @brief Execute alert state sequence
     */
    void runAlertState();
    
    /**
     * @brief Return to idle state
     */
    void returnToIdle();

private:
    LEDController& _leds;
    ArmController& _arms;
    uint8_t _buzzerPin;
    SBotState _currentState;
    SBotState _previousState;
};

#endif // SBOT_STATES_H
