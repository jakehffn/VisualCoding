// From opengl-tutorials

#ifndef CONTROLS_HPP
#define CONTROLS_HPP

#include "glm/glm.hpp"

void setWindow(SDL_Window* gWindow);
bool computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif