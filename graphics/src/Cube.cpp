//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>

#define PI 3.14159265358979323846  /* pi */

Cube::Cube(){

    generateCube(3, 3, 3);

}

void Cube::generateCube(int x, int y, int z){

    int numMass = x*y*z;
    //int numXY = x*y;
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

    // connects all the nearby masses
    for (int j = 0; j < massVec.size(); ++j) {
        std::cout << "Mass " << j << ": " ;
        for (int i = 0; i < massVec.size() ; ++i) {
            if(distance3D(massVec[j], massVec[i]) <= std::sqrt(di*di*2) + di/10 && j!= i){
                massVec[j].connect(i);
                std::cout << i << ", ";
            }
        }
        std::cout << std::endl;


    }



}



// Updates position and velocity of masses
void Cube::updateEuler(){
    
    std::vector<glm::vec3> forceVec;
    glm::vec3 f;



// loop throw all masses and conections
    for (int i=0; i<massVec.size(); i++) {



        if(gravity == true) {
            f = glm::vec3(0, -9.82, 0);
        } else {
            f = glm::vec3(0, 0, 0);
        }


            for (int j = 0; j < massVec[i].connections.size(); ++j) {

                int ni = massVec[i].connections[j]; // Get neighbor index

                // If mass is given as neighbor with itself
                if (ni == i){
                    std::cout << "Mass cannot be connected with itself" << std::endl;
                    return;
                }

                // Check if nan
                if (massVec[i].getVelocity().x != massVec[i].getVelocity().x) {
                    return;
                }
                if (massVec[i].getVelocity().y != massVec[i].getVelocity().y) {
                    return;
                }
                if (massVec[i].getVelocity().z != massVec[i].getVelocity().z) {
                    return;
                }


                glm::vec3 force = calcForce(massVec[i], massVec[ni]);



                f = f + force;




            }

            forceVec.push_back(f);


    }

    //updates all masses
    for (int l = 0; l < massVec.size() ; ++l) {

        // Calculate new velocity
        glm::vec3 vel1 = massVec[l].getVelocity() + dt * (forceVec[l]) / m;
        // Calculate new position
        glm::vec3 pos1 = massVec[l].getPosition() + dt * vel1;


        // set position and velocity
        massVec[l].setPosition(pos1);
        massVec[l].setVelocity(vel1);
    }




}

// calculate the force that effects the mass
glm::vec3 Cube::calcForce(Mass m1, Mass m2) {


    // Find position of mass 1 and mass 2
    glm::vec3 p1 = m1.getPosition();
    glm::vec3 p2 = m2.getPosition();

    // Find velocity of mass 1 and mass 2
    glm::vec3 v1 = m1.getVelocity();
    glm::vec3 v2 = m2.getVelocity();



    double fspring, fdamper;


    // Find angle between p1 and p2
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    double angleyx = std::atan(dy / dx);
    double angleyz = std::atan(dy / dz);


    // if angleyx || angleyz is nan
    if(angleyx != angleyx) {
        angleyx = 0;
    }
    if(angleyz != angleyz) {
        angleyz = PI/2;
    }


    //Get euclidean distance and velocity of masses
    double euclDist = glm::sqrt( glm::pow(p1.x - p2.x, 2) + glm::pow(p1.y - p2.y, 2) + glm::pow(p1.z - p2.z, 2) );
    double euclVel = glm::sqrt( glm::pow(v1.x - v2.x, 2) + glm::pow(v1.y - v2.y, 2) + glm::pow(v1.z - v2.z, 2) );




    double x = std::pow(m1.getinitialPosition().x-m2.getinitialPosition().x, 2);
    double y = std::pow(m1.getinitialPosition().y-m2.getinitialPosition().y, 2);
    double z = std::pow(m1.getinitialPosition().z-m2.getinitialPosition().z, 2);
    double distance = std::sqrt(x+y+z) ;


    //  Spring force & Damper force. Damper force will be in the opposite direction of spring force
    if(distance > di+di/10) {
        // diagonal connection
        double r2 = std::sqrt(r*r*2);
        fspring = ks * (euclDist - r2);
        fdamper = kd * euclVel;
    } else{
        fspring = ks * (euclDist - r);
        fdamper = kd * euclVel;
    }



    // Find direction of damper force
    glm::vec3 dir = glm::vec3(0, 0, 0);
    dir.x = (v2.x - v1.x) / glm::abs(v2.x - v1.x);
    dir.y = (v2.y - v1.y) / glm::abs(v2.y - v1.y);
    dir.z = (v2.z - v1.z) / glm::abs(v2.z - v1.z);

    // If division by zero above
    if(dir.x != dir.x){
        dir.x = 0;
    }
    if(dir.y != dir.y){
        dir.y = 0;
    }
    if(dir.z != dir.z){
        dir.z = 0;
    }

    // For proper angles since atan will not take direction into consideration
    if (dx < 0)
        angleyx = angleyx + PI;
    if (dz <0)
        angleyz = angleyz + PI;


    double hypyx = glm::sqrt(glm::pow(glm::abs(dx),2)+glm::pow(glm::abs(dy),2));
    double hypyz = glm::sqrt(glm::pow(glm::abs(dz),2)+glm::pow(glm::abs(dy),2));


    double cosyx = glm::cos(angleyx);
    double sinyx = glm::sin(angleyx);
    double cosyz = glm::cos(angleyz);

    //Calculate force
    glm::vec3 force = glm::vec3(0, 0, 0);
    force.x = (float) (hypyx * (fspring * cosyx + fdamper * dir.x));
    force.y = (float) (hypyx * (fspring * sinyx + fdamper * dir.y));
    force.z = (float) (hypyz * (fspring * cosyz + fdamper * dir.z));

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
    ks = _k;
    kd = _d;
    r = _r;

}

double Cube::distance3D(Mass m1, Mass m2) {

    double x = std::pow(m1.getPosition().x-m2.getPosition().x, 2);
    double y = std::pow(m1.getPosition().y-m2.getPosition().y, 2);
    double z = std::pow(m1.getPosition().z-m2.getPosition().z, 2);
    
    double distance  = std::sqrt(x+y+z) ;

    return distance;
}
