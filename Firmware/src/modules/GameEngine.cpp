// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <modules/GameEngine.h>

GameEngine::GameEngine()
    : _horses()
{

}

void GameEngine::reset()
{
    for(auto& horse : _horses)
    {
        horse.reverse();
    }
}

void GameEngine::start()
{
    for(auto& horse : _horses)
    {
        horse.resetProgress();
        horse.forward();
    }
}

void GameEngine::stop()
{

}

HorseIdx GameEngine::getWinner()
{

}

void GameEngine::loopCall()
{

}
