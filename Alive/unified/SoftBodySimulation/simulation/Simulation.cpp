
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

int   main_window;
int   wireframe = 0;
int   segments = 8;


Object1D object1D;
//Object2D object2D;


ViewSpace  box;                              // Creat a viewer space

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);  // Define GL View Port rectangle
	glMatrixMode(GL_PROJECTION);
	gluPerspective(50.,float(Width)/float(Height), 1., 100.);
	glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay(); 
}
		
void Display(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);  // Initialize
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(50,float(Width)/float(Height), 1, 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	gluLookAt(2,0,5,0,0,0,0,1,0);  // Camera difinition

	glEnable(GL_BLEND);                                // transparent
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);  // transparent

	glPointSize(8);
	object1D.Draw();
//	object2D.Draw();


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	box.Draw();           // Draw the view box space 	


	glutSwapBuffers(); 
}

//===================================================================================


// when mouse is clicked 

void Mouse(int button, int state, int x, int y)
{
   // ThreeDInner.Mouse(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mousedown = 1;

			xMouse = SCRSIZE * 2.0 * ((float)x/(float)Width - 0.5);
			yMouse = -SCRSIZE * 2.0 * ((float)y/(float)Height - 0.5);

		}
		else if (state == GLUT_UP)
		{

	       	mousedown = 0;
			xMouse = 0;
			yMouse = 0;
	  	}
     }
}


// when mouse is moving

void Motion(int x, int y)
{
  //  ThreeDInner.Motion(x, y);

		if (mousedown)
	{
		xMouse = SCRSIZE * 2.0 * ((float)x/(float)Width - 0.5);
		yMouse = -SCRSIZE * 2.0 * ((float)y/(float)Height - 0.5);
		glutPostRedisplay();
 	}
}



// when a rotation Key is pressed

void Keyboard(unsigned char key, int x, int y)
{     
//	ThreeDInner.Keyboard(key, x, y);		
}

// when a moving direction Key is pressed

void SpecialKeys(int key, int x, int y)
{
//	ThreeDInner.SpecialKeys(key, x, y);	
}




void Idle()
{
	
	object1D.Update(DT, mousedown != 0, xMouse, yMouse);
//	object2D.Update(DT, mousedown != 0, xMouse, yMouse);


  glutPostRedisplay();
}

void motion (int mx, int my)
{
   // Normalize mouse coordinates.
   xMouse = double(mx) ;
   yMouse = double(my) ;
   glutPostRedisplay();
}


//======================================================================================

//	Function main()
 

int main(void)
{
    
	glutInitWindowPosition(200, 200); 
	glutInitWindowSize( Width, Height);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    main_window = glutCreateWindow("A Simulation Ball - Miao Song"); 

 
	glutReshapeFunc(Reshape);
    

//	glutPassiveMotionFunc(motion);
    glutIdleFunc(Idle);
	glutDisplayFunc(Display);

	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeys);
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
