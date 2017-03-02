#include <GL/glew.h>
#include <glm/glm.hpp>

#if defined (__APPLE_CC__)
#include <OpenGL/gl.h>
#include<OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include<GL/glu.h>
#endif

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

#include "Cube.h"




/* -- Global Variables -- */

//float up = 0, down = 0, left = 0, right = 0;
float transX=0, transY=0, transZ=0;

Cube cube1 = Cube();



/* - Function Declarations - */

//void keyboard(unsigned char key, int x, int y);
static void error_callback(int error, const char* description);
//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int main(void)
{

    cube1.setConstans(200, 40); //Jelly


    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glClearColor(0.6, 0.9, 1.0, 1.0);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    glfwSwapInterval(1);



    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        unsigned int GridSizeX = 16;
        unsigned int GridSizeY = 16;
        unsigned int SizeX = 1;
        unsigned int SizeY = 1;

        glfwGetFramebufferSize(window, &width, &height);


        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glEnable(GL_CULL_FACE);
        glEnable(GL_NORMALIZE);
        glEnable(GL_DEPTH_TEST);
        glCullFace(GL_FRONT);

        glFrustum(-ratio, ratio, -1.0f, 1.0f, 1, 50);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glCullFace(GL_FRONT);
        glLoadIdentity();



        gluLookAt(0.0f, 0.5f, 3.0f,
                  (cube1.getCenter().x)/2-0.5, 0.0f, (cube1.getCenter().z)/2,
                  0.0f, 1.0f, 0.0f);




        /* ----------------------- Render code ---------------------------- */




        glPushMatrix();
        glColor3f(0.5f, 0.5f, 0.5f);
        glPushMatrix();
        glTranslatef(-1.4f, 0, -0.5f);
        cube1.draw();
        cube1.updateEuler();




        /* ----------------------------------------------------------------- */

        glfwSwapBuffers(window);
        glfwPollEvents();

    }



    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}








