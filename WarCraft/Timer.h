#pragma once

#include <SDL.h>
#include "rendergame.h"

class Timer
{
public:
    bool Started;
    bool Paused;
    Uint32 StartTime;
    Uint32 PauseTime;
    Uint32 GetTime();
    float TimeWhenPaused;
    void Start();
    void Pause();
    void Unpause();
    void Reset();
    Timer();
    ~Timer();
};
