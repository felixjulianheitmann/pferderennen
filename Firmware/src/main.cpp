// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#include <Arduino.h>
#include <config/globals.h>
#include <modules/GameEngine.h>

// ##########################################################
// ### Function Prototypes
// ##########################################################
void IsrFinish();
void IsrStart();
bool startButtonPressed();
bool resetButtonPressed();

// ##########################################################
// ### Initialize program variables
// ##########################################################

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
    game.reset();

}


// ##########################################################
// ### Program loop
// ##########################################################
void loop() {

    if(startButtonPressed()) game.start();  // If start button is pressed, start the game
    if(resetButtonPressed()) game.reset();  // If reset button is pressed, reset the game

    // iterative call to driver to trigger periodic behaviour
    game.loopCall();

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
    for(HorseIdx i = 0; i < Globals::GameControl::nHorses; ++i)
    {
        if(digitalRead(Globals::GameControl::horseStartTriggers[i]) == LOW)
        {
            horseStartFlags[i] = true;
            return;
        }
    }
}

bool lastStartButtonState = false;
bool startButtonPressed()
{
    bool buttonPressed = ( lastStartButtonState == false && digitalRead(Globals::GameControl::StartButton) );
    lastStartButtonState = digitalRead(Globals::GameControl::StartButton);
    return buttonPressed;
}

bool lastResetButtonState = false;
bool startButtonPressed()
{
    bool buttonPressed = ( lastResetButtonState == false && digitalRead(Globals::GameControl::ResetButton) );
    lastResetButtonState = digitalRead(Globals::GameControl::ResetButton);
    return buttonPressed;
}