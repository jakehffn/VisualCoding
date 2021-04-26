#include "Camera.h"

Camera::Camera(CameraController* controller) :
    controller{ controller }, controllers{ std::vector<CameraController*>{controller} },
	controllerPosition{ 0 },
    position{ glm::vec3(0, 0, 5) }, viewMatrix{ glm::mat4(1) }, 
    horizontalAngle{ 3.14f }, verticalAngle{ 0.0f } {

    float FoV = 90.0f;

    this->projectionMatrix = glm::perspective(glm::radians(FoV), float(render_consts::SCREEN_WIDTH)/float(render_consts::SCREEN_HEIGHT), 0.1f, 100.0f);
}

glm::mat4 Camera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
    return projectionMatrix;
}

// !Remove from Camera class eventually!
void Camera::addController(CameraController* controller) {
	this->controllers.push_back(controller);
}

void Camera::setController(int pos) {

	assert(pos < controllers.size());

	this->controllerPosition = pos;
    this->controller = controllers.at(pos);
}

// !Remove from Camera class eventually!
void Camera::nextController() {

	controllerPosition++;

	if (controllerPosition == controllers.size()) {
		controllerPosition = 0;
	}

	setController(controllerPosition);
}

void Camera::update() {

    controller->update(this->position, this->horizontalAngle, this->verticalAngle);

    glm::vec3 dir = this->computeDir();

	this->viewMatrix = glm::lookAt(
		position,           // Camera is here
		position + dir, // and looks here : at the same position, plus "direction"
		glm::cross(this->computeRight(), dir) // Head is up (set to 0,-1,0 to look upside-down)
	);
}

glm::vec3 Camera::computeDir() {
    // Vector that points out of camera
	return glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
}

glm::vec3 Camera::computeRight() {
    // Vector which points to the right
    return glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
}


