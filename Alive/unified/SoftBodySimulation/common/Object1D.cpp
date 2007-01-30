#include "Object1D.h"

Object1D::Object1D()
{
	CreateStructure();
}


Object1D::~Object1D()
{
}

void Object1D::Draw()
{
	numSprings = 1;
	glPushMatrix();
		glBegin(GL_LINES); // the draw of inner circle
			for(int i = 0 ; i < numSprings; i++)
			{
				glColor3f(1.0,1.0,1.0);
			/*	glVertex2f(inner_springs[i].sp1->r->x,inner_springs[i].sp1->r->y);
				glVertex2f(inner_springs[i].sp2->r->x,inner_springs[i].sp2->r->y);
*/
				glVertex2f(outer_springs[i].sp1->r->x,outer_springs[i].sp1->r->y);
				glVertex2f(outer_springs[i].sp2->r->x,outer_springs[i].sp2->r->y);

			/*	glVertex2f(inner_springs[i].sp1->r->x,inner_springs[i].sp1->r->y);
				glVertex2f(outer_springs[i].sp1->r->x,outer_springs[i].sp1->r->y);
				glVertex2f(inner_springs[i].sp2->r->x,inner_springs[i].sp2->r->y);
*/
			//	glVertex2f(outer_springs[i].sp2->r->x,outer_springs[i].sp2->r->y);
			}
		glEnd();
		glBegin(GL_POINTS);
		//	glVertex2f(OneDPoint[OneDSpring[0].sp1->r->x,OneDPoint[OneDSpring[0].sp1]->r->y);
		//	glVertex2f(OneDPoint[OneDSpring[0].sp2]->r->x,OneDPoint[OneDSpring[0].sp2]->r->y);

			//glVertex2f(OneDPoint[0].r->x,OneDPoint[0].r->y);
			//glVertex2f(OneDPoint[1].r->x,OneDPoint[1].r->y);

		//	glVertex2f(inner_springs[0].sp1->r->x,inner_springs[0].sp1->r->y);
			
			glVertex2f(outer_springs[0].sp1->r->x,outer_springs[0].sp1->r->y);

		//	glVertex2f(inner_springs[0].sp2->r->x,inner_springs[0].sp2->r->y);
		
			glVertex2f(outer_springs[0].sp2->r->x,outer_springs[0].sp2->r->y);
		glEnd();
	glPopMatrix();
}

//====================================================================

void Object1D::Add_Tangent_Spring(int index, int head, int tail)
{

   	outer_springs[index].sp1=&outer_points[head];
	outer_springs[index].sp2=&outer_points[tail];

   	inner_springs[index].sp2= new Particle();
	inner_springs[index].sp1= new Particle();


  
	
/*	draw strange spinning 1D 
	inner_springs[index].sp1= &inner_points[tail];
	inner_springs[index].sp2=new Particle();

	outer_springs[index].sp2= new Particle();
   	outer_springs[index].sp1= &inner_points[head];
	
*/
//	inner_springs[index].setRestLen();
	outer_springs[index].setRestLen();
//	cout<<"restLen"<<inner_springs[index].restLen<<endl;;
}

void Object1D::CreateStructure()
{
	int PosX = 0;
	int PosY = 0;

	for(int i=0; i<2; i++)		// create NUMP points into 2D circle 
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
