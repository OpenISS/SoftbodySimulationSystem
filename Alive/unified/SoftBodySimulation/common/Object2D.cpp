#include "Object2D.h"

Object2D::Object2D() : pressure(DEFAULTPRESSURE)
{
	NUMP = NUMPOINTS;
	NUMS = NUMSPRINGS;
	CreateRing();
}


Object2D::~Object2D()
{
}

void Object2D::Draw()
{
	int i;
	//glClearColor(0,0,0,0);
	//glClear(GL_COLOR_BUFFER_BIT);


	glPushMatrix();
//	glBegin(GL_QUADS); // the draw of outer circle
	glBegin(GL_LINES); // the draw of outer circle
		for(i=0 ; i<NUMS; i++)
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
//	glBegin(GL_QUADS); // the draw of inner circle
	glBegin(GL_POINTS); // the draw of inner circle
//	glBegin(GL_LINES); // the draw of inner circle
		for(i=0 ; i<NUMP; i++)
		{
			glColor3f(0.0, 0.0, 1.0);
/*
			glVertex2f(inner_points[inner_springs[i].head].px,inner_points[inner_springs[i].head].py);
			glVertex2f(inner_points[inner_springs[i].tail].px,inner_points[inner_springs[i].tail].py);
			glVertex2f(inner_points[NUMP-inner_springs[i].head+1].px,inner_points[NUMP-inner_springs[i].head+1].py);
			glVertex2f(inner_points[NUMP-inner_springs[i].tail+1].px,inner_points[NUMP-inner_springs[i].tail+1].py);*/

			glVertex2f(inner_points[i].r->x,inner_points[i].r->y);
			glVertex2f(outer_points[i].r->x,outer_points[i].r->y);
		}
	glEnd();
	glPopMatrix();

	glPushMatrix();
//	glBegin(GL_QUADS); // the draw of inner circle
//	glBegin(GL_POINTS); // the draw of inner circle
	glBegin(GL_LINES); // the draw of inner circle
		for(i=0 ; i<NUMS; i++)
//		for(i=0 ; i<NUMP; i++)
		{
			glColor3f(0.0, 0.0, 1.0);
/*
			glVertex2f(inner_points[inner_springs[i].head].px,inner_points[inner_springs[i].head].py);
			glVertex2f(inner_points[inner_springs[i].tail].px,inner_points[inner_springs[i].tail].py);
			glVertex2f(inner_points[NUMP-inner_springs[i].head+1].px,inner_points[NUMP-inner_springs[i].head+1].py);
			glVertex2f(inner_points[NUMP-inner_springs[i].tail+1].px,inner_points[NUMP-inner_springs[i].tail+1].py);*/

			glVertex2f(inner_springs[i].sp1->r->x,inner_springs[i].sp1->r->y);
			glVertex2f(inner_springs[i].sp2->r->x,inner_springs[i].sp2->r->y);
			//glVertex2f(inner_springs[NUMS - i].sp1->r->x,inner_springs[NUMS - i].sp1->r->y);
			//glVertex2f(inner_springs[NUMS - i].sp2->r->x,inner_springs[NUMS - i].sp2->r->y);
		}
	glEnd();
	glPopMatrix();


/*	
glPushMatrix();
	glBegin(GL_LINES); // the draw of radium lines from inner to outer
		
		for(i=0 ; i<NUMS; i++)
		{
		glColor3f(0.0,1.0,0.0);
		glVertex2f(inner_points[inner_springs[i].head].px,inner_points[inner_springs[i].head].py);
		glVertex2f(outer_points[outer_springs[i].head].px,outer_points[outer_springs[i].head].py);
		}
	glEnd();
	glPopMatrix();


glPushMatrix();
	glBegin(GL_LINES); // the left shear lines from inner to outer
		
		for(i=0 ; i<NUMS; i++)
		{
		glColor3f(0.0,1.0,1.0);
		glVertex2f(inner_points[inner_springs[i].head].px,inner_points[inner_springs[i].head].py);
		glVertex2f(outer_points[outer_springs[i].tail].px,outer_points[outer_springs[i].tail].py);
		}
	glEnd();
	glPopMatrix();



glPushMatrix();
	glBegin(GL_LINES); // the right shear lines from inner to outer
		
		for(i=0 ; i<NUMS; i++)
		{
		glColor3f(0.0,1.0,1.0);
		glVertex2f(inner_points[inner_springs[i].tail].px,inner_points[inner_springs[i].tail].py);
		glVertex2f(outer_points[outer_springs[i].head].px,outer_points[outer_springs[i].head].py);
		}
	glEnd();
	glPopMatrix();
*/		
}

/* Function of adding a new spring on the inner rings*/

void Object2D::Add_Tangent_Spring(int index, int h, int t)
//void Object2D::Add_Tangent_Spring(int index, Particle* h, Particle* t)
{
	/*
    inner_springs[index].head = h; // h, t stand for spring head and tail
    inner_springs[index].tail = t; // index for spring index on the ring
	
    outer_springs[index].head = h; // h, t stand for spring head and tail
    outer_springs[index].tail = t; // index for spring index on the ring

	inner_springs[index].length = 
    sqrt((inner_points[h].px-inner_points[t].px)*(inner_points[h].px-inner_points[t].px)
	+(inner_points[h].py-inner_points[t].py)*(inner_points[h].py-inner_points[t].py));

	outer_springs[index].length = 
    sqrt((outer_points[h].px-outer_points[t].px)*(outer_points[h].px-outer_points[t].px)
	+(outer_points[h].py-outer_points[t].py)*(outer_points[h].py-outer_points[t].py));
*/

    inner_springs[index].sp1 = &inner_points[h]; // h, t stand for spring head and tail
    inner_springs[index].sp2 = &inner_points[t]; // index for spring index on the ring
	
    outer_springs[index].sp1 = &outer_points[h]; // h, t stand for spring head and tail
    outer_springs[index].sp2 = &outer_points[t]; // index for spring index on the ring

	inner_springs[index].restLen = 
    sqrt((inner_points[h].r->x-inner_points[t].r->x)*(inner_points[h].r->x-inner_points[t].r->x)
	+(inner_points[h].r->y-inner_points[t].r->y)*(inner_points[h].r->y-inner_points[t].r->y));

	outer_springs[index].restLen = 
    sqrt((outer_points[h].r->x-outer_points[t].r->x)*(outer_points[h].r->x-outer_points[t].r->x)
	+(outer_points[h].r->y-outer_points[t].r->y)*(outer_points[h].r->y-outer_points[t].r->y));


	//inner_springs[index].setRestLen();
	//outer_springs[index].setRestLen();
}


void Object2D::Add_Radium_Spring(int index)
{
/*    radium_springs[index].n=index; 
	radium_springs[index].length = 
		sqrt((outer_points[index].px-inner_points[index].px)
			*(outer_points[index].px-inner_points[index].px)
		    +(outer_points[index].py-inner_points[index].py)
			*(outer_points[index].py-inner_points[index].py));	
			*/
} 


//void Object2D::Add_Shear_Spring(int index, int h, int t )
void Object2D::Add_Shear_Spring(int index, Particle* h, Particle* t )
{
//    shear_springs_left[index].head = h;  
//   shear_springs_right[index].tail = t; 
    shear_springs_left[index].sp1 = h;  
   shear_springs_right[index].sp2 = t; 

/*	shear_springs_left[index].length = 
		sqrt((outer_points[t].px-inner_points[h].px)
			*(outer_points[t].px-inner_points[h].px)
		    +(outer_points[t].py-inner_points[h].py)
			*(outer_points[t].py-inner_points[h].py));	
*/

   /*
	shear_springs_left[index].length = 
		sqrt((outer_points[t].r->x-inner_points[h].r->x)
			*(outer_points[t].r->x-inner_points[h].r->x)
		    +(outer_points[t].r->y-inner_points[h].r->y)
			*(outer_points[t].r->y-inner_points[h].r->y));	

	shear_springs_right[index].length = 
		sqrt((outer_points[h].px-inner_points[t].px)
			*(outer_points[h].px-inner_points[t].px)
		    +(outer_points[h].py-inner_points[t].py)
			*(outer_points[h].py-inner_points[t].py));	

  */
} 

/* Create 2 2D-rings (points + springs) */
void Object2D::CreateRing(void)
{
	int i;
	for(i=0; i<NUMP; i++)		// create NUMP points into 2D circle 
	{
		inner_points[i].r->x=  RING_RADIUS*cos(i*(2.0*PI)/NUMP);   // inner X coordiation
		inner_points[i].r->y=  RING_RADIUS*sin(i*(2.0*PI)/NUMP);   // inner Y coordiation
		inner_points[i].mass = 2.0*MASS;
				 
		outer_points[i].r->x=3*RING_RADIUS*cos(i*(2.0*PI)/NUMP); // outer point X coordiation
		outer_points[i].r->y=3*RING_RADIUS*sin(i*(2.0*PI)/NUMP); // outer point Y coordiation
		outer_points[i].mass = MASS;
	}


	for(i=0; i<NUMP ;i++)	       // NUMP-1 springs from 1st to the NUMP for outer & inner
	{  
		Add_Tangent_Spring(i,i,(i+1) % NUMP); 
		/*Add_Radium_Spring(i) ;
		Add_Shear_Spring(i,i,i+1);*/
	}
/*
	Add_Tangent_Spring(i,i,1);    // At this monment, i=NUMP, last spring from NUMP - 1st		 
	Add_Radium_Spring(i);         // from inner NUMP point to outer NUMP point
	Add_Shear_Spring(i,i,1);
*/	
}
