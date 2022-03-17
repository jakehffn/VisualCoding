#pragma once

#include <iostream>

#include <SDL.h>

#include "consts.h"

class Clock {
public:
    Clock(bool constantTime);
    double getDeltaTime();
    double getCumulativeTime();
    double tick();
    double getFPS();
    double getAverageFPS();

private:
    Uint64 currentFrame;
    Uint64 lastFrame;

    double deltaTime;
    double cumulativeTime;
    double FPS = 0;
    double previousFPS = 0;

    bool constantTime;
};