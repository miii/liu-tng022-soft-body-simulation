//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>

#define PI 3.14159265358979323846  /* pi */

Cube::Cube(){

    generateCube(4, 4, 4);

}

void Cube::generateCube(int x, int y, int z){

    int numMass = x*y*z;
    int numXY = x*y;
    std::cout << std::endl << "Number of Masses: " << numMass << std::endl;
    int xpos = 0;
    int ypos = 0;
    int zpos = 0;



    // Generate masses and puts them in vector
    for (int i = 0; i < numMass ; ++i) {

        std::cout << "Mass " << i << " : " << xpos*di << ", " << ypos*di <<  ", " << zpos*di << std::endl;

        massVec.push_back(Mass(glm::vec3(xpos*di,ypos*di,zpos*di), glm::vec3(0,0,0)));
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
        std::cout << "mass" << j << ": " ;
        for (int i = 0; i < massVec.size() ; ++i) {
            if(distance3D(massVec[j], massVec[i]) <= std::sqrt(di*di*2)+di/10 && j!= i){
                massVec[j].connect(i);
                std::cout << i << ", ";
            }
        }
        std::cout << std::endl;


    }
/*
    // creat connection in X, Y and Z if other conections are needed, creat them manually with mass.connect(int)
        for (int j = 0; j < massVec.size(); ++j) {
            std::cout << j << ": ";
            if(x > 1) {
            if ((j + 1) % x == 0) {
                massVec[j].connections.push_back(j - 1);
                std::cout << "x: " << j - 1 << ", ";
            } else if (j % x == 0) {
                massVec[j].connections.push_back(j + 1);
                std::cout << "x: " << j + 1 << ", ";
            } else {

                massVec[j].connections.push_back(j - 1);
                massVec[j].connections.push_back(j + 1);
                std::cout << "X(" << j - 1 << ", ";
                std::cout << j + 1 << "), ";
            }
        }


if (y > 1) {
    if (((j - numXY * (j / numXY)) / x) == 0) {
        massVec[j].connections.push_back(j + x);
        std::cout << j + x << ", ";
    } else if (((j - numXY * (j / numXY)) / x) == y - 1) {
        massVec[j].connections.push_back(j - x);
        std::cout << j - x << ", " ;
    } else {
        massVec[j].connections.push_back(j - x);
        massVec[j].connections.push_back(j + x);
        std::cout << "y( " << j - x << ", " << j + x << "), " ;
    }
}
        if (z > 1) {

            if ((((j / numXY)) ) == 0) {
                massVec[j].connections.push_back(j + numXY);
                std::cout << j + numXY << " " << std::endl;

            } else if (( (j / numXY))  == z - 1) {
                massVec[j].connections.push_back(j - numXY);
                std::cout <<j - numXY << ", " << std::endl;


            } else {
                massVec[j].connections.push_back(j - numXY);
                massVec[j].connections.push_back(j + numXY);
                std::cout << "z( " << j - numXY << ", " << j + numXY << ")" << std::endl;
            }
        }
            std::cout << std::endl;

        }
*/



}



// Updates position and velocity of masses
void Cube::updateEuler(){

    gravitys(false);

    std::vector<glm::vec3> forceVec;
    glm::vec3 f;



// loop throw all masses and conections
    for (int i=0; i<massVec.size(); i++) {



        f = glm::vec3(0,0,0);


        //if (i != 0 && i != 9 ) {
            for (int j = 0; j < massVec[i].connections.size(); ++j) {

                int ni = massVec[i].connections[j];

                // Check if nan
                if (massVec[i].getVelocity().x != massVec[i].getVelocity().x) {
                    return;
                }

                glm::vec3 force = calcForce(massVec[i], massVec[ni], i, ni);

                f = f + force;

            }

            forceVec.push_back(f);
        //}

    }

    //updates all masses
    for (int l = 0; l < massVec.size() ; ++l) {

            // Calculate new velocity
            glm::vec3 vel1 = massVec[l].getVelocity() + dt * (forceVec[l]) / m;
            glm::vec3 pos1 = massVec[l].getPosition() + dt * vel1;


            // Set new mass 1 state
            massVec[l].setPosition(pos1);
            massVec[l].setVelocity(vel1);



    }




}

// calculate the force that effects the mass
glm::vec3 Cube::calcForce(Mass m1, Mass m2, int m1Index, int m2Index) {

    glm::vec3 p1 = m1.getPosition();
    glm::vec3 p2 = m2.getPosition();

    glm::vec3 v1 = m1.getVelocity();
    glm::vec3 v2 = m2.getVelocity();



    double fspring, fdamper;


    double dy = p2.y - p1.y;
    double dx = p2.x - p1.x;
    double dz = p2.z - p1.z;




    double angleyx = 0;
    double angleyz = PI/2;
    if (dx != 0)
        angleyx = glm::atan(dy / dx);
    if (dz != 0)
        angleyz = glm::atan(dy / dz);

    double euclDist = glm::sqrt( glm::pow(p1.x - p2.x, 2) + glm::pow(p1.y - p2.y, 2) + glm::pow(p1.z - p2.z, 2) );
    double euclVel = glm::sqrt( glm::pow(v1.x - v2.x, 2) + glm::pow(v1.y - v2.y, 2) + glm::pow(v1.z - v2.z, 2) );



    double x = std::pow(m1.getinitialPosition().x-m2.getinitialPosition().x, 2);
    double y = std::pow(m1.getinitialPosition().y-m2.getinitialPosition().y, 2);
    double z = std::pow(m1.getinitialPosition().z-m2.getinitialPosition().z, 2);

    double distance  = std::sqrt(x+y+z) ;

    //Use This if rest length shouldn't be changed
    if(distance > di+di/10) {
        double r2 = std::sqrt(r*r*2);
        fspring = k * (euclDist - r2);
        fdamper = d * euclVel;
    } else{
        fspring = k * (euclDist - r);
        fdamper = d * euclVel;
    }




    glm::vec3 dir = glm::vec3(0, 0, 0);

    if ((v2.x - v1.x) != 0)
        dir.x = (v2.x - v1.x) / std::abs(v2.x - v1.x);

    if ((v2.y - v1.y) != 0)
        dir.y = (v2.y - v1.y) / std::abs(v2.y - v1.y);

    if ((v2.z - v1.z) != 0)
        dir.z = (v2.z - v1.z) / std::abs(v2.z - v1.z);

    if (dx < 0)
        angleyx = angleyx + PI;
    if (dz <0)
        angleyz = angleyz + PI;


    double hypyx = glm::sqrt(glm::pow(dx,2)+glm::pow(dy,2));
    double hypyz = glm::sqrt(glm::pow(dz,2)+glm::pow(dy,2));


    glm::vec3 force = glm::vec3(0, 0, 0);
    force.x = (float) (fspring * hypyx * glm::cos(angleyx) + fdamper * dir.x);
    force.y = (float) (fspring * hypyx * glm::sin(angleyx) + fdamper * dir.y);
    force.z = (float) (fspring * hypyz * glm::cos(angleyz) + fdamper * dir.z);

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
// Draws the connections of the cube
void Cube::draw()
{
    int count = 0;
    // set the line width
    glLineWidth(5.0);

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

// sets constants of cube
void Cube::setConstants(float _k, float _d, float _r) {
    k = _k;
    d = _d;
    r = _r;

}

// function to activate gravity
void Cube::gravitys(bool b) {

    if(b){
        for (int i = 0; i < massVec.size() ; ++i) {
            glm::vec3 vel1 = glm::vec3(0,0,0);
            vel1.y = massVec[i].getVelocity().y + dt * gravity.y;
            glm::vec3 pos1 = massVec[i].getPosition() + dt * vel1;
            massVec[i].setVelocity(vel1);

        }
    }

}

double Cube::distance3D(Mass m1, Mass m2) {

    double x = std::pow(m1.getPosition().x-m2.getPosition().x, 2);
    double y = std::pow(m1.getPosition().y-m2.getPosition().y, 2);
    double z = std::pow(m1.getPosition().z-m2.getPosition().z, 2);
    
    double distance  = std::sqrt(x+y+z) ;

    return distance;
}
