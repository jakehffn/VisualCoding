#pragma once

// GLEW must come before OpenGL
#include <GL\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include "Shader.h"

class ShaderProgram {
public:
    virtual GLuint getOpenGLShaderProgramID() = 0;
    virtual void renderSetup(glm::mat4 model, glm::mat4 view, glm::mat4 projection) = 0;
};