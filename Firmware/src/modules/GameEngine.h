// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <config/globals.h>
#include <modules/HorseDriver_ULN2003.h>

class GameEngine
{
public:

    /**
     * @brief GameEngine Constructor
     */
    GameEngine();

    /**
     * Resets all horses to their start position
     */
    void reset();

    /**
     * Starts a game. This means calls to loopCall() will cause progress
     */
    void start();

    /**
     * Stops the game. Further calls to loopCall() will not cause progress
     */
    void stop();

    /**
     * Function that gets called every main loop iteration
     * This calls each horses loopCall function
     */
    void loopCall();

    /**
     * Signalize that a horse reached the starting gate
     * If all horses arrived at starting gate, game is stopped
     */
    void triggerHorse(HorseIdx horse);

    /**
     * Changes the game speed
     * @param speed the speed as a factor from 0 - 1 resulting in MinVelocity - MaxVelocity
     */
    void setGameSpeed(float speed);


private:

    enum State_t {
        Started,
        Stopped,
        Resetting
    } _state;

public:
    // The motor drivers to move the horses
    HorseDriver* _horses[Globals::GameControl::nHorses];

private:
    // Flags to signalize whether a horse is at the starting gate. Reset at race start
    bool _horseStartFlags[Globals::GameControl::nHorses] = { false };

    unsigned long _horseTriggerDebouce[Globals::GameControl::nHorses];

    // Horse velocity changer time interval
    unsigned long _lastVelChange;
    
};
