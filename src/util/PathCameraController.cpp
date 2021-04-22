#include "PathCameraController.h"

PathCameraController::PathCameraController(SDL_Window* window, Clock* clock) {
    this->window = window;
    this->clock = clock;

    timePassed = 0;
}

void PathCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {
    
    float deltaTime = clock->getDeltaTime();
    timePassed += deltaTime*0.001f;

    float circleSize = 10.0f;
    float xOffset = 0.0f;
    float yOffset = 5.0f;
    float zOffset = -15.0f;

    pos = circleSize * glm::vec3(
        sin(timePassed), 0.0f, cos(timePassed)
    ) + glm::vec3 (xOffset, yOffset , zOffset);

    dir = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

    right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
}