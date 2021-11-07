#include "Instance.h"

Instance::Instance(glm::vec3 position, 
    glm::vec3 scale /*=glm::vec3(1)*/, glm::vec3 rotation /*=glm::vec3(0)*/) :
        position{ position }, rotation{ rotation }, scale{ scale }, 
        changed{ true }, isStatic{ false } {}

Instance::Instance(glm::mat4 model) :
    position{ glm::vec3() }, rotation{ glm::vec3() }, scale{ glm::vec3() }, 
    changed{ true }, isStatic{ true } {}

glm::mat4 Instance::getModel() {

    // Order matters
    glm::mat4 model = glm::mat4(1);

    glm::mat4 rotate = glm::mat4(1);
    
    rotate = glm::rotate(rotate, this->rotation.x, glm::vec3(1, 0, 0));
    rotate = glm::rotate(rotate, this->rotation.y, glm::vec3(0, 1, 0));
    rotate = glm::rotate(rotate, this->rotation.z, glm::vec3(0, 0, 1));

    glm::mat4 scale = glm::scale(glm::mat4(1), this->scale);

    glm::mat4 translate = glm::translate(glm::mat4(1), this->position);

    changed = false;

    return translate * scale * rotate;
}

bool Instance::needsUpdate() const {
    return this->changed;
}

void Instance::setPosition(glm::vec3 position) {

    assert(("setPosition() called on static instance", !isStatic));

    this->position = position;
    this->changed = true;
}

void Instance::addPosition(glm::vec3 position) {

    assert(("addPosition() called on static instance", !isStatic));

    this->position += position;
    this->changed = true;
}

glm::vec3 Instance::getPosition() {
    return this->position;
}

void Instance::setRotation(glm::vec3 rotation) {

    assert(("setRotation() called on static instance", !isStatic));

    this->rotation = rotation;
    this->changed = true;
}

glm::vec3 Instance::getRotation() {
    return this->rotation;
}

void Instance::setScale(glm::vec3 scale) {

    assert(("setScale() called on static instance", !isStatic));

    this->scale = scale;
    this->changed = true;
}

glm::vec3 Instance::getScale() {
    return this->scale;
}