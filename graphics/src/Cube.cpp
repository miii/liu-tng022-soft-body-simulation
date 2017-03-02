//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>
#include <typeinfo>

#define PI 3.14159265358979323846  /* pi */

Cube::Cube(){

    genrateCube(2,1,1);

}

void Cube::genrateCube(int x, int y, int z){

    int numMass = x*y*z;
    int numXY = x*y;
    std::cout << numMass << std::endl;
    int xpos = 0;
    int ypos = 0;
    int zpos = 0;


        float abs = 0.3;

    for (int i = 0; i < numMass ; ++i) {

        std::cout << xpos << ", " << ypos <<  ", " << zpos << std::endl;

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

    std::cout << std::endl;


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

        //std::cout << "conections: " <<  massVec[j].connections.size() << std::endl;

    }

}






glm::vec3 massXPos;
glm::vec3 massXPos2;
glm::vec3 massYPos;
glm::vec3 massYPos2;
glm::vec3 massZPos;
glm::vec3 massZPos2;

glm::vec3 massXVel;
glm::vec3 massXVel2;
glm::vec3 massYVel;
glm::vec3 massYVel2;
glm::vec3 massZVel;
glm::vec3 massZVel2;


void Cube::updateEuler(){

    glm::vec3 posision1;
    glm::vec3 posision2;
    glm::vec3 velocity1;
    glm::vec3 velocity2;
    float dx;
    float dy;
    float angle;
    float euclDist;
    float euclVel;
    float fspring;
    float fdamper;
    glm::vec3 dir = glm::vec3(0.0f, 0.0f,0.0f);
    glm::vec3 fp1 = glm::vec3(0.0f, 0.0f,0.0f);
    glm::vec3 fp2 = glm::vec3(0.0f, 0.0f,0.0f);


    for (int i=0; i<massVec.size(); i++) {

        //get mass position and velocity
        posision1 = massVec[i].getPosition();
        velocity1 = massVec[i].getVelocity();


        for (int j = 0; j < massVec[i].connections.size() ; ++j) {

            // Get conected mass's position and velocity
            posision2 = massVec[j].getPosition();
            velocity2 = massVec[j].getVelocity();
            dx = posision2.x - posision1.x;
            dy = posision2.y - posision1.y;
            if (dx != 0) {
                angle = glm::atan(dy / dx);
            }
            euclDist = glm::sqrt( glm::pow(posision1.x-posision2.x,2) + glm::pow(posision1.y-posision2.y,2) );
            euclVel = glm::sqrt( glm::pow(velocity1.x-velocity2.x,2) + glm::pow(velocity1.y-velocity2.y,2) );

            fspring = k * (euclDist - r);
            fdamper = d * euclVel;

            glm::vec3 v1 =velocity2 - velocity1;
            glm::vec3 v2 = glm::abs(velocity2 - velocity1);

            dir.x = (velocity2.x - velocity1.x) / glm::abs(velocity2.x - velocity1.x);
            dir.y = (velocity2.y - velocity1.y) / glm::abs(velocity2.y - velocity1.y);
            dir.z = (velocity2.z - velocity1.z) / glm::abs(velocity2.z - velocity1.z);


            if ( dir.x != -1 || dir.x != 0 || dir.x != 1 ){
                dir.x = 0;
            }
            if ( dir.y != -1 || dir.y != 0 || dir.y != 1 ){
                dir.y = 0;
            }
            if ( dir.z != -1 || dir.z != 0 || dir.z != 1 ){
                dir.z = 0;
            }


            if (dx < 0) {
                angle = angle + PI ;
            }

            fp1.x = fspring * glm::cos(angle) + fdamper * dir.x;
            fp1.y = fspring * glm::sin(angle) + fdamper * dir.y;

            fp2 = - fp1;

           /*
            std::cout << "dx: " << dx << std::endl;
            std::cout << "dy: " << dy << std::endl;
            std::cout << "angle: " << angle << std::endl;
            std::cout << "euclDist: " << euclDist << std::endl;
            std::cout << "euclVel: " << euclVel << std::endl;
            std::cout << "fspring: " << fspring << std::endl;
            std::cout << "fdamper: " << fdamper << std::endl;
            std::cout << "dir: ( " << dir.x << ", " << dir.y << ", " << dir.z << ")" << std::endl;
            std::cout << "fp1: ( " << fp1.x << ", " << fp1.y << ", " << fp1.z << ")" << std::endl;
            std::cout << "fp2: ( " << fp2.x << ", " << fp2.y << ", " << fp2.z << ")" << std::endl;
            std::cout << std::endl;
*/

            massVec[i].setVelocity(massVec[i].getPreviousVelocity() + h * fp1 / m) ; // TODO:: FIX
            massVec[j].setVelocity(massVec[j].getPreviousVelocity() + h * fp2 / m) ; // TODO:: FIX

            massVec[i].setPosition(massVec[i].getPreviousPosition() + h * velocity1) ; // TODO:: FIX
            massVec[j].setPosition(massVec[j].getPreviousPosition() + h * velocity2) ; // TODO:: FIX







        }


    }
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
    glLineWidth(4.0);

    // Call only once for all remaining points
    glBegin(GL_LINES);

    for(int i=0; i<massVec.size(); ++i){
        float x = massVec[i].getPosition().x;
        float y = massVec[i].getPosition().y;
        float z = massVec[i].getPosition().z;

        int conx = massVec[i].getxCon();
        int conx2 = massVec[i].getxCon2();
        int cony = massVec[i].getyCon();
        int cony2 = massVec[i].getyCon2();
        int conz = massVec[i].getzCon();
        int conz2 = massVec[i].getzCon2();

        int con;


        //std::cout << conx2 << " x2"<< std::endl;
        //std::cout << conx << " x"<< std::endl;
        //  std::cout << i << " : ";
        for (int j = 0; j < massVec[i].connections.size(); ++j) {
            con = massVec[i].connections[j];
            if (con > i ) {
                glVertex3f(x, y, z);
                glVertex3f(massVec[con].getPosition().x, massVec[con].getPosition().y, massVec[con].getPosition().z);
                count++;
            }
        }




/*
        if (conx > i && conx < massVec.size()){
            glVertex3f(x, y, z);
            glVertex3f(massVec[conx].getPosition().x, massVec[conx].getPosition().y, massVec[conx].getPosition().z);
            //    std::cout << "x: " << conx ;
        }

        if (conx2 > i && conx2 < massVec.size()){
            glVertex3f(x, y, z);
            glVertex3f(massVec[conx2].getPosition().x, massVec[conx2].getPosition().y, massVec[conx2].getPosition().z);
            //    std::cout << "x: " << conx ;
        }

        if (cony > i && cony < massVec.size() ){
            glVertex3f(x, y, z);
            glVertex3f(massVec[cony].getPosition().x, massVec[cony].getPosition().y, massVec[cony].getPosition().z);
            //std::cout << "y: " << cony ;
        }
        if (cony2 > i && cony2 < massVec.size()){
            glVertex3f(x, y, z);
            glVertex3f(massVec[cony2].getPosition().x, massVec[cony2].getPosition().y, massVec[cony2].getPosition().z);
             // std::cout << "y: " << cony ;
        }
        if (conz > i && conz < massVec.size()){
            glVertex3f(x, y, z);
            glVertex3f(massVec[conz].getPosition().x, massVec[conz].getPosition().y, massVec[conz].getPosition().z);
        }
        if (conz2 > i && conz2 < massVec.size()){
            glVertex3f(x, y, z);
            glVertex3f(massVec[conz2].getPosition().x, massVec[conz2].getPosition().y, massVec[conz2].getPosition().z);
        }
        */



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
