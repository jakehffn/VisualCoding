#include "Input.h"

int* Input::getInputs() {
    
    SDL_GetMouseState(&inputs[input_consts::XPOS], &inputs[input_consts::YPOS]);

    // Handle events on queue
    while(SDL_PollEvent( &e ) != 0) {
        
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {

            this->quit = true;

        } else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            
            int isDown = (int)(e.type == SDL_KEYDOWN);

            switch (e.key.keysym.sym) {
                case SDLK_w:
                    inputs[input_consts::FORWARD] = isDown;
                    break;
                case SDLK_s:
                    inputs[input_consts::BACKWARD] = isDown;
                    break;
                case SDLK_a:
                    inputs[input_consts::LEFT] = isDown;
                    break;
                case SDLK_d:
                    inputs[input_consts::RIGHT] = isDown;
                    break;
                case SDLK_SPACE:
                    inputs[input_consts::UP] = isDown;
                    break;
                case SDLK_LSHIFT:
                    inputs[input_consts::DOWN] = isDown;
                    break;
                default:
                    break;
            }
        } 
    }

    return inputs;
} 

bool Input::quitProgram() {
    return quit;
}