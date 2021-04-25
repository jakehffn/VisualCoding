#include "Scene.h"

Scene::Scene(GLuint uniformID) :
    uniformID{ uniformID}, instances{ std::vector<Instance*>() }, numInstances{ 0 } {}

void Scene::addInstance(Instance* instance) {
    instances.push_back(instance);
}

void Scene::render(glm::mat4 projection, glm::mat4 view) {

    for (auto& instance : instances) {

        instance->updateModel();
        glm::mat4 model = instance->getModel();

        glm::mat4 MVP = projection * view * model;

        glUniformMatrix4fv(this->uniformID, 1, GL_FALSE, &MVP[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, instance->getVBO());
        glVertexAttribPointer(
            0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, instance->getColorBuffer());
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

        // glDisableVertexAttribArray(0);
        // glDisableVertexAttribArray(1);
    }
}