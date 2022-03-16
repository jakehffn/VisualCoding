#pragma once

#include "VisualProgram.h"

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "CirclePath.h"
#include "LinePath.h"
#include "BasicShader.h"
#include "TopographicShader.h"

#include "PathCameraController.h"

class MathVisualizer : public VisualProgram {
public:
    MathVisualizer(SDL_Window* window, bool renderParam);
    ~MathVisualizer();
    void init();
    void run();
    
private:
    void createBlockArray(int width, int length);
    void modifyBlockArray(int width, int length);

    float twoDimSine(float time, int xx, int yy);
    float threeDimSine(float time, int xx, int yy);
    float threeDimTangent(float time, int xx, int yy);
};