//
// Created by Johan on 2017-02-10.
//

#include "Mass.h"

glm::vec3 Mass::getPosition(){
    return pos;
}

void Mass::setPosition(glm::vec3 _pos){
    pos=_pos;
}

void Mass::setVelocity(glm::vec3 vel){
    velocity=vel;
}

glm::vec3 Mass::getVelocity(){
    return velocity;
}

Mass::Mass(glm::vec3 _pos, glm::vec3 initVel) {
    pos = _pos;

    initialVelocity=initVel;
    velocity=initialVelocity;

}




int Mass::getxCon() {
    return xCon;
}
int Mass::getxCon2() {
    return xCon2;
}
int Mass::getyCon2() {
    return yCon2;
}
int Mass::getyCon() {
    return yCon;
}
int Mass::getzCon() {
    return zCon;
}
int Mass::getzCon2() {
    return zCon2;
}

glm::vec3 Mass::getPreviousPosition() {
    return ppos;
}

glm::vec3 Mass::getPreviousVelocity() {
    return pvelocity;
}

void Mass::setPreviousPosition( glm::vec3 pos) {
    ppos=pos;

}

void Mass::setPreviousVelocity(glm::vec3 vel) {
    pvelocity=vel;
}

void Mass::connect(int massIndex) {
    connections.push_back(massIndex);
}


