#include "Object1D.h"

Object1D::Object1D()
{
	PosX = 0;
	PosY = 0;
	Mass1 =   10.0f; Mass2 =   1.0f;
	Ks1   =700.0f; Ks2   = 100.0f;
	Kd1   =  20.0f; Kd2   =  1.0f;
	CreateOneD();

	//new Integrator::integrate(OneDPoint, NUMPS);
}


Object1D::~Object1D()
{
}

void Object1D::Draw()
{
	glPushMatrix();
		glBegin(GL_LINES); // the draw of inner circle
			for(int i = 0 ; i < NUMS; i++)
			{
				glColor3f(1.0,1.0,1.0);
				glVertex2f(OneDSpring[i].sp1->r->x,OneDSpring[i].sp1->r->y);
				glVertex2f(OneDSpring[i].sp2->r->x,OneDSpring[i].sp2->r->y);
			}
		glEnd();
		glPointSize(8);
		glBegin(GL_POINTS);
		//	glVertex2f(OneDPoint[OneDSpring[0].sp1->r->x,OneDPoint[OneDSpring[0].sp1]->r->y);
		//	glVertex2f(OneDPoint[OneDSpring[0].sp2]->r->x,OneDPoint[OneDSpring[0].sp2]->r->y);

			//glVertex2f(OneDPoint[0].r->x,OneDPoint[0].r->y);
			//glVertex2f(OneDPoint[1].r->x,OneDPoint[1].r->y);

			glVertex2f(OneDSpring[0].sp1->r->x,OneDSpring[0].sp1->r->y);
			glVertex2f(OneDSpring[0].sp2->r->x,OneDSpring[0].sp2->r->y);
		
		glEnd();
	glPopMatrix();
}

//====================================================================

void Object1D::Add_Tangent_Spring(int index, int head, int tail)
{

   	OneDSpring[index].sp1=&OneDPoint[head];
	OneDSpring[index].sp2=&OneDPoint[tail];
	OneDSpring[index].setRestLen();
	cout<<"restLen"<<OneDSpring[index].restLen<<endl;;
}

void Object1D::CreateOneD()
{
	 for(int i=0; i<2; i++)		// create NUMP points into 2D circle 
	 {
	   OneDPoint[i].r->x += PosX ;   // inner X coordiation
	   OneDPoint[i].r->y += PosY;   // inner Y coordiation
	   OneDPoint[i].mass = 2.0*Mass2;
		 		 
		PosY+=2;
	
	 }

	 for(i=0; i<1 ;i++)	       // NUMP-1 springs from 1st to the NUMP for outer & inner
	 {  

		Add_Tangent_Spring(i, i, i+1); 
	 }
}
