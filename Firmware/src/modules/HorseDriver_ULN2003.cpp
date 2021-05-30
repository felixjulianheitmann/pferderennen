// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/HorseDriver_ULN2003.h>
#include <config/globals.h>
#include <Stepper.h>

HorseDriver_ULN2003::HorseDriver_ULN2003(const Pin pins[4])
    : HorseDriver()
    , _state(Stop)
    , _progress(0.0f)
    , _stepper(Globals::Motor::StepsPerRev, pins[0], pins[1], pins[2], pins[3])
{
}

void HorseDriver_ULN2003::init()
{

}

void HorseDriver_ULN2003::loopCall(float const progress)
{
    // Move the stepper if enabled
    if(_state != Stop)
    {
        if(_state == Forward)
        {
            _stepper.step(progress);
        }
        else if(_state == Reverse)
        {
            _stepper.step(-progress);
        }
    }
    _progress += progress;
}

void HorseDriver_ULN2003::setVelocity(float const velocity)
{
    auto factor = constrain(velocity, Globals::Horse::MinVelocity, Globals::Horse::MaxVelocity) / Globals::Horse::MaxVelocity;
    _stepper.setSpeed(Globals::Motor::MaxRpm * factor);
}

void HorseDriver_ULN2003::forward()
{
    _state = Forward;
}

void HorseDriver_ULN2003::reverse()
{
    _state = Reverse;
}

void HorseDriver_ULN2003::stop()
{
    _state = Stop;
}

float HorseDriver_ULN2003::getProgress()
{
    return _progress;
}

void HorseDriver_ULN2003::resetProgress()
{
    _progress = 0.0f;
}