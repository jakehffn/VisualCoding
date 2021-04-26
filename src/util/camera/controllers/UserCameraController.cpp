#include "UserCameraController.h"

UserCameraController::UserCameraController(SDL_Window* window, Clock* clock, Input* input) :
    clock{ clock }, window{ window }, input{ input } {

    SDL_ShowCursor(SDL_DISABLE);

    SDL_WarpMouseInWindow(this->window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);
    input->update();
}

void UserCameraController::update(glm::vec3& pos, float& horizontalAngle, float& verticalAngle) {

    // Reset mouse position for next frame
    // This allows measuring mouse movement while keeping mouse centered
	SDL_WarpMouseInWindow(this->window, render_consts::SCREEN_WIDTH/2, render_consts::SCREEN_HEIGHT/2);

    int* inputList = input->getInputs();

    updateAngles(horizontalAngle, verticalAngle);

    glm::vec3 forward = computeForward(horizontalAngle, verticalAngle);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::cross(forward, up);
	
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
        pos += up * deltaTime * input_consts::KEY_SPEED;
    }
    // Move down
    if (inputList[input_consts::DOWN]) {
        pos -= up * deltaTime * input_consts::KEY_SPEED;
    }
}

void UserCameraController::updateAngles(float& horizontalAngle, float& verticalAngle) {

    int* inputList = input->getInputs();

    // Compute new orientation
	horizontalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_WIDTH/2 - inputList[input_consts::XPOS]);
	verticalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_HEIGHT/2 - inputList[input_consts::YPOS]);

    // Avoids backwards camera from the top
    if (verticalAngle > 3.14/2) {
        verticalAngle = 3.14/2;
    }
    // Avoids backwards camera from the bottom
    if (verticalAngle < -3.14/2) {
        verticalAngle = -3.14/2;
    }
}

glm::vec3 UserCameraController::computeForward(float horizontalAngle, float verticalAngle) {
    // Vector which points forward
    return glm::vec3(
        sin(horizontalAngle),
        0,
        cos(horizontalAngle)
    );
}