#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

// GLEW must come before OpenGL
#include <gl\glew.h>
#include <SDL.h>

#include "consts.h"
#include "VisualProgram.h"

#include "OpenGLTutorial.h"
#include "MultipleObjects.h"

bool init();
void eventHandler();
void close();

SDL_Window* window = NULL;
SDL_GLContext gContext;
VisualProgram* program;

// Initializes SDL, GLEW, then OpenGL
bool init() {
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;

	} else {
		// Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		window = SDL_CreateWindow("visualCoding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			render_consts::SCREEN_WIDTH, render_consts::SCREEN_HEIGHT, 
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_INPUT_FOCUS
		);

		if(window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;

		} else {
			gContext = SDL_GL_CreateContext(window);

			if(gContext == NULL) {
				printf("SDL: OpenGL context could not be created!\nSDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				glewExperimental = GL_TRUE; 
				GLenum glewError = glewInit();
				if( glewError != GLEW_OK ) {
					printf("GLEW: Error initializing! %s\n", glewGetErrorString(glewError));
				}

				// Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
					printf( "SDL: Warning: Unable to set VSync!\nSDL Error: %s\n", SDL_GetError() );
				}

				if( !program->init(window) ) {
					printf( "Unable to init program!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

void close() {

	// Destroy window	
	SDL_DestroyWindow(window);
	window = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

void applyProgram(std::string input) {

	if (input == "OpenGLTutorial") {
		program = new OpenGLTutorial();
	} 

	if (input == "MultipleObjects") {
		program = new MultipleObjects();
	}

}

// Parameters necessary for SDL_Main
int main(int argv, char** args) {

	std::string input;

	if (argv == 1) {
		input = std::string("OpenGLTutorial");
	} else {
		input = std::string(args[1]);
	}

	applyProgram(input);

	// Start up SDL and create window
	if(!init()) {
		
		printf("Failed to initialize!\n");

	} else {
		// SDL_SetWindowGrab(window, SDL_TRUE);
		// SDL_SetWindowInputFocus(window);
		program->run();
	}

	close();

	return 0;
}