//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>
#include <typeinfo>

Cube::Cube(){

    genrateCube(5,5,5);

}

void Cube::genrateCube(int x, int y, int z){

    int numMass = x*y*z;
    int numXY = x*y;
    std::cout << numMass << std::endl;
    int xpos = 0;
    int ypos = 0;
    int zpos = 0;

        float abs = 0.4;
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

        if ((j + 1) % x == 0) {
            massVec[j].xCon = j - 1;
            massVec[j].connections.push_back(j - 1);
            std::cout << "x: "<<j - 1 << ", ";

        } else if (j % x == 0) {
            massVec[j].xCon2 = j + 1;
            massVec[j].connections.push_back(j + 1);
            std::cout <<"x: " <<j + 1 << ", ";
        } else {
            massVec[j].xCon = j - 1;
            massVec[j].xCon2 = j + 1;
            massVec[j].connections.push_back(j - 1);
            massVec[j].connections.push_back(j + 1);
            std::cout << "X(" << j - 1 << ", ";
            std::cout << j + 1 << "), ";
        }


        if (((j - numXY * (j / numXY)) / x) == 0) {
            massVec[j].yCon2 = j + x;
            massVec[j].connections.push_back(j + x);
            std::cout << massVec[j].yCon2 << ", " << std::endl;
        } else if (((j - numXY * (j / numXY)) / x) == y - 1) {
            massVec[j].yCon = j - x;
            massVec[j].connections.push_back(j - x);
            std::cout << massVec[j].yCon << ", " << std::endl;
        } else {
            massVec[j].yCon = j - x;
            massVec[j].yCon2 = j + x;
            massVec[j].connections.push_back(j - x);
            massVec[j].connections.push_back(j + x);
            std::cout << "y( " << massVec[j].yCon << ", " << massVec[j].yCon2 << "), " << std::endl;
        }
        if (z > 1) {

            std::cout << "j: " << j << " numXY: " << numXY << " j / numXY: " << j / numXY <<   " val: " << ((j - numXY * (j / numXY)) / numXY) << std::endl;

            if ((((j / numXY)) ) == 0) {
                massVec[j].zCon2 = j + numXY;
                massVec[j].connections.push_back(j + numXY);
                //std::cout << j-numXY << " x"<< std::endl ;
                std::cout << massVec[j].zCon2 << " " << std::endl;
                std::cout << "z1" << std::endl;

            } else if (( (j / numXY))  == z - 1) {
                massVec[j].zCon = j - numXY;
                massVec[j].connections.push_back(j - numXY);
                //std::cout << j+numXY << std::endl ;
                std::cout << massVec[j].zCon << ", " << std::endl;
                std::cout << "z2" << std::endl;


            } else {
                massVec[j].zCon = j - x;
                massVec[j].zCon2 = j + x;
                massVec[j].connections.push_back(j - numXY);
                massVec[j].connections.push_back(j + numXY);
                std::cout << "z( " << massVec[j].zCon << ", " << massVec[j].zCon2 << ")" << std::endl;
            }
        }

        std::cout << "conections: " <<  massVec[j].connections.size() << std::endl;

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

    glm::vec3 massXPos;
    glm::vec3 massYPos;
    glm::vec3 massZPos;

    for (int i=0; i<massVec.size(); i++) {





    }



    for (int i=0; i<massVec.size(); i++){
       // massVec[i].setVelocity(massVec[i].getVelocity()+Fource[i]*h/m);
       // massVec[i].setPosition(massVec[i].getPosition()+massVec[i].getVelocity()*h);

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

void Cube::setConstans(float _k, float _d) {
        k=_k;
        d=_d;
}
