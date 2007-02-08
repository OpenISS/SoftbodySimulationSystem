#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;


#define DT      0.003f			// Delta time in derivatives	

#define KS 1300.0f				// Hooke spring constant
#define KD 100.0f				// Hooke spring damping constant

#define RKS 755.0f				// radium spring constant
#define RKD 35.0f				// radium spring damping constant

#define MOUSE_KS 25.0f			// mouse spring constant
#define MOUSE_KD 25.0f			// mouse damping constant
#define MOUSE_REST 2.0f			// mouse rest lenth


#define PI     3.1416f			// Circle = 2*PI*RADIUS
	

#define GY        -10.0f		// Gravity
#define WIND      10.0f			// External force, such as wind force
#define PRESSURE 40.0f			// Pressure constant

#define LIMIT     2.0f			// Collision detection floor and wall screen size
#define Width     500			// Display window width
#define Height    500		    // Display window Height

#define SCRSIZE 10				// screen size factor for mouse dragging

#define MAX_POINTS_SPRINGS 40											//reserve temp space particle and spring
#define NUMPOINTS   30													//default number of particles on a object
#define NUMSPRINGS  NUMPOINTS											//default number of springs on a object

#define MASS 1.0f				// point mass on the rings = 5.0
#define RING_RADIUS 0.5f		// default radius of the 2D and 3D object


enum dimensionality {DIM1D, DIM2D, DIM3D};								//object type, 1D, 2D, and 3D
enum integrator_type {EULER, MIDPOINT, RK4};							//integrator type, EULER, MIDPOINT, RK4
enum spring_type { SPRING_STRUCTURAL, SPRING_RADIUM, SPRING_SHEAR };	//spring type, structrual, radium, shear





#endif /* _GLOBAL_H */
