#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <GL/glu.h>
#include <stdlib.h>
#include <vector>

using namespace std;


#define DT      0.003f    // Delta time in derivatives	

#define KS 300.0f    // Hooke spring constant
#define KD 20.0f     // Hooke spring damping constant

#define RKS 550.0f            // radium spring constant
#define RKD 50.0f            // radium spring damping constant

//#define KS 755.0f    // Hooke spring constant
//#define KD 35.0f     // Hooke spring damping constant


#define PI     3.1416f    // Circle = 2*PI*RADIUS
#define RADIUS    1.0f    // Ball initial radius	

#define GY        0.0f    // Gravity
#define WIND      10.0f    // External force, such as wind force
#define LIMIT     2.0f    // Screen size
#define PRESSURE 500.0f    // Pressure constant

#define Width     500     // Display window width
#define Height    500     // Display window Height
#define RESTLEN   2.2f    // Mouse rest length  

#define SCRSIZE 9	        // screen size factor


          // radium spring damping constant
#define MOUSE_KS 15.0f		// mouse spring constant
#define MOUSE_KD 15.0f		// mouse damping constant
#define MOUSE_REST 2.0f		// mouse rest lenth

// Mouse variables
extern int mousedown;                // for GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
extern float xMouse, yMouse, zMouse;    // for mouse point r(x,y,z) 
extern int closest_i, closest_j;        // Closest point index i, j 
extern int NUMS;