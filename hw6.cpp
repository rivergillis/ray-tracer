#include "vec3d.h"
#include "point3d.h"
#include "ray3d.h"
#include "sphere3d.h"
#include "rgb.h"
#include "phong.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Global variables
constexpr int kX = 800;
constexpr int kY = 800;
unsigned char image[kX][kY][3];

// Single-dimension vector. Address with kX*[row] + col
std::vector<Ray3D> rays;

// Projection plane is at (0, 0, 0) on Z = 0
constexpr int kProjectionPlaneDistance = 0;

// The camera is at (0,0,-distance)
int distance = 8;

std::pair<int, int> ImgToWorld(int img_x, int img_y) {
  // middle of image is (0,0,0) in world coordinates
  // so shift everything left by k[X/Y]/2
  int world_x = img_x - kX/2;
  int world_y = img_y - kY/2;
  return std::make_pair(world_x, world_y);
}

void init() {
  // Initialize OpenGL
  glClearColor(0.0, 0.0, 0.0, 1.0);

  // Print command menu
  std::cout << "Program commands:\n"
    << "   'q' - quit program\n";
}

// Set up the rays to point from the camera to the projection plane
void InitRays() {
  Point3D camera(0, 0, -1 * distance);

  rays.reserve(kX * kY);
  for (int row = 0; row < kX; row++) {
    for (int col = 0; col < kY; col++) {
      //std::cout << "(" << kX*row+col << ") row: " << row << "col: " << col << std::endl;
      std::pair<int, int> world_x_y = ImgToWorld(row, col);
      Point3D projection_point(world_x_y.first, world_x_y.second, kProjectionPlaneDistance);

      rays.emplace_back(camera, projection_point);
    }
  }
}

void display() {
  // TO BE ADDED

  // Display image
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(kX, kY, GL_RGB, GL_UNSIGNED_BYTE, image);
  glFlush();
}


void keyboard(unsigned char key, int x, int y) {
  // End program
  if (key == 'q') {
    exit(0);
  }

  // TO BE ADDED

  // Display image
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  // Create OpenGL window
  glutInit(&argc, argv);
  glutInitWindowSize(kX, kY);
  glutInitWindowPosition(0, 0);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutCreateWindow("Ray Trace");
  init();

  InitRays();

  // Specify callback function
  //glutDisplayFunc(display);
  //glutKeyboardFunc(keyboard);
  //glutMainLoop();
  return 0;
}