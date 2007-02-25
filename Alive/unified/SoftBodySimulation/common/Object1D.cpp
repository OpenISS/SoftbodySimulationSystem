#include "Object1D.h"
#include <vector>
Object1D::Object1D()
{
	SetObject();
	dim = DIM1D;
}


Object1D::~Object1D()
{
}

void Object1D::Draw()
{
	static bool findOnce = false;

	glPushMatrix();
		glBegin(GL_LINES); // the draw of inner circle
			for(int i = 0 ; i < outer_springs.size(); i++)
			{
				glColor3f(1.0,1.0,1.0);
				glVertex2f(outer_springs[i]->sp1->r->x,outer_springs[i]->sp1->r->y);
				glVertex2f(outer_springs[i]->sp2->r->x,outer_springs[i]->sp2->r->y);

			}
		glEnd();
		glBegin(GL_POINTS);
			for(int j = 0 ; j < outer_springs.size(); j++)
			{
				glVertex2f(outer_springs[j]->sp1->r->x,outer_springs[j]->sp1->r->y);
				glVertex2f(outer_springs[j]->sp2->r->x,outer_springs[j]->sp2->r->y);
			}
		glEnd();

		if(integrator->dragExists)
		{
			if(findOnce == true)
			{
				FindClosestPoint();
				findOnce = false;
			}

		//	cout<<"mDragX="<<integrator->mDragX<<",mDragY="<<integrator->mDragY<<",x="<<outer_points[closest_i]->r->x<<",y="<<outer_points[closest_i]->r->y<<endl;

		
			glColor3f(1,1,0);      // A white line between the Object3D point and the mouse point
			glBegin(GL_LINES);	
				glVertex2f(integrator->mDragX, integrator->mDragY);
				glVertex2f(outer_points[closest_i]->r->x,outer_points[closest_i]->r->y);
			glEnd();
		}
		else
		{
			FindClosestPoint();
			findOnce = true;
		}


	glPopMatrix();

  
}

//====================================================================

void Object1D::Add_Structural_Spring(int index, int head, int tail)
{

	outer_springs.push_back( new Spring(outer_points[head],outer_points[tail]));
	inner_springs.push_back( new Spring());

 /*  	outer_springs[index].sp1 = &outer_points[head];
	outer_springs[index].sp2 = &outer_points[tail];

  	inner_springs[index].sp1 = new Particle();
	inner_springs[index].sp2 = new Particle();

	outer_springs[index].setRestLen();
	*/
	inner_springs[index]->setRestLen();
	outer_springs[index]->setRestLen();
}


//================================================================
void Object1D::SetObject()
{


	int PosX = 0;
	int PosY = 0;
	int i;
//	cout<<"numParticles---1D------"<<numParticles<<endl;
	for(i=0; i<numParticles; i++)		// create NUMP points into 2D circle 
	{
	outer_points.push_back( new Particle(new Vector(PosX,PosY,0), MASS));
	inner_points.push_back( new Particle());
	/*	outer_points[i].r->x += PosX ;   // outer X coordiation
		outer_points[i].r->y += PosY;   // outer Y coordiation
		outer_points[i].mass =  MASS;
	*/	 
		PosY += 2;
	}


	for(i=0; i<1 ;i++)	       // NUMP-1 springs from 1st to the NUMP for outer & inner
	{  
		Add_Structural_Spring(i, i, (i+1) % numParticles); 
	}
}


//=======================================================
/*		
void Object1D::FindClosestPoint(void)
{
	float dmin = 0;
	float mousepointd = 0;
	int i;

	// find closest point
	dmin = sqrt(pow(outer_points[closest_i]->r->x - integrator->mDragX,2) + pow(outer_points[closest_i]->r->y - integrator->mDragY,2));

	for(i=0; i<numParticles; i++)
	{
		mousepointd = sqrt(	pow(outer_points[i]->r->x - integrator->mDragX,2) +
							pow(outer_points[i]->r->y - integrator->mDragY,2));
		if(mousepointd < dmin)
		{
			dmin = mousepointd;
			closest_i = i;
		}
	}

	cout<<"	closest_i=="<<	closest_i<<endl;
}*/
