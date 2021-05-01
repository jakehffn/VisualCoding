#include "Input.h"

Input::Input() :
    keyInputs{ std::unordered_set<SDL_Keycode>() },
    toggleInputs{ std::unordered_set<SDL_Keycode>() },
    abridgedInputs{ std::unordered_set<SDL_Keycode>() },
    mouseX{ 0 }, mouseY{ 0 }, quit{ false }{}

void Input::update() {

    SDL_GetMouseState(&this->mouseX, &this->mouseY);

    for(auto abridgedInput : abridgedInputs) {
        keyInputs.erase(abridgedInput);
    }

    // Handle events on queue
    while(SDL_PollEvent( &e ) != 0) {
        
        if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {

            this->quit = true;

        } else if(e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            
            int isDown = (int)(e.type == SDL_KEYDOWN);

            SDL_Keycode currKey = e.key.keysym.sym;

            if(toggleInputs.count(currKey) == 1 && isDown) {

                if (keyInputs.count(currKey) == 1) {

                    keyInputs.erase(currKey);
                } else {
                    keyInputs.insert(currKey);
                }

            } else {

                if(isDown) {
                    keyInputs.insert(currKey);
                } else {
                    keyInputs.erase(currKey);
                }

            }
            

        } 
    }

}

void Input::setToggle(SDL_Keycode key) {

    assert(this->abridgedInputs.count(key) == 0);

    this->toggleInputs.insert(key);
}

void Input::setAbridge(SDL_Keycode key) {

    assert(this->toggleInputs.count(key) == 0);

    this->abridgedInputs.insert(key);
}

bool Input::isKeyDown(SDL_Keycode key) {
    return (this->keyInputs.count(key));
} 

int Input::getMouseX() {
    return this->mouseX;
}

int Input::getMouseY() {
    return this->mouseY;
}

bool Input::quitProgram() {
    return quit;
}