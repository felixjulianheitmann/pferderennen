// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/HorseDriver.h>

class HorseDriver_ULN2003 : HorseDriver
{
public:
    HorseDriver_ULN2003(/* args */);

    /**
     * A initialization function to setup motor configurations, etc. 
     */
    void init() override;

    /**
     * This function is called in every iteration of the main loop.
     * After a call to startMoving, this function can be used to increment stepper motors, etc 
     */
    void loopCall() override;

    /**
     * Set the horse velocity. This should relate to the horses' motors' rpm
     * @param velocity a velocity value that determines the horses' pace
     * The velocity value ranges from Globals::Horse::MinVelocity to Globals::Horse::MaxVelocity
     * Game reset is always at Globals::Horse::MaxVelocity - full speed.
     */
    void setVelocity(float const velocity) override;

    /**
     * Start the horse forward movement.
     * This function should enable the horses' ability to move. 
     * It is called at the start of a race.
     */
    void forward() override;

    /**
     * Start the horse reverse movement.
     * This function should enable the horses' ability to move. 
     * It is called at a game reset.
     */
    void reverse() override;

    /**
     * Stop the horse movement.
     * This function should disable the horses' ability to move. 
     */
    void stop() override;

    /**
     * This function should return some form of progress information.
     * The precise position is not relevant. The value is used to determine the winning horse, after
     * the finish line has been triggered.
     * 
     * This function might be used if there is an indication which horse won. Led stripes or something
     * 
     * @return float a qualitative progress value that enables horse progess comparison
     */
    float getProgress() override;

    /**
     * Resets the progress value. The function is called at the game reset.
     */
    void resetProgress() override;

private:

    // whether movement is enabled
    bool _enabled;

    // the progress value
    float _progress;


};
