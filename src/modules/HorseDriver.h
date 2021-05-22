// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

/**
 * @brief This abstract class provides an interface that is used to
 * move horses along the track.
 */

class HorseDriver
{
public:
    HorseDriver() {};
    ~HorseDriver() {};

    /**
     * A initialization function to setup motor configurations, etc. 
     */
    virtual void init() = 0;

    /**
     * This function is called in every iteration of the main loop.
     * After a call to startMoving, this function can be used to increment stepper motors, etc 
     */
    virtual void loopCall() = 0;

    /**
     * Set the horse velocity. This should relate to the horses' motors' rpm
     * @param velocity a velocity value that determines the horses' pace
     * The velocity value ranges from Globals::Horse::MinVelocity to Globals::Horse::MaxVelocity
     * Game reset is always at Globals::Horse::MaxVelocity - full speed.
     */
    virtual void setVelocity(float const velocity) = 0;

    /**
     * Start the horse forward movement.
     * This function should enable the horses' ability to move. 
     * It is called at the start of a race.
     */
    virtual void forward() = 0;

    /**
     * Start the horse reverse movement.
     * This function should enable the horses' ability to move. 
     * It is called at a game reset.
     */
    virtual void reverse() = 0;

    /**
     * Stop the horse movement.
     * This function should disable the horses' ability to move. 
     */
    virtual void stop() = 0;

    /**
     * This function should return some form of progress information.
     * The precise position is not relevant. The value is used to determine the winning horse, after
     * the finish line has been triggered.
     * 
     * This function might be used if there is an indication which horse won. Led stripes or something
     * 
     * @return float a qualitative progress value that enables horse progess comparison
     */
    virtual float getProgress() = 0;

    /**
     * Resets the progress value. The function is called at the game reset.
     */
    virtual void resetProgress() = 0;

};