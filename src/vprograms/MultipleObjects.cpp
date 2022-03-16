#include "MultipleObjects.h"

MultipleObjects::MultipleObjects(SDL_Window* window, bool renderParam) :
    VisualProgram{ window, renderParam } {}

MultipleObjects::~MultipleObjects() {
    // Deallocate program
    glDeleteProgram(programID);
}

void MultipleObjects::init() {
    this->input->setAbridge(SDLK_c);
}

void MultipleObjects::run() {

    ShaderProgram* shaderProgram = new BasicShader();

    int shaderID = scene->addShaderProgram(shaderProgram);

    char objPath[] = "./src/objects/cube.obj";

    int objID = scene->addObject(objPath);
    int instanceID = scene->addInstance(objID, shaderID, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
    int instanceID2 = scene->addInstance(objID, shaderID, glm::vec3(4, 0, 4), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));

    CirclePath* path = new CirclePath(glm::vec3(0, 0, 0), 8, 5, 1);
    PathCameraController* controller2 = new PathCameraController(clock, path);
    scene->addCameraController(controller2);

    // While application is running
    while(!input->quitProgram() && !input->isKeyDown(SDLK_ESCAPE)) {

        clock->tick();
        
        if (input->isKeyDown(SDLK_c)) {
            scene->nextCameraController();
        } 

        scene->render();

        // Update screen
        SDL_GL_SwapWindow(window);

        // TODO: Figure out how to have this done through base class
        glReadPixels(0, 0, render_consts::SCREEN_WIDTH, render_consts::SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, this->frameBuffer);
        fwrite(this->frameBuffer, sizeof(int)*render_consts::SCREEN_WIDTH*render_consts::SCREEN_HEIGHT, 1, ffmpeg);
    }

    SDL_StopTextInput();
}