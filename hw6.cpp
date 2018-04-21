#include "vec3d.h"
#include "point3d.h"
#include "ray3d.h"
#include "sphere3d.h"
#include "rgb.h"
#include "phong.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
constexpr int kX = 800;
constexpr int kY = 800;
unsigned char image[kX][kY][3];


//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   // Initialize OpenGL
   glClearColor(0.0, 0.0, 0.0, 1.0);

   // Print command menu
   std::cout << "Program commands:\n"
        << "   'q' - quit program\n";
}

//---------------------------------------
// Display callback for OpenGL
//---------------------------------------
void display()
{
   // TO BE ADDED
 
   // Display image
   glClear(GL_COLOR_BUFFER_BIT);
   glDrawPixels(kX, kY, GL_RGB, GL_UNSIGNED_BYTE, image);
   glFlush();
}

//---------------------------------------
// Keyboard callback for OpenGL
//---------------------------------------
void keyboard(unsigned char key, int x, int y)
{
   // End program
   if (key == 'q')
      exit(0);

   // TO BE ADDED

   // Display image
   glutPostRedisplay();
}

//---------------------------------------
// Main program
//---------------------------------------
int main(int argc, char *argv[])
{
   // Create OpenGL window
   glutInit(&argc, argv);
   glutInitWindowSize(kX, kY);
   glutInitWindowPosition(0, 0);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutCreateWindow("Ray Trace");
   init();

   // Specify callback function
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
