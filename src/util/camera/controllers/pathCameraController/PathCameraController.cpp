#include "PathCameraController.h"

PathCameraController::PathCameraController(Clock* clock, Path* path) :
	clock{ clock }, path{ path } {}

void PathCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {
	path->update(pos, dir, right, clock->getCumulativeTime());
}