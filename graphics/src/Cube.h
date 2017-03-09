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

    //Spring values
    float m = 2.0f;
    float h = 0.00001f;

    glm::vec3 gravity=glm::vec3(0.0f, -9.82f, 0.0f);
    glm::vec3 sXlenght = glm::vec3(0.9f, 0.0f,0.0f);
    glm::vec3 sYlenght = glm::vec3(0.0f, 0.9f,0.0f);
    glm::vec3 sZlenght = glm::vec3(0.0f, 0.0f,0.9f);
    glm::vec3 sXYZlenght = glm::vec3(0.9f, 0.9f,0.9f);





public:

    float k; // Spring
    float d; // Damper
    float r; // Rest length of spring

    Cube();

    void setConstans(float _k, float _d, float _r);
    std::vector<Mass> massVec;
    glm::vec3 Fource[8];

    void draw();
    void updateEuler();
    glm::vec3 getCenter();

    void generateCube(int x, int y, int z);

    glm::vec3 calcForce(Mass m1, Mass m2);
};


#endif //SOFTBODY_CUBE_H
