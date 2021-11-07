#pragma once

#include "VisualProgram.h"
#include "Scene.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "UserCameraController.h"
#include "Clock.h"
#include "CirclePath.h"
#include "LinePath.h"
#include "InstancedShader.h"

#include "UserCameraController.h"
#include "PathCameraController.h"

class MathVisualizer : public VisualProgram {
public:
    ~MathVisualizer();
    void init(SDL_Window* window);
    void run();
    
private:
    void createBlockArray(int width, int length);
    void modifyBlockArray(int width, int length);

    float twoDimSine(float time, int xx, int yy);
    float threeDimSine(float time, int xx, int yy);
    float threeDimTangent(float time, int xx, int yy);

    GLuint programID = 0;
    SDL_Window* window = NULL;

    Clock* clock;
    Input* input;
    Scene* scene;

    CameraController* cameraController;
};