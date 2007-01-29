
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

int   main_window;
int   wireframe = 0;
int   segments = 8;

int NUMP=2;
int NUMS=1;


float Mass1 =   10.0f, Mass2 =   1.0f;
float Ks1   =700.0f, Ks2   = 100.0f;
float Kd1   =  45.0f, Kd2   =  1.0f;
float Rad1  =   1.0f, Rad2  =   4.0f; 
float Press1 = 10.0f, Press2=  50.0f; //(orignal press2=50;)


//int PosX=0;
//int PosY=0;


Object3D ThreeDInner(Mass1, Ks1, Kd1,  Press1);   //	Creat a ball object globally
//Ball outer(Mass2, Ks2, Kd2, Rad2, Press2);

//Ball OneD(Mass1, Ks1, Kd1);

//Spring OneDSpring[1];
//Particle OneDPoint[2];

Object1D object1D;
Object2D object2D;


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
		object2D.Draw();

     
		/*	glPushMatrix();

		glRotatef(xMouse, 0.0, 1.0, 1.0);

          ThreeDInner.Rotated();      // Rotate about X-axis, Y-axis, and/or Z-axis 
		
	//	 
	//	
 		ThreeDInner.Draw();         // Draw the ball object
        glPopMatrix();
		
		glColor4f(0,0,1,1);
	//	outer.Draw();
	

		glPointSize(4);
		glLineWidth(3);
	

		glPushMatrix();
		//glTranslatef(0,1.67,0);
		glScalef(1.4,1.4,1.4);	   
		glPopMatrix();*/
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	box.Draw();           // Draw the view box space 	

	if(mousedown)
	{
	  glColor3f(1,0,1);
	  glBegin(GL_LINES);
		glVertex2f(xMouse,yMouse);
//   	   	glVertex2f(OneDPoint[closest_i].r->x,OneDPoint[closest_i].r->y);
   	   	glVertex2f(object1D.inner_points[closest_i].r->x,object1D.inner_points[closest_i].r->y);
      glEnd();
	}     


		glutSwapBuffers(); 
}

//===================================================================================


// when mouse is clicked 

void Mouse(int button, int state, int x, int y)
{
    ThreeDInner.Mouse(button, state, x, y);

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
	  	}
     }
}


// when mouse is moving

void Motion(int x, int y)
{
    ThreeDInner.Motion(x, y);

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
	ThreeDInner.Keyboard(key, x, y);		
}

// when a moving direction Key is pressed

void SpecialKeys(int key, int x, int y)
{
	ThreeDInner.SpecialKeys(key, x, y);	
}




void Idle()
{
	

//	xMouse+=2;
//	yMouse+=2;

//	ThreeDInner.AccumulateForces();
//	ThreeDInner.Derivatives(DT);
//  outer.AccumulateForces();
 // outer.Derivatives(DT);


//	AccumulateForces();
//	Euler_Integrator();

	//object1D.Update(DT, false, xMouse, yMouse);
	object1D.Update(DT, mousedown != 0, xMouse, yMouse);
	object2D.Update(DT, mousedown != 0, xMouse, yMouse);
	//object2D.Update(DT, false, xMouse, yMouse);

	
  if (ThreeDInner.getPressure()<PRESSURE)
  {
      ThreeDInner.setPressure(PRESSURE);
//	  outer.setPressure(PRESSURE);
	  
	  ThreeDInner.setPressure(ThreeDInner.getPressure()+PRESSURE/300.0f);
  }

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

    ThreeDInner.SetObject(); 
//	CreateOneD();
 //   outer.SetBall();	

	glutReshapeFunc(Reshape);
    

	glutPassiveMotionFunc(motion);
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
