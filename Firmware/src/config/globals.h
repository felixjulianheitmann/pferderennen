// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#pragma once

#include <Arduino.h>

typedef int Pin;   // Typedef for a hardware pin
typedef size_t HorseIdx;       // Typedef for a horse index

namespace Globals {


    namespace GameControl {

        constexpr Pin IntStart          = 2;          // Interrupt Pin for the start line trigger
        constexpr Pin IntFinish         = 3;          // Interrupt Pin for the finish line trigger

        constexpr Pin StartButton       = 4;
        constexpr Pin ResetButton       = 5;

        constexpr unsigned int nHorses =    3;          // The number of horses in the race
        constexpr Pin horseStartTriggers[nHorses] =     // The trigger pins to check whether a horse is at the starting gate 
        {
            6,
            7,
            8,
        };

        constexpr Pin VelocityPotentiometer = A7;   // A potentiometer to control game velocity
    }

    namespace Horse {

        constexpr float MinVelocity =   0.0f;       // The minimum velocity value that can be set for a horse
        constexpr float MaxVelocity =   100.0f;     // The maximium velocity value that can be set for a horse

        constexpr unsigned int MinProgress = 10;    // The minimum progress a horse should make each loop
        constexpr unsigned int MaxProgress = 100;   // The maximum progress a horse should make each loop

        constexpr float ProgressOffset = 0.5;       // The initial offset from the starting trigger

    }

    namespace Motor {

        constexpr unsigned int StepsPerRev  = 4096; // The number of steps for one revolution of the stepper motor
        constexpr unsigned int MaxRpm       = 60;   // The maximum revolution per minute of the motor

        constexpr Pin MotorPins[GameControl::nHorses][4] = {    // The hardware pins associated with each horse
            {
                 9,
                10,
                11,
                12,
            },
            {
                13,
                A0,
                A1,
                A2,
            },
            {
                A3,
                A4,
                A5,
                A6,
            },

        };

        // A switch to invert the direction of each motor
        constexpr bool MotorDirections[GameControl::nHorses] = {
            true,
            true,
            true,
        };

    }

}