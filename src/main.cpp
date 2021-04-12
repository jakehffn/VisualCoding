#include <stdio.h>
#include <iostream>
#include <string>

// GLEW must come before OpenGL
#include <gl\glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include "consts.h"
#include "ShaderLoader.h"
#include "Lin.h"

bool init();
bool initOpenGL();
void eventHandler();

void update();
void render();

void close();

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

bool gRenderQuad = true;

GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

// Initializes SDL, GLEW, then OpenGL
bool init() {
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;

	} else {
		// Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		gWindow = SDL_CreateWindow( "visualCoding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, render_consts::SCREEN_WIDTH, render_consts::SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;

		} else {
			gContext = SDL_GL_CreateContext( gWindow );

			if( gContext == NULL ) {
				printf( "SDL: OpenGL context could not be created!\nSDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				glewExperimental = GL_TRUE; 
				GLenum glewError = glewInit();
				if( glewError != GLEW_OK ) {
					printf( "GLEW: Error initializing! %s\n", glewGetErrorString( glewError ) );
				}

				// Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
					printf( "SDL: Warning: Unable to set VSync!\nSDL Error: %s\n", SDL_GetError() );
				}

				if( !initOpenGL() ) {
					printf( "OpenGl: Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

bool initOpenGL() {

	bool success = true;

	gProgramID = glCreateProgram();

	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	ShaderLoader shaderLoader = ShaderLoader(gProgramID, vertexShader, fragmentShader);

	std::string vertexPath = "./src/shaders/vertexShader.glsl";
	std::string fragmentPath = "./src/shaders/fragmentShader.glsl";

	if (!shaderLoader.loadShaders(vertexPath, fragmentPath)) {

		printf("Unable to load shaders %d!");
		success = false;

	} else {





		// Get vertex attribute location
		gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );

		if( gVertexPos2DLocation == -1 ) {
			printf( "LVertexPos2D is not a valid glsl program variable!\n" );
			success = false;

		} else {
			// Initialize clear color
			glClearColor( 0.f, 0.f, 0.f, 1.f );

			// VBO data
			GLfloat vertexData[] =
			{
				-1.0f, -1.0f,
				1.0f, -1.0f,
				0.0f,  1.0f,
			};

			// IBO data
			GLuint indexData[] = { 0, 1, 2};

			// Create VBO
			glGenBuffers( 1, &gVBO );
			glBindBuffer( GL_ARRAY_BUFFER, gVBO );
			glBufferData( GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

			// Create IBO
			glGenBuffers( 1, &gIBO );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
		}
	}
	return success;
}

void handleKeys( unsigned char key, int x, int y ) {
	// Toggle quad
	if( key == 'q' ) {
		gRenderQuad = !gRenderQuad;
	}
}

void update() {
	// No per frame update needed
}

void render() {
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Render quad
	if(gRenderQuad) {
		// Bind program
		glUseProgram(gProgramID);

		// Enable vertex position
		glEnableVertexAttribArray(gVertexPos2DLocation);

		// Set vertex data
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

		// Set index data and render
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

		// Disable vertex position
		glDisableVertexAttribArray(gVertexPos2DLocation);

		// Unbind program
		glUseProgram(0);
	}
}

void close() {
	// Deallocate program
	glDeleteProgram( gProgramID );

	// Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// Quit SDL subsystems
	SDL_Quit();
}

// Parameters necessary for SDL_Main
int main(int argv, char** args) {
	// Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );

	} else {
		// Main loop flag
		bool quit = false;

		// Event handler
		SDL_Event e;
		
		// Enable text input
		SDL_StartTextInput();

		// While application is running
		while( !quit ) {
			// Handle events on queue
			while( SDL_PollEvent( &e ) != 0 ) {
				// User requests quit
				if( e.type == SDL_QUIT ) {
					quit = true;
				}
				// Handle keypress with current mouse position
				else if( e.type == SDL_TEXTINPUT ) {
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}

			render();
			
			// Update screen
			SDL_GL_SwapWindow( gWindow );
		}
		
		// Disable text input
		SDL_StopTextInput();
	}

	close();

	return 0;
}