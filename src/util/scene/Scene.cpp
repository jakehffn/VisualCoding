#include "Scene.h"

Scene::Scene(SDL_Window* window, Clock* clock, Input* input, CameraController* cameraController) :
    window{ window }, clock{ clock }, input{ input }, cameraControllerPosition{ 0 },
    shaderPrograms{ std::vector<ShaderProgram*>() }, 
    objects{ std::vector<Object>() } {

        this->cameraControllers = std::vector<CameraController*>{ cameraController };
        this->camera = Camera(this->cameraControllers.at(0));

        // glClearColor(0.0f, 0.4f, 0.4f, 0.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
}

int Scene::addShaderProgram(ShaderProgram* shaderProgram) {

    this->shaderPrograms.push_back(shaderProgram);
    return this->shaderPrograms.size() - 1;
}

int Scene::addObject(char* objPath, int shaderProgramID) {

    Object newObject = Object(objPath, shaderProgramID);
    this->objects.push_back(newObject);
    return this->objects.size() - 1;
}

void Scene::updateObject(int objID) {
    this->objects.at(objID).updateModelMatrices();
}

int Scene::addInstance(int objID, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) {
    
    Object* instanceObject = &(this->objects.at(objID));

    int instanceID = instanceObject->addInstance(position, scale, rotation);

    return instanceID;
}

int Scene::addInstance(int objID, glm::vec3 position, glm::vec3 scale) {
    return this->addInstance(objID, position, scale, glm::vec3(0, 0, 0));
}

int Scene::addInstance(int objID, glm::vec3 position) {
    return this->addInstance(objID, position, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0));
}

Instance& Scene::getInstance(int objID, int instanceID) {

    assert(objID < objects.size());

    return this->objects[objID].getInstance(instanceID);
}

int Scene::addCameraController(CameraController* cameraController) {
    
	this->cameraControllers.push_back(cameraController);
    return this->cameraControllers.size() - 1;
}

void Scene::setCameraController(int pos) {

	assert(pos < cameraControllers.size());

	this->cameraControllerPosition = pos;
    this->camera.setController(this->cameraControllers.at(pos));
}

void Scene::nextCameraController() {

	cameraControllerPosition++;

	if (cameraControllerPosition == cameraControllers.size()) {
		cameraControllerPosition = 0;
	}

	setCameraController(cameraControllerPosition);
}

void Scene::render() {

    input->update();
    camera.update();

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto& object : objects) {

        object.updateModelMatrices();

        int instanceShaderID = object.getShaderProgramID();

        assert(instanceShaderID < shaderPrograms.size());

        // Use shader
        ShaderProgram* instanceShader = this->shaderPrograms.at(instanceShaderID);
        GLuint openGLShaderProgramID = instanceShader->getOpenGLShaderProgramID();
        glUseProgram(openGLShaderProgramID);

        // glm::mat4 model = instance.getModel();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();

        instanceShader->renderSetup(view, projection);
        
        glBindVertexArray(object.getVAO());
        // glDrawArrays(GL_TRIANGLES, 0, object.getNumVertices()); 
        glDrawArraysInstanced(GL_TRIANGLES, 0, object.getNumVertices(), object.getNumInstances());
        glBindVertexArray(0);

        // GLenum err;
        // while((err = glGetError()) != GL_NO_ERROR) {
        //     printf("\n\nError: %d\n\n", err);
        // }

        // printf("Instances: %d VAO: %d\r", object.getNumInstances(), object.getVAO());
    }
}
