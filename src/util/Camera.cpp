#include "Camera.h"

Camera::Camera(SDL_Window* window, CameraController* controller) {

    this->window = window;
    this->controller = controller;

    position = glm::vec3( 0, 0, 5 );
    float FoV = 90.0f;

    this->viewMatrix = glm::mat4(1);
    this->projectionMatrix = glm::perspective(glm::radians(FoV), float(render_consts::SCREEN_WIDTH)/float(render_consts::SCREEN_HEIGHT), 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

void Camera::update() {

    controller->update(this->position, this->direction, this->right);

	this->viewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		glm::cross(right, direction) // Head is up (set to 0,-1,0 to look upside-down)
	);
}

