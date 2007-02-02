#include "Object1D.h"

Object1D::Object1D()
{
	SetObject();
}


Object1D::~Object1D()
{
}

void Object1D::Draw()
{
//	cout<<"numSprings----1D-----"<<numSprings<<endl;
	glPushMatrix();
		glBegin(GL_LINES); // the draw of inner circle
			for(int i = 0 ; i < numSprings; i++)
			{
				glColor3f(1.0,1.0,1.0);
		
				glVertex2f(outer_springs[i].sp1->r->x,outer_springs[i].sp1->r->y);
				glVertex2f(outer_springs[i].sp2->r->x,outer_springs[i].sp2->r->y);

				}
		glEnd();
		glBegin(GL_POINTS);
			for(int j = 0 ; j < numSprings; j++)
			{
			
			glVertex2f(outer_springs[j].sp1->r->x,outer_springs[j].sp1->r->y);

		
			glVertex2f(outer_springs[j].sp2->r->x,outer_springs[j].sp2->r->y);
			}
		glEnd();

		if(integrator->dragExists)
		{
		  glColor3f(1,1,0);      // A white line between the Object3D point and the mouse point
		  glBegin(GL_LINES);	
			glVertex2f(integrator->mDragX, integrator->mDragY);
   	   		glVertex2f(outer_springs[0].sp1->r->x,outer_springs[0].sp1->r->y);
		   glEnd();
		}                   

	glPopMatrix();
}

//====================================================================

void Object1D::Add_Tangent_Spring(int index, int head, int tail)
{
	cout<<"add spring................"<<endl;
   	outer_springs[index].sp1=&outer_points[head];
	outer_springs[index].sp2=&outer_points[tail];

   	inner_springs[index].sp1= new Particle();
	inner_springs[index].sp2= new Particle();


  
	outer_springs[index].setRestLen();

}

void Object1D::SetObject()
{cout<<"set object............."<<endl;
	int PosX = 0;
	int PosY = 0;
//	cout<<"numParticles---1D------"<<numParticles<<endl;
	for(int i=0; i<numParticles; i++)		// create NUMP points into 2D circle 
	{
		outer_points[i].r->x += PosX ;   // outer X coordiation
		outer_points[i].r->y += PosY;   // outer Y coordiation
		outer_points[i].mass = 2.0 * MASS;
			 
		PosY += 2;
	}

	for(i=0; i<1 ;i++)	       // NUMP-1 springs from 1st to the NUMP for outer & inner
	{  
		Add_Tangent_Spring(i, i, (i+1) % numParticles); 
	}
}
