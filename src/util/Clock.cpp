#include "Clock.h"
#include <iostream>

Clock::Clock(bool constantTime=false) :
    currentFrame{ SDL_GetPerformanceCounter() }, 
    lastFrame{ 0 }, deltaTime{ 0 }, cumulativeTime{ 0 },
    constantTime{ constantTime } {

        if (constantTime) {
            deltaTime = 1.0 / render_consts::SCREEN_FPS;
        }
}

double Clock::tick() {
    
    if (constantTime) {

        this->lastFrame = currentFrame;
        this->currentFrame = SDL_GetPerformanceCounter();

        double realDelta = (double)((currentFrame - lastFrame) / (double)SDL_GetPerformanceFrequency());
        
        this->previousFPS = FPS;
        this->FPS = 1.0/realDelta;

        this->cumulativeTime += this->deltaTime;

    } else {

        this->lastFrame = currentFrame;
        this->currentFrame = SDL_GetPerformanceCounter();

        this->deltaTime = (double)((currentFrame - lastFrame) / (double)SDL_GetPerformanceFrequency());
        this->cumulativeTime += deltaTime;

        this->previousFPS = FPS;
        this->FPS = 1.0/deltaTime;
    }

    return deltaTime;
}

double Clock::getDeltaTime() {
    return deltaTime;
}

double Clock::getCumulativeTime() {
    return cumulativeTime;
}

double Clock::getFPS() {
    return this->FPS;
}

double Clock::getAverageFPS() {
    return (this->FPS+this->previousFPS)/2.0;
}