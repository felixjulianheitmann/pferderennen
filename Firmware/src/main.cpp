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
bool startButtonPressed();
bool resetButtonPressed();
bool horseTriggered(HorseIdx idx);
void setPinModes();


// ##########################################################
// ### Initialize program variables
// ##########################################################

auto game  = GameEngine();

bool lastStartButtonState = true;
bool lastResetButtonState = true;
bool lastTriggerState[Globals::GameControl::nHorses] = { true };

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

    // +++ Reset Horses to start
    game.reset();

    Serial.println("# Enter loop ...");

}



// ##########################################################
// ### Program loop
// ##########################################################
void loop() {

    if(startButtonPressed()) game.start();  // If start button is pressed, start the game
    if(resetButtonPressed()) game.reset();  // If reset button is pressed, reset the game
    for(unsigned int idx = 0; idx < Globals::GameControl::nHorses; ++idx)
        if(horseTriggered(idx)) game.triggerHorse(idx);

    // // set rpm according to potentiometer
    // auto input = analogRead(Globals::GameControl::VelocityPotentiometer) / 1023.0f;
    // game.setGameSpeed(input);
    // game.setGameSpeed(1.0f);

    // iterative call to driver to trigger periodic behaviour
    game.loopCall();

}



// ##########################################################
// ### Function Definitions
// ##########################################################
bool startButtonPressed()
{
    // randomSeed(micros());
    bool buttonPressed = ( lastStartButtonState == true && digitalRead(Globals::GameControl::StartButton) == false );
    lastStartButtonState = digitalRead(Globals::GameControl::StartButton);
    return buttonPressed;
}

bool resetButtonPressed()
{
    bool buttonPressed = ( lastResetButtonState == true && digitalRead(Globals::GameControl::ResetButton) == false );
    lastResetButtonState = digitalRead(Globals::GameControl::ResetButton);
    return buttonPressed;
}

bool horseTriggered(HorseIdx idx) 
{
    bool now = (digitalRead(Globals::GameControl::horseTriggers[idx]));
    bool triggered = ( lastTriggerState[idx] == true && now == false );
    lastTriggerState[idx] = now;
    return triggered;
}

void setPinModes()
{
    pinMode(Globals::GameControl::StartButton, INPUT_PULLUP);
    pinMode(Globals::GameControl::ResetButton, INPUT_PULLUP);
    pinMode(Globals::GameControl::VelocityPotentiometer, INPUT);

    for(auto& pin : Globals::GameControl::horseTriggers)
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