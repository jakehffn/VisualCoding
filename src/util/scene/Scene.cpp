#include "Scene.h"

Scene::Scene(GLint programID) :
    programID{ programID }, instances{ std::vector<Instance*>() } {

    this->setUniformIDs();
}

void Scene::addInstance(Instance* instance) {
    instances.push_back(instance);
}

void Scene::render(glm::mat4 projection, glm::mat4 view) {

    for (auto& instance : instances) {

        instance->updateModel();

        glm::mat4 M = instance->getModel();
        glm::mat4 MVP = projection*view*M;

        glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(this->LightID, 0, 100, 10);

        glUniformMatrix4fv(this->MVPuniformID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(this->MuniformID, 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(this->VuniformID, 1, GL_FALSE, &view[0][0]);

        glBindVertexArray(instance->getObjectVAO());
        glDrawArrays(GL_TRIANGLES, 0, instance->getObjectNumVertices()); 
        glBindVertexArray(0);
    }
}

void Scene::setUniformIDs() {
    
    this->MVPuniformID = glGetUniformLocation(this->programID, "MVP");
    this->MuniformID = glGetUniformLocation(this->programID, "M");
    this->VuniformID - glGetUniformLocation(this->programID, "V");
    this->LightID = glGetUniformLocation(this->programID, "LightPosition_worldspace");
}