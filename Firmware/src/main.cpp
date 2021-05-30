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
void setPinModes();


// ##########################################################
// ### Initialize program variables
// ##########################################################

auto game  = GameEngine();



// ##########################################################
// ### Program setup
// ##########################################################
void setup() {

    Serial.begin(115200);
    Serial.println("########################################");
    Serial.println("# Welcome to the Horse track           #");
    Serial.println("########################################");

    Serial.println("# Setting up horse positions ... ");

    // +++ Set pin modes
    setPinModes();

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

    // set rpm according to potentiometer
    auto input = analogRead(Globals::GameControl::VelocityPotentiometer) / 1023.0f;
    game.setGameSpeed(input);

    // iterative call to driver to trigger periodic behaviour
    game.loopCall();

}



// ##########################################################
// ### Function Definitions
// ##########################################################
void IsrFinish()
{
    game.stop();
}

void IsrStart()
{
    for(HorseIdx idx = 0; idx < Globals::GameControl::nHorses; ++idx)
    {
        if(digitalRead(Globals::GameControl::horseStartTriggers[idx]) == LOW)
        {
            game.atStartingGate(idx);
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
bool resetButtonPressed()
{
    bool buttonPressed = ( lastResetButtonState == false && digitalRead(Globals::GameControl::ResetButton) );
    lastResetButtonState = digitalRead(Globals::GameControl::ResetButton);
    return buttonPressed;
}

void setPinModes()
{
    pinMode(Globals::GameControl::IntStart, INPUT_PULLUP);
    pinMode(Globals::GameControl::IntFinish, INPUT_PULLUP);
    pinMode(Globals::GameControl::StartButton, INPUT_PULLUP);
    pinMode(Globals::GameControl::ResetButton, INPUT_PULLUP);
    pinMode(Globals::GameControl::VelocityPotentiometer, INPUT);

    for(auto& pin : Globals::GameControl::horseStartTriggers)
    {
        pinMode(pin, INPUT_PULLUP);
    }

    for(auto& pinSet : Globals::Motor::MotorPins)
    {
        for(auto& pin : pinSet)
        {
            pinMode(pin, OUTPUT);
        }
    }
}