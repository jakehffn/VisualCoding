#include "MathVisualizer.h"

MathVisualizer::~MathVisualizer() {
    // Deallocate program
    glDeleteProgram(programID);
}

void MathVisualizer::init(SDL_Window* window) {

    this->window = window;

    this->clock = new Clock();
    this->input = new Input();

    this->input->setAbridge(SDLK_c);

    this->cameraController = new UserCameraController(this->window, this->clock, this->input);

    this->scene = new Scene(this->window, this->clock, this->input, this->cameraController);

    // Enable text input
    SDL_StartTextInput();
}

void MathVisualizer::run() {

    int blockWidth = 1;
    int blockHeight = 1;

    createBlockArray(blockWidth, blockHeight);

    CirclePath* circlePath = new CirclePath(glm::vec3(0, 0, 0), 100, 30, 0.1);
    PathCameraController* circleCamera = new PathCameraController(clock, circlePath);
    scene->addCameraController(circleCamera);

    printf("\n\n");

    // While application is running
    while(!input->quitProgram() && !input->isKeyDown(SDLK_ESCAPE)) {

        clock->tick();
        // printf("FPS: %f\r", this->clock->getAverageFPS());
        // std::cout << clock->getFPS();
        // clock->getFPS();
        
        if (input->isKeyDown(SDLK_c)) {
            scene->nextCameraController();
        } 

        // modifyBlockArray(blockWidth, blockHeight);
        scene->render();

        // Update screen
        SDL_GL_SwapWindow(window);
    }

    SDL_StopTextInput();
}

void MathVisualizer::createBlockArray(int width, int length) {

    ShaderProgram* shaderProgram = new InstancedShader(-2, 2, glm::vec3(0.15, 0, 0.26), glm::vec3(.1, .1, 2));
    int shaderID = scene->addShaderProgram(shaderProgram);

    char objPath[] = "./src/objects/cube.obj";
    int objID = scene->addObject(objPath, shaderID);

    for (int xx = 0; xx < width; xx++) {

        for (int yy = 0; yy < length; yy++) {
            
            float xPos = (xx - (float)(width)/2.0)*2.0;
            float yPos = (yy - (float)(length)/2.0)*2.0;

            scene->addInstance(objID, glm::vec3(xPos, 0, yPos), glm::vec3(1, 2, 1));
        }
    }
}

void MathVisualizer::modifyBlockArray(int width, int length) {

    float time = this->clock->getCumulativeTime();

    for (int xx = 0; xx < width; xx++) {

        for (int yy = 0; yy < length; yy++) {

            int pos = xx * width + yy;

            Instance& currInstance = scene->getInstance(0, pos);

            float yPos = threeDimTangent(time, xx - width/2, yy - length/2);
            
            glm::vec3 prev = currInstance.getPosition();
            currInstance.setPosition(glm::vec3(prev.x, yPos, prev.z));
        }

        
    }
}

float MathVisualizer::twoDimSine(float time, int xx, int yy) {

    time = time * 0.5;
    float amplitude = 2;
    float phase = (xx + yy)*0.1;
    float period = 2;

    float yPos = amplitude*sin(period*(time + phase));

    return yPos;
}

float MathVisualizer::threeDimSine(float time, int xx, int yy) {

    time = time * 1.5;
    float amplitude = 3;
    float phase = (xx*xx + yy*yy)*0.1;
    float period = 3;

    float yPos = amplitude*sin(period*sqrt(phase + time));

    return yPos;
}

float MathVisualizer::threeDimTangent(float time, int xx, int yy) {

    time = time * 1.5;
    float amplitude = 3;
    float phase = (xx*xx + yy*yy)*0.1;
    float period = 3;

    float yPos = amplitude*tan(period*sqrt(phase + time));

    return yPos;
}