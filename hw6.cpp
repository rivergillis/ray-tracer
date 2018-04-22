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

constexpr int kX = 800;
constexpr int kY = 800;
unsigned char image[kX][kY][3];

// Projection plane is at (0, 0, 0) on Z = 0
constexpr int kProjectionPlaneDistance = 0;

// The camera is at (0,0,-distance)
int distance = 8;

// Single-dimension vector. Address with kX*[row] + col
std::vector<Ray3D> rays;

// The list of spheres to render
std::vector<Sphere3D> spheres;

Phong phong;
// Light source
Point3D light_location(10, 10, 5);
Rgb light_color(1.0, 1.0, 1.0);

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
      std::pair<int, int> world_x_y = ImgToWorld(row, col);
      Point3D projection_point(world_x_y.first, world_x_y.second, kProjectionPlaneDistance);

      rays.emplace_back(camera, projection_point);
    }
  }
}

void InitSpheres() {
  spheres.emplace_back(Point3D(0,0,10), 5, 0.3, 0.4, 0.3, 4, Rgb(0.9, 0.1, 0.1));
}

void InitPhong() {
  // Ideally this information would be stored in the sphere object
  phong.SetCamera(Point3D(0, 0, -1 * distance));
  // SetLight has to be done on the surface
}

// Cast the ray until we reach the limit on any axis
bool CastRay(const Ray3D& ray, Point3D* intersection, Vec3D* normal) {
  Point3D closest_intersection(0,0,0);
  Vec3D normal_of_closest(0,0,0);
  int intersection_idx = -1;

  for (int i = 0; i < spheres.size(); i++) {
    Sphere3D sphere = spheres[i];
    Point3D intersection_point(0,0,0);
    Vec3D intersection_normal(0,0,0);
    if (sphere.GetIntersection(ray, intersection_point, intersection_normal)) {
      // Only want sphere that was first hit
      if (intersection_point.getZ() < closest_intersection.getZ()) {
        closest_intersection = intersection_point;
        normal_of_closest = intersection_normal;
        intersection_idx = i;
      }
    }
  }

  intersection->setX(closest_intersection.getX());
  intersection->setY(closest_intersection.getY());
  intersection->setZ(closest_intersection.getZ());
  normal->Set(normal_of_closest);

  return intersection_idx;
}

void SetImage(int x, int y, const Point3D& intersection_point, const Vec3D& normal, Sphere3D sphere) {
  Vec3D intersection_to_light = intersection_point.VecTo(light_location);
  phong.SetLight(light_color, intersection_to_light);
  phong.SetObject(sphere.Color(), sphere.A(), sphere.D(), sphere.S(), sphere.Alpha());
  Rgb shade = phong.GetShade(intersection_point, normal);
  image[x][y][0] = shade.DenormR();
  image[x][y][1] = shade.DenormG();
  image[x][y][2] = shade.DenormB();
  std::cout << "set img x: " << x << " y: " << y << " - " << shade.ToString(true) << std::endl;
}

void display() {
  for (int row = 0; row < kX; row++) {
    for (int col = 0; col < kY; col++) {
      Ray3D ray = rays[kX*row + col];

      Point3D intersection_point(0,0,0);
      Vec3D intersection_normal(0,0,0);
      int sphere_index = CastRay(ray, &intersection_point, &intersection_normal);
      if (sphere_index != -1) {
        SetImage(row, col, intersection_point, intersection_normal, spheres[sphere_index]);
      }
    }
  }

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
  InitSpheres();
  InitPhong();

  // Specify callback function
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}