#include "Instance.h"

Instance::Instance(Object* object, int shaderProgramID, glm::vec3 position, 
    glm::vec3 scale /*=glm::vec3(1)*/, glm::vec3 rotation /*=glm::vec3(0)*/) :
        object{ object }, shaderProgramID{ shaderProgramID },
        position{ position }, rotation{ rotation }, scale{ scale }, 
        needsUpdate{ true }, isStatic{ false } {

    updateModel();
}

Instance::Instance(Object* object, GLuint openGLShaderProgramID, glm::mat4 model) :
    object{ object }, model{ model }, 
    position{ glm::vec3() }, rotation{ glm::vec3() }, scale{ glm::vec3() }, 
    needsUpdate{ false }, isStatic{ true } {}

void Instance::updateModel() {

    if (needsUpdate && !isStatic) {

        // Order matters
        this->model = glm::mat4(1);

        this->model = glm::rotate(this->model, this->rotation.x, glm::vec3(1, 0, 0));
        this->model = glm::rotate(this->model, this->rotation.y, glm::vec3(0, 1, 0));
        this->model = glm::rotate(this->model, this->rotation.z, glm::vec3(0, 0, 1));

        this->model = glm::scale(this->model, this->scale);

        this->model = glm::translate(this->model, this->position);

        needsUpdate = false;
    }
}

glm::mat4 Instance::getModel() {
    return this->model;
}

void Instance::setPosition(glm::vec3 position) {

    assert(("setPosition() called on static instance", !isStatic));

    this->position = position;
    needsUpdate = true;
}

void Instance::addPosition(glm::vec3 addend) {
    this->position += addend;
}

glm::vec3 Instance::getPosition() {
    return this->position;
}

void Instance::setRotation(glm::vec3 rotation) {

    assert(("setRotation() called on static instance", !isStatic));

    this->rotation = rotation;
    needsUpdate = true;
}

glm::vec3 Instance::getRotation() {
    return this->rotation;
}

void Instance::setScale(glm::vec3 scale) {

    assert(("setScale() called on static instance", !isStatic));

    this->scale = scale;
    needsUpdate = true;
}

glm::vec3 Instance::getScale() {
    return this->scale;
}

int Instance::getShaderProgramID() {
    return this->shaderProgramID;
}

GLuint Instance::getObjectVAO() {
    return this->object->getVAO();
}

int Instance::getObjectNumVertices() {
    return this->object->getNumVertices();
}