//
// Created by Johan on 2017-02-10.
//

#include "Mass.h"

// gets the position of the mass
glm::vec3 Mass::getPosition(){
    return pos;
}

// sets the position for the mass
void Mass::setPosition(glm::vec3 _pos){
    pos=_pos;
}

// sets velocity for the cube
void Mass::setVelocity(glm::vec3 vel){
    velocity=vel;
}

// gets the velocity of the cube
glm::vec3 Mass::getVelocity(){
    return velocity;
}

// mass constructor
Mass::Mass(glm::vec3 _pos, glm::vec3 initVel) {
    pos = _pos;
    initialPosition = _pos;

    initialVelocity=initVel;
    velocity=initialVelocity;

}

// connects mass
void Mass::connect(int massIndex) {
    connections.push_back(massIndex);
}

glm::vec3 Mass::getinitialPosition() {
    return initialPosition;
}


