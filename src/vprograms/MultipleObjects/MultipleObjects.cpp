#include "MultipleObjects.h"

MultipleObjects::~MultipleObjects() {
    // Deallocate program
    glDeleteProgram(programID);
}

void MultipleObjects::init(SDL_Window* window) {

    this->window = window;

    this->clock = new Clock();
    this->input = new Input();

    this->input->setAbridge(SDLK_c);

    this->cameraController = new UserCameraController(this->window, this->clock, this->input);

    this->scene = new Scene(this->window, this->clock, this->input, this->cameraController);

    // Enable text input
    SDL_StartTextInput();
}

void MultipleObjects::run() {

    std::string vertexPath = "./src/vprograms/MultipleObjects/shaders/vertexShader.glsl";
    std::string fragmentPath = "./src/vprograms/MultipleObjects/shaders/fragmentShader.glsl";

    ShaderProgram* shaderProgram = new BasicShaderProgram(vertexPath, fragmentPath);

    int shaderID = scene->addShaderProgram(shaderProgram);

    char objPath[] = "C:\\Users\\Jaket\\OneDrive\\Documents\\Programming\\visualCoding\\src\\vprograms\\MultipleObjects\\objects\\cube.obj";

    int objID = scene->addObject(objPath);
    int instanceID = scene->addInstance(objID, shaderID, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));

    CirclePath* path = new CirclePath(glm::vec3(0, 0, 0), 8, 5, 0.001);
    PathCameraController* controller2 = new PathCameraController(clock, path);
    scene->addCameraController(controller2);

    // While application is running
    while(!input->quitProgram()) {

        clock->tick();
        
        if (input->isKeyDown(SDLK_c)) {
            scene->nextCameraController();
        } 

        scene->render();

        // Update screen
        SDL_GL_SwapWindow(window);
    }

    SDL_StopTextInput();
}