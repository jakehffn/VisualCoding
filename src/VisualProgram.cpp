#include "VisualProgram.h"


VisualProgram::VisualProgram(SDL_Window* window, bool render) :
    window{ window }, clock{ new Clock() }, input{ new Input() } {

        cameraController = new UserCameraController(this->window, this->clock, this->input);
        scene = new Scene(this->window, this->clock, this->input, this->cameraController);
        
        // Enable text input
        SDL_StartTextInput();

}