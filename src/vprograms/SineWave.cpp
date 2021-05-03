#include "SineWave.h"

SineWave::~SineWave() {
    // Deallocate program
    glDeleteProgram(programID);
}

void SineWave::init(SDL_Window* window) {

    this->window = window;

    this->clock = new Clock();
    this->input = new Input();

    this->input->setAbridge(SDLK_c);

    this->cameraController = new UserCameraController(this->window, this->clock, this->input);

    this->scene = new Scene(this->window, this->clock, this->input, this->cameraController);

    // Enable text input
    SDL_StartTextInput();
}

void SineWave::run() {

    int blockWidth = 100;
    int blockHeight = 100;

    createBlockArray(blockWidth, blockHeight);

    CirclePath* path = new CirclePath(glm::vec3(0, 0, 0), 8, 5, 0.001);
    PathCameraController* controller2 = new PathCameraController(clock, path);
    scene->addCameraController(controller2);

    // While application is running
    while(!input->quitProgram() && !input->isKeyDown(SDLK_ESCAPE)) {

        clock->tick();
        
        if (input->isKeyDown(SDLK_c)) {
            scene->nextCameraController();
        } 

        modifyBlockArray(blockHeight*blockWidth);
        scene->render();

        // Update screen
        SDL_GL_SwapWindow(window);
    }

    SDL_StopTextInput();
}

void SineWave::createBlockArray(int width, int length) {

    ShaderProgram* shaderProgram = new BasicShaderProgram();
    int shaderID = scene->addShaderProgram(shaderProgram);

    char objPath[] = "./src/objects/cube.obj";
    int objID = scene->addObject(objPath);

    for (int xx = 0; xx < width; xx++) {

        for (int yy = 0; yy < length; yy++) {
            
            int xPos = xx*2;
            int yPos = yy*2;

            scene->addInstance(objID, shaderID, glm::vec3(xPos, 0, yPos));
        }
    }
}

void SineWave::modifyBlockArray(int totalBlocks) {

    float time = this->clock->getCumulativeTime()*0.001;

    for (int xx = 0; xx < totalBlocks; xx++) {

        Instance& currInstance = scene->getInstance(xx);

        glm::vec3 prev = currInstance.getPosition();
        currInstance.setPosition(glm::vec3(prev.x, sin(time - xx*0.01), prev.z));
    }
}