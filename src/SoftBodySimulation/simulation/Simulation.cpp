
/********************************************************************************
 *                                                                              *
 *  A demo 3D ball of multi-layers with deformation under non-uniform factors.  *
 *  The deformation reaction under those non-distributed influences is well     * 
 *  observed                                                                    *                                                                                 
 *                                                                              *                                                
 *  Version V1.01                                                               *
 *  Copyright by Miao Song                                                      *
 *                                                                              *
 ********************************************************************************/




//#include <GL/glui.h>
//using namespace std;

#include "Simulation.h"

// Mouse variables
int mousedown =0;                // for GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
float xMouse, yMouse, zMouse;    // for mouse point r(x,y,z) 
int closest_i, closest_j;        // Closest point index i, j 

// Keyboard variables
int   GoDir;           		   // for GLUT_KEY_LEFT,GLUT_KEY_RIGHT,GLUT_KEY_UP,GLUT_KEY_DOWN
float RotateRegX=0;              // for glRotatef() rotating direction
float RotateRegY=0;              // for glRotatef() rotating direction
float RotateRegZ=0;    		   // for glRotatef() rotating direction


int   main_window;
int   wireframe = 0;
int   segments = 8;


Object1D object1D;		  // initial the object1D
Object2D object2D;		  // initial the object2D
Object3D object3D;		  // initial the object3D


ViewSpace  box;                 // Creat a viewer space

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);  			// Define GL View Port rectangle
	glMatrixMode(GL_PROJECTION);
	gluPerspective(20.,float(Width)/float(Height), 1., 100.);
	glLoadIdentity();
    	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay(); 
}
		
void Display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  // Initialize
	//	glClearColor(.8, 0.8, 0.8, 0.0);  // Initialize	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

///*	gluPerspective(50,float(Width)/float(Height), 1, 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 //	gluLookAt(2,0,10,1,-1,6,0,1,0);  // Camera difinition		gluLookAt(2,0,10,1,-1,6,0,1,0);  // Camera difinition
//*//*	gluPerspective(40,float(Width)/float(Height), 1, 100.);	glMatrixMode(GL_MODELVIEW);	glLoadIdentity(); 	gluLookAt(2,0,7,1,0,5,0,1,0);  // Camera difinition*/
	glPointSize(8);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	box.Draw();        // Draw the view box space 	

//	object1D.Draw();

	Rotated();
//	object2D.Draw();
	object3D.Draw();
	glutSwapBuffers(); 
}

//===================================================================================


// when mouse is clicked 
void Mouse(int button, int state, int x, int y)
{
   
	xMouse = (4 *  ((float)x/(float)Width)) -2 ;
	yMouse = -((4 * ( (float)y/(float)Height))-2) ;

	if (state == GLUT_DOWN)
	{
		mousedown = 1;
	}
	else if (state == GLUT_UP)
	{
		mousedown = 0;	
	}
}

// when mouse is moving
void Motion(int x, int y)
{
	xMouse = (4 *  ((float)x/(float)Width)) -2 ;
	yMouse = -((4 * ( (float)y/(float)Height))-2 );
}



// when a rotation Key is pressed

void Keyboard(unsigned char key, int x, int y)
{     
//	ThreeDInner.Keyboard(key, x, y);		

	cout << "key = " << key << endl;

   	switch(key){
    		case 'x':
    		case 'X':
			RotateRegX+=10;			
        		glutPostRedisplay();
			break;

    		case 'y':
   		case 'Y':
			RotateRegY+=10;	
        		glutPostRedisplay();
			break;

		case 'z':
    		case 'Z':
			RotateRegZ+=10;	
        		glutPostRedisplay();
			break;

		case 'r':
    		case 'R':
			RotateRegX+=5;
       		RotateRegY+=5;
       		RotateRegZ+=5;
        		glutPostRedisplay();
			break;
   
        	default:                             
			break;              // do nothing
	}
}

void Rotated(void)
{  
// glPushMatrix();
   glRotated(RotateRegX, 1.0, 0.0, 0.0);  // Rotate 90 about X-axis 
   glRotated(RotateRegY, 0.0, 1.0, 0.0);  // Rotate 90 about X-axis 
   glRotated(RotateRegZ, 0.0, 0.0, 1.0);  // Rotate 90 about X-axis 
// glPopMatrix();
} 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// when a moving direction Key is pressed
void SpecialKeys(int key, int x, int y)
{
//	ThreeDInner.SpecialKeys(key, x, y);	
	switch (key){
		case GLUT_KEY_UP:
			 GoDir = 1;
         		 break;
		case GLUT_KEY_DOWN:
		 	 GoDir = 2;
		 	 break;
		case GLUT_KEY_LEFT:
		 	 GoDir = 3;
		 	 break;
		case GLUT_KEY_RIGHT:
			 GoDir = 4;
		 	 break;
		default:
		 	 GoDir = 0;
		 	 break; 	
	}
}


void Idle()
{
	object1D.Update(DT, mousedown != 0, xMouse, yMouse);
	object2D.Update(DT, mousedown != 0, xMouse, yMouse);
	object3D.Update(DT, mousedown != 0, xMouse, yMouse);
	glutPostRedisplay();
}

/*void motion (int mx, int my)
{
// Normalize mouse coordinates.
   xMouse = double(mx) ;
   yMouse = double(my) ;
   glutPostRedisplay();
}
*/
//======================================================================================
int main(void)
{    
	glutInitWindowPosition(200, 200); 
	glutInitWindowSize( Width, Height);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
 	main_window = glutCreateWindow("A Simulation Ball - Miao Song"); 

	glutReshapeFunc(Reshape);
    
	glEnable(GL_BLEND);                                // transparent
 	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  // transparent
	glEnable(GL_DEPTH_TEST);

//	glutPassiveMotionFunc(motion);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	/*
	GLUI *glui = GLUI_Master.create_glui( "GLUI" );

	new GLUI_Checkbox( glui, "Wireframe", &wireframe );
	(new GLUI_Spinner( glui, "Segments:", &segments ))
		->set_int_limits( 3, 60 ); 
   
	glui->set_main_gfx_window( main_window );
	GLUI_Master.set_glutIdleFunc( Idle ); 
	*/
	glutMainLoop(); 	
	return 0;
}
