// ######################################################
// Author: Felix Heitmann (felixjulianheitmann@gmail.com)
// Creation date: 22.05.2021
// ######################################################

#pragma once

typedef unsigned int Pin;

namespace Globals {

    namespace GameControl {

        constexpr Pin IntStart =            2;          // Interrupt Pin for the start line trigger
        constexpr Pin IntFinish =           3;          // Interrupt Pin for the finish line trigger

        constexpr unsigned int nHorses =    2;          // The number of horses in the race
        constexpr Pin horseStartTriggers[nHorses] =     // The trigger pins to check whether a horse is at the starting gate 
        {
            12,
            13,
        };
    }

    namespace Horse {

        constexpr float MinVelocity =   0.0f;       // The minimum velocity value that can be set for a horse
        constexpr float MaxVelocity =   100.0f;     // The maximium velocity value that can be set for a horse

    }

}