#pragma once

#include <vector>

#include "Object.h"
#include "Instance.h"
#include "Camera.h"
#include "Clock.h"
#include "ShaderProgram.h"
#include "UserCameraController.h"

class Scene {
public:
    Scene(SDL_Window* window, Clock* clock, Input* input, CameraController* cameraController);

    // Returns ID for shader program (currently just vector pos)
    int addShaderProgram(ShaderProgram* shaderProgram);
    // Returns ID for obj (currently just vector pos)
    int addObject(char* objPath);
    // Returns ID for instance (currently just vector pos)
    int addInstance(int objID, int shaderProgramID, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
    int addInstance(int objID, int shaderProgramID, glm::vec3 position, glm::vec3 scale);
    int addInstance(int objID, int shaderProgramID, glm::vec3 position);
    Instance& getInstance(int instanceID);
    int numInstances();

    // Returns the position of added camera controller
    int addCameraController(CameraController* cameraController);
    void setCameraController(int pos);
    void nextCameraController();
    // void addPointLight(glm::vec3 lightPos);

    void render();

private:
    SDL_Window* window;
    Clock* clock;
    Input* input;

    Camera camera;

    std::vector<CameraController*> cameraControllers;
    int cameraControllerPosition;

    std::vector<ShaderProgram*> shaderPrograms;
    std::vector<Object> objects;
    std::vector<Instance> instances;
};