#include "Clock.h"

Clock::Clock() :
    currentFrame{ SDL_GetPerformanceCounter() }, 
    lastFrame{ 0 }, deltaTime{ 0 }, cumulativeTime{ 0 } {}

double Clock::tick() {
    
    lastFrame = currentFrame;
    currentFrame = SDL_GetPerformanceCounter();

    deltaTime = (double)((currentFrame - lastFrame)*1000 / (double)SDL_GetPerformanceFrequency());
    cumulativeTime += deltaTime;

    return deltaTime;
}

double Clock::getDeltaTime() {
    return deltaTime;
}

double Clock::getCumulativeTime() {
    return cumulativeTime;
}