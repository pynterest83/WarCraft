#pragma once

#include <SDL.h>
#include "rendergame.h"

class Timer {
public:
    Timer();
    ~Timer();
    
    //check started or paused
    bool Started;
    bool Paused;

    // get start time and current time
    Uint32 StartTime;
    Uint32 GetTime();

    // get time when paused
    float TimeWhenPaused;

    // start, pause, unpause, reset
    void Start();
    void Pause();
    void Unpause();
    void Reset();
};
