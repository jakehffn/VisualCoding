#pragma once

#include "VisualProgram.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "consts.h"

#include "CirclePath.h"
#include "LinePath.h"
#include "BasicShader.h"

#include "PathCameraController.h"

class MultipleObjects : public VisualProgram {
public:
    MultipleObjects(SDL_Window* window, bool renderParam);
    ~MultipleObjects();
    void init();
    void run();
};