#include "UserCameraController.h"

UserCameraController::UserCameraController(SDL_Window* window, Clock* clock, Input* input) {

    this->clock = clock;
    this->window = window;

    this->input = input;

    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
}

void UserCameraController::update(glm::vec3& pos, glm::vec3& dir, glm::vec3& right) {

    // Reset mouse position for next frame
	SDL_WarpMouseInWindow(this->window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);

    float deltaTime = (float)clock->getDeltaTime();
    int* inputList = input->getInputs();

    int xPos = inputList[input_consts::XPOS];
    int yPos = inputList[input_consts::YPOS];

    // Compute new orientation
	horizontalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_WIDTH/2 - xPos);
	verticalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_HEIGHT/2 - yPos);

	// Vector that points out of camera
	dir = glm::vec3(
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
	right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
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