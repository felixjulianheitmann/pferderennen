// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/HorseDriver_ULN2003.h>
#include <config/globals.h>
#include <Stepper.h>

// Maps a floating point value
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

HorseDriver_ULN2003::HorseDriver_ULN2003(const Pin pins[4], bool const dir)
    : HorseDriver()
    , _state(Stop)
    , _velocity(0.0f)
    , _dir(dir)
    , _pins{ pins[0], pins[1], pins[2], pins[3] }
    , _step(0)
    , _lastStepTime(0)
{
}

void HorseDriver_ULN2003::init()
{

}

void HorseDriver_ULN2003::loopCall()
{
    // Move the stepper if enabled
    if(_state != Stop)
    {
        if(_state == Forward)
        {
            step(_dir ? true : false);
        }
        else if(_state == Reverse)
        {
            step(_dir ? false : true);
        }
    }
}

void HorseDriver_ULN2003::setVelocity(float velocity)
{
    _velocity = velocity;
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

void HorseDriver_ULN2003::step(bool const dir)
{

    // Execute only when the interval is exceeded.
    // This gives a velocity defined behaviour
    // Serial.println("V: " + String(_velocity));
    if(micros() - _lastStepTime < ( Globals::Motor::Delay / _velocity )) return;
    _lastStepTime = micros();

    // increment or decrement step in range 0 - 4
    if(dir) _step = ( _step + 1 ) % 4;
    else --_step;
    if(_step == -1) _step = 3;


    /* Stepping order
    * Step C0 C1 C2 C3 (A, A*, B, B*)
    *    1  1  0  1  0
    *    2  0  1  1  0
    *    3  0  1  0  1
    *    4  1  0  0  1
    */
    switch(_step)
    {
    case 0: // 1010
        digitalWrite(_pins[0], HIGH);
        digitalWrite(_pins[1], LOW);
        digitalWrite(_pins[2], HIGH);
        digitalWrite(_pins[3], LOW);
        break;
    case 1: // 0110
        digitalWrite(_pins[0], LOW);
        digitalWrite(_pins[1], HIGH);
        digitalWrite(_pins[2], HIGH);
        digitalWrite(_pins[3], LOW);
        break;
    case 2: // 0101
        digitalWrite(_pins[0], LOW);
        digitalWrite(_pins[1], HIGH);
        digitalWrite(_pins[2], LOW);
        digitalWrite(_pins[3], HIGH);
        break;
    case 3: // 1001
        digitalWrite(_pins[0], HIGH);
        digitalWrite(_pins[1], LOW);
        digitalWrite(_pins[2], LOW);
        digitalWrite(_pins[3], HIGH);
        break;
    }

}