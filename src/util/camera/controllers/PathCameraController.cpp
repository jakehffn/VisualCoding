#include "PathCameraController.h"

PathCameraController::PathCameraController(SDL_Window* window, Clock* clock) {
	this->window = window;
	this->clock = clock;

	timePassed = 0;
	verticalAngle = 0;
	horizontalAngle = 0;
}

void PathCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {

	float deltaTime = clock->getDeltaTime();
	timePassed += deltaTime*0.001f;

	glm::vec3 circleCenter(0, 0, 0);
	float circleRadius = 10.0f;
	float viewingLoft = 5;

	float loftAngle = -atan(viewingLoft/circleRadius);

	verticalAngle = loftAngle;

	pos = circleRadius * glm::vec3(sin(timePassed), 0.0f, cos(timePassed));

	pos += glm::vec3 (circleCenter.x, circleCenter.y + viewingLoft, circleCenter.z);

	horizontalAngle = timePassed + 3.14f;

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