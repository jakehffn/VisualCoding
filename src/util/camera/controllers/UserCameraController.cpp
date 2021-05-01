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

    updateAngles(horizontalAngle, verticalAngle);

    glm::vec3 forward = computeForward(horizontalAngle, verticalAngle);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::cross(forward, up);
	
    float deltaTime = (float)clock->getDeltaTime();

    // Move forward
    if (input->isKeyDown(SDLK_w)) {
        pos += forward * deltaTime * input_consts::KEY_SPEED;
    }
    // Move backward
    if (input->isKeyDown(SDLK_s)) {
        pos -= forward * deltaTime * input_consts::KEY_SPEED;
    }
    // Strafe left
    if (input->isKeyDown(SDLK_a)) {
        pos -= right * deltaTime * input_consts::KEY_SPEED;
    }
    // Strafe right
    if (input->isKeyDown(SDLK_d)) {
        pos += right * deltaTime * input_consts::KEY_SPEED;
    }
    // Move up
    if (input->isKeyDown(SDLK_SPACE)) {
        pos += up * deltaTime * input_consts::KEY_SPEED;
    }
    // Move down
    if (input->isKeyDown(SDLK_LSHIFT)) {
        pos -= up * deltaTime * input_consts::KEY_SPEED;
    }
}

void UserCameraController::updateAngles(float& horizontalAngle, float& verticalAngle) {

    // Compute new orientation
	horizontalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_WIDTH/2 - input->getMouseX());
	verticalAngle += input_consts::MOUSE_SPEED * float(render_consts::SCREEN_HEIGHT/2 - input->getMouseY());

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