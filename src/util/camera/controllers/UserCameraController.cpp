#include "UserCameraController.h"

UserCameraController::UserCameraController(SDL_Window* window, Clock* clock, Input* input) :
    clock{ clock }, window{ window }, input{ input },
    horizontalAngle{ 3.14f }, verticalAngle{ 0.0f } {

    SDL_ShowCursor(SDL_DISABLE);
    SDL_WarpMouseInWindow(this->window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);
}

void UserCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {

    // Reset mouse position for next frame
    // This allows measuring mouse movement while keeping mouse centered
	SDL_WarpMouseInWindow(this->window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);

    int* inputList = input->getInputs();

    computeAngles(inputList[input_consts::XPOS], inputList[input_consts::YPOS]);

    dir = computeDir();
    right = computeRight();
    glm::vec3 forward = computeForward();
	
    float deltaTime = (float)clock->getDeltaTime();

    // Move forward
    if (inputList[input_consts::FORWARD]) {
        pos += forward * deltaTime * input_consts::KEY_SPEED;
    }
    // Move backward
    if (inputList[input_consts::BACKWARD]) {
        pos -= forward * deltaTime * input_consts::KEY_SPEED;
    }
    // Strafe left
    if (inputList[input_consts::LEFT]) {
        pos -= right * deltaTime * input_consts::KEY_SPEED;
    }
    // Strafe right
    if (inputList[input_consts::RIGHT]) {
        pos += right * deltaTime * input_consts::KEY_SPEED;
    }
    // Move up
    if (inputList[input_consts::UP]) {
        pos += glm::vec3(0, 1, 0) * deltaTime * input_consts::KEY_SPEED;
    }
    // Move down
    if (inputList[input_consts::DOWN]) {
        pos -= glm::vec3(0, 1, 0) * deltaTime * input_consts::KEY_SPEED;
    }
}

void UserCameraController::computeAngles(int xPos, int yPos) {

    // Compute new orientation
	horizontalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_WIDTH/2 - xPos);
	verticalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_HEIGHT/2 - yPos);

    // Avoids backwards camera from the top
    if (verticalAngle > 3.14/2) {
        verticalAngle = 3.14/2;
    }
    // Avoids backwards camera from the bottom
    if (verticalAngle < -3.14/2) {
        verticalAngle = -3.14/2;
    }
}

glm::vec3 UserCameraController::computeDir() {
    // Vector that points out of camera
	return glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
}

glm::vec3 UserCameraController::computeRight() {
    // Vector which points to the right
    return glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
}

glm::vec3 UserCameraController::computeForward() {
    // Vector which points forward
    return glm::vec3(
        sin(horizontalAngle),
        0,
        cos(horizontalAngle)
    );
}