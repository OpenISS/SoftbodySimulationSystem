#include "Object2D.h"

Object2D::Object2D() : pressure(PRESSURE)
{
	cout<<"2D constructor"<<endl;
	numParticles = NUMPOINTS;
	numSprings = NUMSPRINGS;
	SetObject();
	dim = DIM2D;
}


Object2D::~Object2D()
{
}

void Object2D::Draw()
{

	int i;


	glPushMatrix();
//	glBegin(GL_QUADS); // the draw of outer circle
	glBegin(GL_LINES); // the draw of outer circle
		for(i=0 ; i<numSprings; i++)
		{
			glColor3f(0.8,0.4,0.4);
			
			/*glVertex2f(outer_points[outer_springs[i].head].px,outer_points[outer_springs[i].head].py);
			glVertex2f(outer_points[outer_springs[i].tail].px,outer_points[outer_springs[i].tail].py);
    		glVertex2f(outer_points[NUMP-outer_springs[i].head+1].px,outer_points[NUMP-outer_springs[i].head+1].py);
			glVertex2f(outer_points[NUMP-outer_springs[i].tail+1].px,outer_points[NUMP-outer_springs[i].tail+1].py);*/

			glVertex2f(outer_springs[i].sp1->r->x,outer_springs[i].sp1->r->y);
			glVertex2f(outer_springs[i].sp2->r->x,outer_springs[i].sp2->r->y);

			/*
    		glVertex2f(outer_points[NUMP-outer_springs[i].head+1].px,outer_points[NUMP-outer_springs[i].head+1].py);
			glVertex2f(outer_points[NUMP-outer_springs[i].tail+1].px,outer_points[NUMP-outer_springs[i].tail+1].py);*/
		}
	glEnd(); 
	glPopMatrix();
	

	glPushMatrix();

	glBegin(GL_POINTS); // the draw of inner circle

		for(i=0 ; i<numParticles; i++)
		{
			glColor3f(0.0, 0.0, 1.0);
			glVertex2f(outer_points[i].r->x,outer_points[i].r->y);
		}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POINTS); // the draw of inner circle

		for(i=0 ; i<numParticles; i++)
		{
			glColor3f(0.0, 0.0, 1.0);
			glVertex2f(inner_points[i].r->x,inner_points[i].r->y);
		}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES); // the draw of inner circle
		for(i=0 ; i<numSprings; i++)

		{
			glColor3f(0.3, 0.3, 1.0);

			glVertex2f(inner_springs[i].sp1->r->x,inner_springs[i].sp1->r->y);
			glVertex2f(inner_springs[i].sp2->r->x,inner_springs[i].sp2->r->y);
			}
	glEnd();
	glPopMatrix();

	
	glPushMatrix();
	glBegin(GL_LINES); // the draw of radium lines from inner to outer
		for(i=0 ; i<numSprings; i++)
		{
			glColor3f(0.0,1.0,0.0);
			glVertex2f(radium_springs[i].sp1->r->x, radium_springs[i].sp1->r->y);
			glVertex2f(radium_springs[i].sp2->r->x, radium_springs[i].sp2->r->y);

		}
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glBegin(GL_LINES); // the left shear lines from inner to outer
		for(i=0 ; i<numSprings; i++)
		{
			glColor3f(1.0,0.0,0.0);
			glVertex2f(shear_springs_left[i].sp1->r->x,shear_springs_left[i].sp1->r->y);
			glVertex2f(shear_springs_left[i].sp2->r->x,shear_springs_left[i].sp2->r->y);
		}
	glEnd();
	glPopMatrix();



	glPushMatrix();
	glBegin(GL_LINES); // the right shear lines from inner to outer
		for(i=0 ; i<numSprings; i++)
		{
			glColor3f(0.0,0.0,1.0);
			glVertex2f(shear_springs_right[i].sp1->r->x,shear_springs_right[i].sp1->r->y);
			glVertex2f(shear_springs_right[i].sp2->r->x,shear_springs_right[i].sp2->r->y);
		}
	glEnd();
	glPopMatrix();
		
}

/* Function of adding a new spring on the inner rings*/

void Object2D::Add_Structural_Spring(int index, int h, int t)

{

    
    inner_springs[index].sp1 = &inner_points[h];		//inner structural spring head points to the inner particle i
    inner_springs[index].sp2 = &inner_points[t];		//inner structural spring tail points to the inner particle i+1
	
    outer_springs[index].sp1 = &outer_points[h];		//outer structural spring head points to the outer particle i
    outer_springs[index].sp2 = &outer_points[t];		//outer structural spring tail points to the outer particle i+1

	
	inner_springs[index].setRestLen();					//set the inner spring's length
	outer_springs[index].setRestLen();					//set the outer spring's length
}


void Object2D::Add_Radium_Spring(int index)
{
   	
	radium_springs[index].sp1 = &inner_points[index];		//radium spring head points to the inner particle i
    radium_springs[index].sp2 = &outer_points[index];		//radium spring tail points to the outer particle i

	radium_springs[index].setRestLen();						//set the radium spring's length
} 


void Object2D::Add_Shear_Spring(int index, int h, int t )
{
      
	
	shear_springs_left[index].sp1 = &inner_points[h];		//shear left spring head points to the inner particle i
	shear_springs_left[index].sp2 = &outer_points[t];		//shear left spring tail points to the outer particle i+1
	
	shear_springs_right[index].sp1 = &inner_points[t];		//shear right spring head points to the inner particle i+1
	shear_springs_right[index].sp2 = &outer_points[h];		//shear right spring head points to the outer particle i
   
	shear_springs_left[index].setRestLen();					//set the shear left spring's length
	shear_springs_right[index].setRestLen();				//set the shear right spring's length
 
} 

/* Create 2 2D-rings (points + springs) */
void Object2D::SetObject(void)
{
	int i;
	for(i=0; i<numParticles; i++)							// create NUMP points into 2D circle 
	{
		inner_points[i].r->x=  RING_RADIUS*cos(i*(2.0*PI)/numParticles);	// inner X coordiation
		inner_points[i].r->y=  RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// inner Y coordiation
		inner_points[i].mass = MASS;
				 

		outer_points[i].r->x=2*RING_RADIUS*cos(i*(2.0*PI)/numParticles);	// outer point X coordiation
		outer_points[i].r->y=2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// outer point Y coordiation
		outer_points[i].mass = MASS;

	
	}


	for(i=0; i<numParticles ;i++)						//add the springs for outer & inner
	{  
		Add_Structural_Spring(i,i,(i+1) % numParticles); 
		Add_Radium_Spring(i) ;
		Add_Shear_Spring(i,i,(i+1) % numParticles);
	}
}
