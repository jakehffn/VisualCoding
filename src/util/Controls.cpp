#include <SDL.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdio.h>
#include <iostream>

#include "controls.hpp"
#include "consts.h"

Controls::Controls(SDL_Window* window) {

    printf("initialized controls\n");

    this->window = window;

    inputList = new bool[6]{0};

    position = glm::vec3( -5, 0, 5 );
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 90.0f;

    speed = 3.0f;
    mouseSpeed = 0.001f;

    lastTime = SDL_GetTicks();
	currentTime = SDL_GetTicks();
    deltaTime = 0.0f;
}

glm::mat4 Controls::getViewMatrix(){
	return viewMatrix;
}
glm::mat4 Controls::getProjectionMatrix(){
	return projectionMatrix;
}

bool Controls::update(){

	currentTime = SDL_GetTicks();
    // Change in time since last frame
	deltaTime = float(currentTime - lastTime)/1000.0f;

    getInputs();
    applyInputs();

	lastTime = currentTime;

    return quit;
}

void Controls::getInputs() {

    SDL_GetMouseState(&xpos, &ypos);

    // Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
        
        if( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {

            quit = true;

        } else if( e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            
            bool isDown = (e.type == SDL_KEYDOWN);

            switch ( e.key.keysym.sym )
            {
            case SDLK_w:
                inputList[Inputs::FORWARD] = isDown;
                break;
            case SDLK_s:
                inputList[Inputs::BACKWARD] = isDown;
                break;
            case SDLK_a:
                inputList[Inputs::LEFT] = isDown;
                break;
            case SDLK_d:
                inputList[Inputs::RIGHT] = isDown;
                break;
            case SDLK_SPACE:
                inputList[Inputs::UP] = isDown;
                break;
            case SDLK_LSHIFT:
                inputList[Inputs::DOWN] = isDown;
                break;
            default:
                break;
            }
        } 
    }
}

void Controls::applyInputs() {

    // Reset mouse position for next frame
	SDL_WarpMouseInWindow(window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(render_consts::SCREEN_WIDTH/2 - xpos);
	verticalAngle += mouseSpeed * float(render_consts::SCREEN_HEIGHT/2 - ypos);

	// Vector that points out of camera
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

    glm::vec3 forward = glm::vec3(
        sin(horizontalAngle),
        0,
        cos(horizontalAngle)
    );
	
	// Vector which points to the right
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

    // Move forward
    if (inputList[Inputs::FORWARD]) {
        position += forward * deltaTime * speed;
    }
    // Move backward
    if (inputList[Inputs::BACKWARD]) {
        position -= forward * deltaTime * speed;
    }
    // Strafe left
    if (inputList[Inputs::LEFT]) {
        position -= right * deltaTime * speed;
    }
    // Strafe right
    if (inputList[Inputs::RIGHT]) {
        position += right * deltaTime * speed;
    }
    // Move up
    if (inputList[Inputs::UP]) {
        position += glm::vec3(0, 1, 0) * deltaTime * speed;
    }
    // Move down
    if (inputList[Inputs::DOWN]) {
        position -= glm::vec3(0, 1, 0) * deltaTime * speed;
    }

	float FoV = initialFoV;

	this->projectionMatrix = glm::perspective(glm::radians(FoV), float(render_consts::SCREEN_WIDTH)/float(render_consts::SCREEN_HEIGHT), 0.1f, 100.0f);

	this->viewMatrix = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);
}