#include "Scene.h"

Scene::Scene(GLint programID) :
    uniformID{ glGetUniformLocation(programID, "MVP") }, instances{ std::vector<Instance*>() } {}

void Scene::addInstance(Instance* instance) {
    instances.push_back(instance);
}

void Scene::render(glm::mat4 projection, glm::mat4 view) {

    for (auto& instance : instances) {

        instance->updateModel();

        glm::mat4 model = instance->getModel();
        glm::mat4 MVP = projection * view * model;

        glUniformMatrix4fv(this->uniformID, 1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(instance->getVAO());
        glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0); 
        glBindVertexArray(0);
    }
}