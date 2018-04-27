#include "vec3d.h"
#include "point3d.h"
#include "ray3d.h"
#include "sphere3d.h"
#include "rgb.h"
#include "phong.h"
#include "constants.h"

#include <iostream>
#include <vector>
#include <utility>
#include <cstdio>
#include <cstdlib>
#include <limits>
#ifdef MAC
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

constexpr int kX = 800;
constexpr int kY = 800;
// Note: When rendered, image[0][0] is bottom-left hand corner
unsigned char image[kX][kY][3];

// Projection plane is at (0, 0, 0) on Z = 0
constexpr int kProjectionPlaneDistance = 0;

// The camera is at (0,0,-distance)
int distance = 800;

// Single-dimension vector. Address with kX*[row] + col
std::vector<Ray3D> rays;

// The list of spheres to render
std::vector<Sphere3D> spheres;

Phong phong;
// Light source
Point3D light_location(200, 200, 20);
Rgb light_color(1,1,1);

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
  rays.clear();
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
  spheres.emplace_back(Point3D(0,0, 300), 200, 0.3, 0.4, 0.3, 4, Rgb(0, 1, 1));
  spheres.emplace_back(Point3D(0, -400, 600), 100, 0.3, 0.4, 0.3, 4, Rgb(1, 0, 1));
//  spheres.emplace_back(Point3D(100, -300, 200), 100, 0.3, 0.4, 0.3, 4, Rgb(0, 0, 1));
//  spheres.emplace_back(Point3D(300, 0, 100), 120, 0.3, 0.4, 0.3, 4, Rgb(1, 1, 1));
}

void InitPhong() {
  phong.SetCamera(Point3D(0, 0, -1 * distance));
}

// Cast the ray until we reach the limit on any axis
int CastRay(const Ray3D& ray, Point3D* intersection, Vec3D* normal) {
  Point3D closest_intersection(0,0,std::numeric_limits<double>::max());
  Vec3D normal_of_closest(0,0,0);
  int intersection_idx = -1;

  for (int i = 0; i < spheres.size(); i++) {
    Sphere3D sphere = spheres[i];
    Point3D intersection_point(0,0,0);
    Vec3D intersection_normal(0,0,0);
    if (sphere.GetIntersection(ray, intersection_point, intersection_normal)) {
      // Only want sphere that was first hit
      if (intersection_point.getZ() <= closest_intersection.getZ()) {
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

void SetImage(int x, int y, const Point3D& intersection_point, const Vec3D& normal, Sphere3D sphere, bool is_in_shadow) {
  double obj_d = is_in_shadow ? 0 : sphere.D();
  double obj_s = is_in_shadow ? 0 : sphere.S();

  Vec3D intersection_to_light = intersection_point.VecTo(light_location);
  phong.SetLight(light_color, intersection_to_light);
  phong.SetObject(sphere.Color(), sphere.A(), obj_d, obj_s, sphere.Alpha());
  Rgb shade = phong.GetShade(intersection_point, normal);

  // Set the color of the pixel
  std::vector<unsigned char> denormed = shade.Denormalized();
  image[x][y][0] = denormed[0];
  image[x][y][1] = denormed[1];
  image[x][y][2] = denormed[2];
}

void clearImage() {
  for (int row = 0; row < kX; row++) {
    for (int col = 0; col < kY; col++) {
      image[row][col][0] = 0;
      image[row][col][1] = 0;
      image[row][col][2] = 0;
    }
  }
}

bool PointInShadow(int sphere_index, Point3D start_point) {
  Ray3D point_to_light(start_point, light_location);

  for (int i = 0; i < spheres.size(); i++) {
    // Don't try to intersect with out own sphere
    if (i == sphere_index) { continue; }

    Sphere3D sphere = spheres[i];
    Point3D intersection_point(0,0,0);
    Vec3D intersection_normal(0,0,0);
    if (sphere.GetIntersection(point_to_light, intersection_point, intersection_normal)) {
      return true;
    }
  }
  return false;
}

void display() {
  clearImage();

  for (int row = 0; row < kX; row++) {
    for (int col = 0; col < kY; col++) {
      Ray3D ray = rays[kX*row + col];

      Point3D intersection_point(0,0,0);
      Vec3D intersection_normal(0,0,0);
      int sphere_index = CastRay(ray, &intersection_point, &intersection_normal);
      if (sphere_index != -1) {
        bool is_in_shadow = PointInShadow(sphere_index, intersection_point);
        // std::cout << "ray intersected\n";
        SetImage(row, col, intersection_point, intersection_normal, spheres[sphere_index], is_in_shadow);
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
  } else if (key == 'w') {
    distance -= 500;
  } else if (key == 's') {
    distance += 500;
  } else if (key == 'h') {
    light_location.setX(light_location.getX() - 20);
  } else if (key == 'j') {
    light_location.setY(light_location.getY() - 20);
  } else if (key == 'k') {
    light_location.setY(light_location.getY() + 20);
  } else if (key == 'l') {
    light_location.setX(light_location.getX() + 20);
  }

  InitPhong();
  InitRays();

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