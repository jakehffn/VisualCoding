#pragma once

#include "glm/glm.hpp"


class Controls {
public:
    Controls(SDL_Window*);
    bool update();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
private:
    void getInputs();
    void applyInputs();

    enum Inputs {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    SDL_Window* window;
    SDL_Event e;

    bool quit = false;

    glm::vec3 position; 
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;

    float speed;
    float mouseSpeed;

    int currentTime;
    int lastTime;
    float deltaTime;

    int xpos, ypos;
    bool* inputList;
};
