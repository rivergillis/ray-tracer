# define libraries
ifeq ($(shell uname),Darwin)
LIB = -DMAC -framework OPENGL -framework GLUT
else
LIB = -lGL -lGLU -lglut
endif

CC = c++
CSTD = -std=c++11
CFLAGS = -Wall $(CSTD) -c -Wno-deprecated-declarations

hw6: hw6.o vec3d.o point3d.o ray3d.o sphere3d.o phong.o rgb.o
	$(CC) $(LIB) hw6.o vec3d.o point3d.o ray3d.o sphere3d.o phong.o rgb.o -o hw6

hw6.o: hw6.cpp constants.h
	$(CC) $(CFLAGS) hw6.cpp

vec3d.o: vec3d.cpp vec3d.h constants.h
	$(CC) $(CFLAGS) vec3d.cpp

point3d.o: point3d.h point3d.cpp constants.h
	$(CC) $(CFLAGS) point3d.cpp

ray3d.o: ray3d.h ray3d.cpp constants.h
	$(CC) $(CFLAGS) ray3d.cpp

sphere3d.o: sphere3d.h sphere3d.cpp constants.h
	$(CC) $(CFLAGS) sphere3d.cpp

phong.o: phong.h phong.cpp constants.h
	$(CC) $(CFLAGS) phong.cpp

rgb.o: rgb.h rgb.cpp constants.h
	$(CC) $(CFLAGS) rgb.cpp

clean:
	rm *.o hw6 *.gch
