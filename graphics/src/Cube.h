//
// Created by Johan on 2017-02-10.
//

#ifndef SOFTBODY_CUBE_H
#define SOFTBODY_CUBE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "Mass.h"



class Cube {

private:

    float m = 2.0f; // Mass
    float dt = 0.0005f; // step length

    glm::vec3 gravity = glm::vec3(0.0f, -9.82f, 0.0f); // gravity

public:

    float k; // Spring
    float d; // Damper
    float r; // Rest length of spring

    Cube();

    void setConstants(float _k, float _d, float _r);
    std::vector<Mass> massVec;

    void draw(); // draw the connections
    void updateEuler(); // update masses

    void generateCube(int x, int y, int z); // generates cube and connections

    glm::vec3 calcForce(Mass m1, Mass m2, int m1Index, int m2Index); // calculate force

    void gravitys(bool b); // applies gravity if true

};


#endif //SOFTBODY_CUBE_H
