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

        constexpr Pin StartButton       = 2;
        constexpr Pin ResetButton       = 4;
        constexpr unsigned long Debounce = 50; // Trigger debounce in ms
        constexpr unsigned int nHorses =    3;          // The number of horses in the race
        constexpr Pin horseTriggers[nHorses] =     // The trigger pins to check whether a horse is at the starting gate - connected to horses
        {
            5,
            7,  
            8,
        };

        constexpr Pin VelocityPotentiometer = A6;   // A potentiometer to control game velocity

        constexpr unsigned int VelocityChangeInterval = 500; // The interval after which the velocity of horses is reevaluated

    }

    namespace Horse {

        constexpr float MinVelocity =   0.10f;       // The minimum velocity value that can be set for a horse - in respect to MaxVelocity
        constexpr float MaxVelocity =   1.00f;     // The maximium velocity value that can be set for a horse - 1 equals full speed

        constexpr unsigned int StartOffset = 1000; // Offset to the starting gate before race

    }

    namespace Motor {

        constexpr unsigned long Delay        = 3000;   // The maximum revolution per minute of the motor

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
                3,
            },

        };

        // A switch to invert the direction of each motor
        constexpr bool MotorDirections[GameControl::nHorses] = {
            false,
            false,
            false,
        };

    }

}