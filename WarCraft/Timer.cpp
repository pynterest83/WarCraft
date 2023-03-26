#include "Timer.h"

using namespace std;
Timer::Timer()
{
    Started = false;
    Paused = false;
    TimeWhenPaused = 0;
    StartTime = 0;
    PauseTime = 0;
}
Timer::~Timer() {};
void Timer::Start()
{
    Started = true;
    Paused = false;
    StartTime = SDL_GetTicks();
    PauseTime = 0;
}
void Timer::Reset()
{
    Started = false;
    Paused = false;
    StartTime = 0;
    PauseTime = 0;
}
void Timer::Pause()
{
    if (Started && !Paused)
    {
        Paused = true;
        TimeWhenPaused = SDL_GetTicks() - StartTime;
        StartTime = 0;
    }
}
void Timer::Unpause()
{
    if (Started && Paused)
    {
        Paused = false;
        StartTime = SDL_GetTicks() - TimeWhenPaused;
        PauseTime = 0;
    }
}
Uint32 Timer::GetTime()
{
    if (Started)
    {
        if (Paused) return TimeWhenPaused;
        else return SDL_GetTicks() - StartTime;
    }
    return 0;
}