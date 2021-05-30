// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/GameEngine.h>

GameEngine::GameEngine()
    : _state(Stopped)
    , _horses()
    , _horseStartFlags{ false }
{
}

void GameEngine::reset()
{
    for(auto& horse : _horses)
    {
        horse->setVelocity(Globals::Horse::MaxVelocity);
        horse->reverse();
    }
    _state = Resetting;
}

void GameEngine::start()
{
    for(auto& horse : _horses)
    {
        horse->resetProgress();
        horse->forward();
    }
    _state = Started;
}

void GameEngine::stop()
{
    for(auto& horse : _horses)
    {
        horse->stop();
    }
    _state = Started;
}

HorseIdx GameEngine::getWinner()
{
    HorseIdx winner = 0;
    float winnerProgress = 0.0f;

    for(HorseIdx idx = 0; idx < Globals::GameControl::nHorses; ++idx)
    {
        if(_horses[idx]->getProgress() > winnerProgress)
        {
            winner = idx;
            winnerProgress = _horses[idx]->getProgress();
        }
    }
    return winner;
}

void GameEngine::loopCall()
{
    for(HorseIdx horse = 0; horse < Globals::GameControl::nHorses; ++horse)
    {
        // Invert direction if config says so
        int dir = Globals::Motor::MotorDirections[horse] ? 1 : -1;

        _horses[horse]->loopCall(
            dir * random(Globals::Horse::MinProgress, Globals::Horse::MaxProgress)
        );
    }
}

void GameEngine::atStartingGate(HorseIdx horse)
{
    if(_state == Resetting)
    {
        // If resetting, mark the horse at starting gate
        // Then move it a bit forward, to clear the start trigger
        // Finally disable the horse
        _horseStartFlags[horse] = true;
        _horses[horse]->forward();
        _horses[horse]->loopCall(Globals::Horse::ProgressOffset);
        _horses[horse]->stop();

        bool allReady = true; // Are all horses ready?
        for(auto& flag : _horseStartFlags)
        {
            if(!flag) allReady = false;
        }

        // Then set the game to stopped
        if(allReady)
        {
            _state = Stopped;
        }

    }
}

void GameEngine::setGameSpeed(float speed)
{
    speed = Globals::Horse::MinVelocity + 
            ( Globals::Horse::MaxProgress - Globals::Horse::MinVelocity ) * speed;

    for(auto& horse : _horses)
    {
        horse->setVelocity(speed);
    }
}