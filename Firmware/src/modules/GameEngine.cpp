// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/GameEngine.h>

GameEngine::GameEngine()
    : _state(Stopped)
    , _horses()
    , _horseStartFlags{ false }
    , _horseTriggerDebouce{ 0 }
    , _lastVelChange()
{
    for(HorseIdx idx = 0; idx < Globals::GameControl::nHorses; ++idx)
    {
        _horses[idx] = new HorseDriver_ULN2003(
            Globals::Motor::MotorPins[idx],
            Globals::Motor::MotorDirections[idx]
            );
    }
}

void GameEngine::reset()
{
    Serial.println("Resetting game!");
    for(auto& horse : _horses)
    {
        horse->setVelocity(Globals::Horse::MaxVelocity);
        horse->reverse();
    }
    for(HorseIdx idx = 0; idx < Globals::GameControl::nHorses; ++idx) _horseStartFlags[idx] = false;                                                       
    _state = Resetting;
}

void GameEngine::start()
{
    Serial.println("Starting new game!");
    for(auto& horse : _horses)
    {
        horse->forward();
    }
    _state = Started;
}

void GameEngine::stop()
{
    Serial.println("Game stopped!");
    for(auto& horse : _horses)
    {
        horse->stop();
    }
    _state = Stopped;
}

void GameEngine::loopCall()
{
    if(
            _state == Started
        &&  millis() > ( _lastVelChange + Globals::GameControl::VelocityChangeInterval )
    )
    {
        _lastVelChange = millis();

        Serial.println("Reevaluating velocity ...");

        for(HorseIdx horse = 0; horse < Globals::GameControl::nHorses; ++horse)
        {

            float velocity;
            // If reversing set velocity to max
            if(_state == Resetting) velocity = Globals::Horse::MaxVelocity;
            // If in game, set velocity randomly
            else velocity = random(Globals::Horse::MinVelocity * 1000.0f, Globals::Horse::MaxVelocity * 1000.0f) / 1000.0f;

            Serial.println("Horse: " + String(horse) + "\tV: " + String(velocity));
            _horses[horse]->setVelocity(velocity);
        }
    }

    // Move horse
    for(HorseIdx horse = 0; horse < Globals::GameControl::nHorses; ++horse)
    {
        _horses[horse]->loopCall();
    }
}

void GameEngine::triggerHorse(HorseIdx horse)
{
    if(millis() - _horseTriggerDebouce[horse] < Globals::GameControl::Debounce) return;
    else _horseTriggerDebouce[horse] = millis();


    Serial.println("Horse " + String(horse) + " triggered.");

    if(_state == Resetting && _horseStartFlags[horse] == false)
    {
        // If resetting, mark the horse at starting gate
        // Then move it a bit forward, to clear the start trigger
        // Finally disable the horse

        _horseStartFlags[horse] = true;
        _horses[horse]->forward();

        // Move forward for StartOffset milliseconds
        auto end = millis() + Globals::Horse::StartOffset;
        while(millis() < end) _horses[horse]->loopCall();

        _horses[horse]->stop();

        bool allReady = true; // Are all horses ready?
        for(auto& flag : _horseStartFlags)
        {
            if(!flag) allReady = false;
        }

        // Then set the game to stopped
        if(allReady)
        {
            for(auto& flag : _horseStartFlags) flag = false;
            _state = Stopped;
        }
    }

    else if(_state == Started)
    {
        // If game is started, stop it, because horse has just
        // won the race.
        stop();
    }
}

void GameEngine::setGameSpeed(float speed)
{
    if(_state != Resetting)
    {
        speed = Globals::Horse::MinVelocity +
                ( Globals::Horse::MaxVelocity - Globals::Horse::MinVelocity ) * speed;

        for(auto& horse : _horses)
        {
            horse->setVelocity(speed);
        }
    }
}