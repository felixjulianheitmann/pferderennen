// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <Arduino.h>
#include <config/globals.h>
#include <modules/GameEngine.h>
#include <modules/HorseDriver_ULN2003.h>

// ##########################################################
// ### Interrupt Service Routines Prototypes
// ##########################################################
void IsrFinish();
void IsrStart();

// ##########################################################
// ### Initialize program variables
// ##########################################################

auto horse = HorseDriver_ULN2003();
auto game  = GameEngine();

// Flags to signalize whether a horse is at the starting gate. Reset at race start
volatile bool horseStartFlags[Globals::GameControl::nHorses] = { false };

// Flag to signalize to finish of a race. Reset at game start.
volatile bool finishFlag = false;

// ##########################################################
// ### Program setup
// ##########################################################
void setup() {

    Serial.begin(115200);
    Serial.println("########################################");
    Serial.println("# Welcome to the Horse track           #");
    Serial.println("########################################");

    Serial.println("# Setting up horse positions ... ");

    // +++ Register start and finish trigger interrupts
    attachInterrupt(digitalPinToInterrupt(Globals::GameControl::IntFinish), IsrFinish, FALLING);
    attachInterrupt(digitalPinToInterrupt(Globals::GameControl::IntStart),  IsrStart,  FALLING);

    // +++ Reset Horses to start
    horse.setVelocity(100.0f);
    horse.reverse();

}


// ##########################################################
// ### Program loop
// ##########################################################
void loop() {



    // iterative call to driver to trigger periodic behaviour
    horse.loopCall();

}


// ##########################################################
// ### ISR Definitions
// ##########################################################
void IsrFinish()
{
    finishFlag = true;
}

void IsrStart()
{
    for(size_t i = 0; i < Globals::GameControl::nHorses; ++i)
    {
        if(digitalRead(Globals::GameControl::horseStartTriggers[i]) == LOW)
        {
            horseStartFlags[i] = true;
            return;
        }
    }
}