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
    glm::vec3 pos;
    glm::vec3 ppos;
    glm::vec3 velocity;
    glm::vec3 pvelocity;



public:
    glm::vec3 initialVelocity;

    int xCon = -1;
    int xCon2 = -1;
    int yCon = -1;
    int yCon2 = -1;
    int zCon = -1;
    int zCon2 = -1;
    std::vector<int> connections;

    int xyzCon;

    Mass(glm::vec3 _pos, glm::vec3 initVel);


    void setPosition(glm::vec3);
    glm::vec3 getPosition();
    glm::vec3 getPreviousPosition();
    void setPreviousPosition(glm::vec3 pos);

    void setVelocity(glm::vec3 vel);
    glm::vec3 getVelocity();
    glm::vec3 getPreviousVelocity();
    void setPreviousVelocity(glm::vec3 vel);

    int getxCon();
    int getyCon();
    int getzCon();

    int getxCon2();

    int getzCon2();

    int getyCon2();
};


#endif //SOFTBODY_MASS_H
