#include <GL/glew.h>
#include <glm/glm.hpp>

#if defined (__APPLE_CC__)
#include <OpenGL/gl.h>
#include<OpenGL/glu.h>
#else
    #include <GL/gl.dt>
    #include<GL/glu.dt>
#endif

#include <GLFW/glfw3.h>
#include <iostream>

#include "Cube.h"
#include "Functions.h"



/* - Function Declarations - */
static void error_callback(int error, const char* description);


int main(void)
{


    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
    GLFWwindow* window; // GLFW struct to hold information about the window
    glfwSetErrorCallback(error_callback);

    double fps = 0.0f;  // FPS - Frames Per Secound

    // Initialise GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());




    // Creats Window
    window = glfwCreateWindow(vidmode->width/2, vidmode->height/2, "Soft", NULL, NULL);
    if (!window)
    {
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }

    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);

    printf("GL vendor:       %s\n", glGetString(GL_VENDOR));
    printf("GL renderer:     %s\n", glGetString(GL_RENDERER));
    printf("GL version:      %s\n", glGetString(GL_VERSION));
    printf("Desktop size:    %d x %d pixels\n", vidmode->width, vidmode->height);

    Cube cube1 = Cube();
    cube1.setConstants(400, 2, 1.0); // sets value: spring, damper, rest length
    glLoadIdentity();


    glfwSwapInterval(0); // 0 or 1





    while (!glfwWindowShouldClose(window))
    {


        fps = Functions::displayFPS(window);

        // Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.6f, 0.9f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST); // Use the Z buffer
        glEnable(GL_CULL_FACE);  // Use back face culling
        glCullFace(GL_BACK);


        float ratio;
        int width, height;


        glfwGetFramebufferSize(window, &width, &height);


        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glEnable(GL_NORMALIZE);

        glFrustum(-ratio, ratio, -1.0f, 1.0f, 1, 50);

        gluLookAt(3.0f, 3.0f, -3.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


        /* ----------------------- Render code ---------------------------- */

        glPushMatrix();

        glColor3f(1.0f, 0.5f, 0.5f); // set cube collor



            glPushMatrix();
            cube1.draw(); // Draw connections
            cube1.updateEuler(); // Update masses

            cube1.draw(); // Draw connections

        glPopMatrix();






        /* ----------------------------------------------------------------- */



        glfwSwapBuffers(window);
        glfwPollEvents();

        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

    }



    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}








