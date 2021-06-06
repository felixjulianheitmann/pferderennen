// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/HorseDriver.h>
#include <Stepper.h>
#include <config/globals.h>

class HorseDriver_ULN2003 : public HorseDriver
{
public:

    // default constructor
    HorseDriver_ULN2003();

    /**
     * constructor with hardware configuration and motor direction
     * @param motorPins the hardware pins connected to the motor
     * @param dir a switch to invert motor spin direction
     */
    HorseDriver_ULN2003(const Pin motorPins[4], bool const dir);

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
    void setVelocity(float velocity) override;

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
     * steps the motor one step further 
     * @param dir the direction to step
     */
    void step(bool const dir);

private:

    // Shows the horses control state
    enum State_t {
        Forward,
        Reverse,
        Stop
    } _state;

    // the velocity value
    float _velocity;

    // global motor spin direction - can invert motor behaviour
    bool _dir;

    // ULN2003 pins
    int _pins[4];

    // current step
    int _step;

    // the timestamp of the last step
    unsigned long _lastStepTime;
};
