#include "PathCameraController.h"

PathCameraController::PathCameraController(SDL_Window* window, Clock* clock, Path* path) {
	this->window = window;
	this->clock = clock;
	this->path = path;
}

void PathCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {
	path->update(pos, dir, right, clock->getCumulativeTime());
}