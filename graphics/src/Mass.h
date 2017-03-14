//
// Created by Johan on 2017-02-10.
//

#ifndef SOFTBODY_MASS_H
#define SOFTBODY_MASS_H

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>

class Mass {

private:
    // position of mass
    glm::vec3 pos = glm::vec3(0,0,0);
    // velocity of mass
    glm::vec3 velocity = glm::vec3(0,0,0);



public:
    glm::vec3 initialVelocity; // initial Velocity


    // all the connections for the mass
    std::vector<int> connections;

    // constructor of Mass
    Mass(glm::vec3 _pos, glm::vec3 initVel);


    // connects
    void connect(int massIndex);

    // sets the position of the mass
    void setPosition(glm::vec3);

    // gets the position of the mass
    glm::vec3 getPosition();

    // sets the Velocity of the masses
    void setVelocity(glm::vec3 vel);

    // gets the Velocity of the masses
    glm::vec3 getVelocity();

};


#endif //SOFTBODY_MASS_H
