#include "MathVisualizer.h"

MathVisualizer::MathVisualizer(SDL_Window* window, bool renderParam) :
    VisualProgram{ window, renderParam } {}

MathVisualizer::~MathVisualizer() {
    // Deallocate program
    glDeleteProgram(programID);
}

void MathVisualizer::init() {
    this->input->setAbridge(SDLK_c);
}

void MathVisualizer::run() {

    createBlocks(20);

    CirclePath* circlePath = new CirclePath(glm::vec3(0, 0, 0), 150, 100, 0.1);
    PathCameraController* circleCamera = new PathCameraController(clock, circlePath);
    scene->addCameraController(circleCamera);

    // While application is running
    while(!input->quitProgram() && !input->isKeyDown(SDLK_ESCAPE)) {

        clock->tick();
        printf("FPS: %f\r", this->clock->getAverageFPS());
        // std::cout << clock->getFPS();
        // clock->getFPS();
        
        if (input->isKeyDown(SDLK_c)) {
            scene->nextCameraController();
        } 

        modifyBlocks();
        scene->render();

        // Update screen
        SDL_GL_SwapWindow(window);

        // TODO: Figure out how to have this done through base class
        if (this->renderParam) {
            glReadPixels(0, 0, render_consts::SCREEN_WIDTH, render_consts::SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, this->frameBuffer);
            fwrite(this->frameBuffer, sizeof(int)*render_consts::SCREEN_WIDTH*render_consts::SCREEN_HEIGHT, 1, ffmpeg);
        }
    }

    SDL_StopTextInput();
}

void MathVisualizer::createBlocks(int radius) {

    ShaderProgram* shaderProgram = new TopographicShader(-2, 2, glm::vec3(0.15, 0, 0.26), glm::vec3(.1, .1, 2));
    int shaderID = scene->addShaderProgram(shaderProgram);

    char objPath[] = "./src/objects/cube.obj";
    int objID = scene->addObject(objPath);

    for (int xx = -radius; xx < radius; xx++) {

        for (int zz = -radius; zz < radius; zz++) {

            if (glm::sqrt(glm::pow(xx, 2) + glm::pow(zz, 2)) < radius) {

                float xPos = xx*2;
                float zPos = zz*2;

                scene->addInstance(objID, shaderID, glm::vec3(xPos, 0, zPos), glm::vec3(1, 1, 1));
            }    
        }
    }

    printf("Num instances: %d\n", this->scene->numInstances());
}

void MathVisualizer::modifyBlocks() {

    float time = this->clock->getCumulativeTime();

    for (int xx = 0; xx < scene->numInstances(); xx++) {


        Instance& currInstance = scene->getInstance(xx);

        glm::vec3 prevPos = currInstance.getPosition();

        float yPos = threeDimTangent(time, prevPos.x, prevPos.z);
        
        currInstance.setPosition(glm::vec3(prevPos.x, yPos, prevPos.z));
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
    float amplitude = 10;
    float phase = (xx*xx + yy*yy)*0.1;
    float period = .5;

    float yPos = amplitude*tan(period*sqrt(phase + time));

    return yPos;
}