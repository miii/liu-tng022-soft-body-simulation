//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>
#include <typeinfo>

#define PI 3.14159265358979323846  /* pi */

Cube::Cube(){

    generateCube(2, 2, 2);

}

void Cube::generateCube(int x, int y, int z){

    int numMass = x*y*z;
    int numXY = x*y;
    std::cout << std::endl << "Number of Masses: " << numMass << std::endl;
    int xpos = 0;
    int ypos = 0;
    int zpos = 0;


        float abs = 0.8;

    for (int i = 0; i < numMass ; ++i) {

        std::cout << "Mass " << i << " : " << xpos*abs << ", " << ypos*abs <<  ", " << zpos*abs << std::endl;

        massVec.push_back(Mass(glm::vec3(xpos*abs,ypos*abs,zpos*abs), glm::vec3(0,0,0))); // BACK-BOT-LEFT
        xpos++;

        if ( xpos % x == 0 ){
            xpos = 0;
            ypos++;
            if ( ypos % y == 0 ){
                ypos = 0;
                zpos++;
            }

        }

    }

    std::cout << std::endl << "Conections:" << std::endl;


        for (int j = 0; j < massVec.size(); ++j) {

            std::cout << j << ": ";
            if(x > 1) {
            if ((j + 1) % x == 0) {
                massVec[j].xCon = j - 1;
                massVec[j].connections.push_back(j - 1);
                std::cout << "x: " << j - 1 << ", ";

            } else if (j % x == 0) {
                massVec[j].xCon2 = j + 1;
                massVec[j].connections.push_back(j + 1);
                std::cout << "x: " << j + 1 << ", ";
            } else {
                massVec[j].xCon = j - 1;
                massVec[j].xCon2 = j + 1;
                massVec[j].connections.push_back(j - 1);
                massVec[j].connections.push_back(j + 1);
                std::cout << "X(" << j - 1 << ", ";
                std::cout << j + 1 << "), ";
            }
        }


if (y > 1) {
    if (((j - numXY * (j / numXY)) / x) == 0) {
        massVec[j].yCon2 = j + x;
        massVec[j].connections.push_back(j + x);
        std::cout << massVec[j].yCon2 << ", ";
    } else if (((j - numXY * (j / numXY)) / x) == y - 1) {
        massVec[j].yCon = j - x;
        massVec[j].connections.push_back(j - x);
        std::cout << massVec[j].yCon << ", " ;
    } else {
        massVec[j].yCon = j - x;
        massVec[j].yCon2 = j + x;
        massVec[j].connections.push_back(j - x);
        massVec[j].connections.push_back(j + x);
        std::cout << "y( " << massVec[j].yCon << ", " << massVec[j].yCon2 << "), " ;
    }
}
        if (z > 1) {

            //std::cout << "j: " << j << " numXY: " << numXY << " j / numXY: " << j / numXY <<   " val: " << ((j - numXY * (j / numXY)) / numXY) << std::endl;

            if ((((j / numXY)) ) == 0) {
                massVec[j].zCon2 = j + numXY;
                massVec[j].connections.push_back(j + numXY);
                //std::cout << j-numXY << " x"<< std::endl ;
                std::cout << massVec[j].zCon2 << " " << std::endl;
                //std::cout << "z1" << std::endl;

            } else if (( (j / numXY))  == z - 1) {
                massVec[j].zCon = j - numXY;
                massVec[j].connections.push_back(j - numXY);
                //std::cout << j+numXY << std::endl ;
                std::cout << massVec[j].zCon << ", " << std::endl;
                //std::cout << "z2" << std::endl;


            } else {
                massVec[j].zCon = j - x;
                massVec[j].zCon2 = j + x;
                massVec[j].connections.push_back(j - numXY);
                massVec[j].connections.push_back(j + numXY);
                std::cout << "z( " << massVec[j].zCon << ", " << massVec[j].zCon2 << ")" << std::endl;
            }
        }
            std::cout << std::endl;

        //std::cout << "conections: " <<  massVec[j].connections.size() << std::endl;

    }



    //TODO :: remove later
    //massVec[0].connect(3);
    //massVec[1].connect(2);
    //massVec[2].connect(1);
    //massVec[3].connect(0);

}



void Cube::updateEuler(){

    glm::vec3 posision1;
    glm::vec3 posision2;
    glm::vec3 velocity1;
    glm::vec3 velocity2;


    for (int i=0; i<massVec.size(); i++) {

        for (int j = 0; j < massVec[i].connections.size() ; ++j) {

            int ni =  massVec[i].connections[j];

            if(massVec[i].getVelocity().x != massVec[i].getVelocity().x){
                return;
            }

            // Calculate forces for mass 1 and 2
            glm::vec3 force = calcForce(massVec[i], massVec[ni]);





            // Calculate new velocity
            glm::vec3 vel1 = massVec[i].getVelocity() + h * (force /*+ m*gravity*/) / m;
            glm::vec3 vel2 = massVec[ni].getVelocity() + h * (-force /*+ m*gravity*/)/ m;



          //  std::cout << vel1.x << std::endl;

            // Calculate new position
            glm::vec3 pos1 = massVec[i].getPosition() + h * vel1;
            glm::vec3 pos2 = massVec[ni].getPosition() + h * vel2;

            //std::cout << pos1.x << std::endl;

            // Set new mass 1 state

                massVec[i].setPosition(pos1);
                massVec[i].setVelocity(vel1);

            // Set new mass 2 state
                massVec[ni].setPosition(pos2);
                massVec[ni].setVelocity(vel2);


            std::cout << "pos mass" << i << ": " << massVec[i].getPosition().x << ", " << massVec[i].getPosition().y << ", " << massVec[i].getPosition().z <<  std::endl;


        }



    }

}

glm::vec3 Cube::calcForce(Mass m1, Mass m2) {

    glm::vec3 p1 = m1.getPosition();
    glm::vec3 p2 = m2.getPosition();

    glm::vec3 v1 = m1.getVelocity();
    glm::vec3 v2 = m2.getVelocity();


    double dy = p2.y - p1.y;
    double dx = p2.x - p1.x;
    double dz = p2.z - p1.z;

    double angleyx = 0;
    double angleyz = 0;
    if (dx != 0)
        angleyx = glm::atan(dy / dx);
    if (dz != 0)
        angleyz = glm::atan(dy / dz);

    double euclDist = glm::sqrt( glm::pow(p1.x - p2.x, 2) + glm::pow(p1.y - p2.y, 2) + glm::pow(p1.z - p2.z, 2) );
    double euclVel = glm::sqrt( glm::pow(v1.x - v2.x, 2) + glm::pow(v1.y - v2.y, 2) + glm::pow(v1.z - v2.z, 2) );




    double fspring = k * (euclDist - r);
    double fdamper = d * euclVel;



    glm::vec3 dir = glm::vec3(0, 0, 0);

    if ((v2.x - v1.x) != 0)
        dir.x = (v2.x - v1.x) / std::abs(v2.x - v1.x);

    if ((v2.y - v1.y) != 0)
        dir.y = (v2.y - v1.y) / std::abs(v2.y - v1.y);

    if ((v2.z - v1.z) != 0)
        dir.z = (v2.z - v1.z) / std::abs(v2.z - v1.z);

    //std::cout << "dir x: " << dir.x << " y: " << dir.y << std::endl;

    if (dx < 0)
        angleyx = angleyx + PI;
    if (dz <0)
        angleyz = angleyz + PI;


    double hypyx = glm::sqrt(glm::pow(dx,2)+glm::pow(dy,2));
    double hypyz = glm::sqrt(glm::pow(dz,2)+glm::pow(dy,2));


    glm::vec3 force = glm::vec3(0, 0, 0);
    force.x = fspring * hypyx * glm::cos(angleyx) + fdamper * hypyx * dir.x;
    force.y = fspring * hypyx * glm::sin(angleyx) + fdamper *  hypyx *dir.y;
    force.z = fspring * hypyz * glm::cos(angleyz) + fdamper * hypyz * dir.z;

      //std::cout << "f: " << force.y << std::endl;



    return force;

}

    /*

     6----------7
     |\         |\
     | \        | \
     |  2----------3
     |  |       |  |
     4--|-------5  |
      \ |        \ |
       \|         \|
        0----------1

     */




void Cube::draw()
{
    int count = 0;
    // set the line width
    glLineWidth(8.0);

    // Call only once for all remaining points
    glBegin(GL_LINES);

    for(int i=0; i<massVec.size(); ++i){
        float x = massVec[i].getPosition().x;
        float y = massVec[i].getPosition().y;
        float z = massVec[i].getPosition().z;

        int con;

        for (int j = 0; j < massVec[i].connections.size(); ++j) {

            con = massVec[i].connections[j];
            if (con > i ) {

                glVertex3f(x, y, z);
                glVertex3f(massVec[con].getPosition().x, massVec[con].getPosition().y, massVec[con].getPosition().z);
                count++;
            }
        }
    }


        // Done drawing points
        glEnd();

    /*

     6----------7
     |\         |\
     | \        | \
     |  2----------3
     |  |       |  |
     4--|-------5  |
      \ |        \ |
       \|         \|
        0----------1

     */

}



glm::vec3 Cube::getCenter(){

    glm::vec3 avgPos= glm::vec3(0.0f, 0.0f, 0.0f);

    for(int i=0; i<massVec.size();i++)
    {
        avgPos+=massVec[i].getPosition();
    }

    avgPos/=(float)massVec.size();

    return avgPos;
}

void Cube::setConstans(float _k, float _d, float _r) {
    k = _k;
    d = _d;
    r = _r;

}
