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


#define DT      0.003f    // Delta time in derivatives	

#define KS 1300.0f    // Hooke spring constant
#define KD 100.0f     // Hooke spring damping constant

#define RKS 755.0f            // radium spring constant
#define RKD 35.0f            // radium spring damping constant

#define PI     3.1416f    // Circle = 2*PI*RADIUS
//#define RADIUS    1.0f    // Ball initial radius	

#define GY        -10.0f    // Gravity
#define WIND      10.0f    // External force, such as wind force
#define LIMIT     2.0f    // Screen size
#define PRESSURE 40.0f    // Pressure constant

#define Width     500     // Display window width
#define Height    500     // Display window Height
#define RESTLEN   2.2f    // Mouse rest length  

#define SCRSIZE 10	        // screen size factor


          // radium spring damping constant
#define MOUSE_KS 25.0f		// mouse spring constant
#define MOUSE_KD 25.0f		// mouse damping constant
#define MOUSE_REST 2.0f		// mouse rest lenth

#define LIMIT     2.0f    // Screen size


enum dimensionality {DIM1D, DIM2D, DIM3D};
enum integrator_type {EULER, MIDPOINT, RK4};
enum spring_type { SPRING_STRUCTURAL, SPRING_RADIUM, SPRING_SHEAR };


#define NUMPOINTS   30
#define NUMSPRINGS  NUMPOINTS
#define DEFAULTPRESSURE 25.0

#define MASS 1.0f           // point mass on the rings = 5.0
#define RING_RADIUS 0.5f	// default radius of the ball
#define MAX_POINTS_SPRINGS 40



#endif /* _GLOBAL_H */
