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
     * 
     * 
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
     * Returns the HorseIdx with the maximum progress
     * @return HorseIdx index of the currently winning horse
     */
    HorseIdx getWinner();

    /**
     * Function that gets called every main loop iteration
     * This calls each horses loopCall function
     */
    void loopCall();

private:

    HorseDriver_ULN2003 _horses[Globals::GameControl::nHorses];

};
