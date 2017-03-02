//
// Created by Johan on 2017-02-10.
//

#include "Cube.h"
#include <iostream>
#include <typeinfo>


void Cube::genrateCube(int x, int y, int z){

    int numMass = x*y*z;
    int numXY = x*y;
    std::cout << numMass << std::endl;
    int xpos = 0;
    int ypos = 0;
    int zpos = 0;

        float abs = 0.2;
    for (int i = 0; i < numMass ; ++i) {

        std::cout << xpos << ", " << ypos <<  ", " << zpos << std::endl;

        massVec.push_back(Mass(glm::vec3(xpos*abs,ypos*abs,zpos*abs), glm::vec3(-1,-1,-1))); // BACK-BOT-LEFT
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
            std::cout << j - 1 << ", ";

        } else if (j % x == 0) {
            massVec[j].xCon2 = j + 1;
            std::cout << j + 1 << ", ";
        } else {
            massVec[j].xCon = j - 1;
            massVec[j].xCon2 = j + 1;
            std::cout << "X(" << j - 1 << ", ";
            std::cout << j + 1 << "), ";
        }


        if (((j - numXY * (j / numXY)) / x) == 0) {
            massVec[j].yCon2 = j + x;
            std::cout << massVec[j].yCon2 << ", " << std::endl;
        } else if (((j - numXY * (j / numXY)) / x) == y - 1) {
            massVec[j].yCon = j - x;
            std::cout << massVec[j].yCon << ", " << std::endl;
        } else {
            massVec[j].yCon = j - x;
            massVec[j].yCon2 = j + x;
            std::cout << "y( " << massVec[j].yCon << ", " << massVec[j].yCon2 << "), " << std::endl;
        }
        if (z > 1) {

            if (((j - numXY * (j / numXY)) / numXY) == 0) {
                massVec[j].zCon2 = j + numXY;
                //std::cout << j-numXY << " x"<< std::endl ;
                std::cout << massVec[j].zCon2 << " " << std::endl;

            } else if (((j - numXY * (j / numXY)) / numXY) == z - 1) {
                massVec[j].zCon = j - numXY;
                //std::cout << j+numXY << std::endl ;
                std::cout << massVec[j].zCon << ", " << std::endl;

            } else {
                massVec[j].zCon = j - x;
                massVec[j].zCon2 = j + x;
                std::cout << "z( " << massVec[j].zCon << ", " << massVec[j].zCon2 << ")" << std::endl;
            }
        }


    }





    /*
    massVec[0].xCon=1; //Mass 0
    massVec[0].yCon=2;
    massVec[0].zCon=4;

    massVec[1].xCon=0; //Mass 1
    massVec[1].yCon=3;
    massVec[1].zCon=5;

    massVec[2].xCon=3; //Mass 2
    massVec[2].yCon=0;
    massVec[2].zCon=6;

    massVec[3].xCon=2; //Mass 3
    massVec[3].yCon=1;
    massVec[3].zCon=7;

    massVec[4].xCon=5; //Mass 4
    massVec[4].yCon=6;
    massVec[4].zCon=0;

    massVec[5].xCon=4; //Mass 5
    massVec[5].yCon=7;
    massVec[5].zCon=1;

    massVec[6].xCon=7; //Mass 6
    massVec[6].yCon=4;
    massVec[6].zCon=2;

    massVec[7].xCon=6; //Mass 7
    massVec[7].yCon=5;
    massVec[7].zCon=3;
*/


}


Cube::Cube(){

    genrateCube(50,50,50);

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

    float sign[3];

    glm::vec3 massXPos;
    glm::vec3 massYPos;
    glm::vec3 massZPos;

    for (int i=0; i<massVec.size(); i++) {

        // Ett värde med ett eller noll ??? KANSKE!!!

        int ax  = 0;
        int ax2 = 0;
        int ay  = 0;
        int ay2 = 0;
        int az  = 0;
        int az2 = 0;

        if(massVec[i].xCon != -1){
            Mass massX = massVec[massVec[i].xCon];
            massXPos += massX.getPosition();

        }
        if(massVec[i].xCon2 != -1){
            Mass massX2 = massVec[massVec[i].xCon2];
            massXPos += massX2.getPosition();
        }

        if(massVec[i].yCon != -1){
            Mass massY = massVec[massVec[i].yCon];
            massYPos += massY.getPosition();
            ay = 1;
        }
        if(massVec[i].yCon2 != -1){
            Mass massY2 = massVec[massVec[i].yCon2];
            massYPos += massY2.getPosition();
            ay2 = 1;
        }

        if(massVec[i].zCon != -1){
            Mass massZ = massVec[massVec[i].zCon];
            massZPos += massZ.getPosition();
            az = 1;
        }
        if(massVec[i].zCon2 != -1){
            Mass massZ2 = massVec[massVec[i].zCon2];
            massZPos += massZ2.getPosition();
            az2 = 1;
        }

        sign[0] = -glm::normalize((massXPos.x + massXPos2.x - massVec[i].getPosition().x));
        sign[1] = -glm::normalize((massYPos.y + massYPos2.y - massVec[i].getPosition().y));
        sign[2] = -glm::normalize((massZPos.z + massZPos2.z - massVec[i].getPosition().z));

        /*
        Fource[i]=k*(massXPos-massVec[i].getPosition()+sign[0]*sXlenght)
             +d*(massXPos-massVec[i].getVelocity());      //x-led
        Fource[i]+=k*(massYPos-massVec[i].getPosition()+sign[1]*sYlenght)
              +d*(massYPos-massVec[i].getVelocity())-m*g;    //y-led
        Fource[i]+=k*(massZPos-massVec[i].getPosition()+sign[2]*sZlenght)
              +d*(massZPos-massVec[i].getVelocity());         //z-led
*/


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

        //std::cout << conx2 << " x2"<< std::endl;
        //std::cout << conx << " x"<< std::endl;
        //  std::cout << i << " : ";



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
