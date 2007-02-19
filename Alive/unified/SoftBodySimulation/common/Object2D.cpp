#include "Object2D.h"

Object2D::Object2D() : pressure(PRESSURE)
{
	numParticles = NUMPOINTS;
	numSprings =  NUMSPRINGS;
	SetObject();
	dim = DIM2D;
}


Object2D::~Object2D()
{
}

void Object2D::Draw()
{
		static bool findOnce = false;
	//because of the drawing method, two circles are on the same plane, cross each other with depth buffer
	glDisable(GL_DEPTH_TEST); 
	
	int i;

	glPushMatrix();
		glColor4f(0.5,0.2,0.5, 0.7);

		glBegin(GL_LINES);
			for(i=0 ; i<outer_faces.size(); i++)
			{
			glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
		
			glVertex3f((outer_faces[i]->normal->x + outer_faces[i]->fp1->r->x),
				       (outer_faces[i]->normal->y + outer_faces[i]->fp1->r->y),
					   (outer_faces[i]->normal->z + outer_faces[i]->fp1->r->z));
				
			
			}
		glEnd();

		glBegin(GL_POLYGON); // the draw of outer circle
		for(i=0 ; i<outer_points.size(); i++)
		{
			glVertex2f(outer_points[i]->r->x, outer_points[i]->r->y);
		}
		glEnd(); 
	glPopMatrix();

	glPushMatrix();
		glColor4f(0.0,1.0,0.0, 0.5 );
		glBegin(GL_POLYGON); // the draw of outer circle
		for(i=0 ; i<inner_points.size(); i++)
		{
			glVertex2f(inner_points[i]->r->x, inner_points[i]->r->y);
		}
		glEnd(); 
	glPopMatrix();

	glPushMatrix();
		glBegin(GL_LINES); // the draw of outer circle
			for(i=0 ; i<outer_springs.size(); i++)
			{
				glColor3f(0.2,0.2,1.0);
				glVertex2f(outer_springs[i]->sp1->r->x,outer_springs[i]->sp1->r->y);
				glVertex2f(outer_springs[i]->sp2->r->x,outer_springs[i]->sp2->r->y);

			}
		glEnd(); 


		glBegin(GL_POINTS);
			for(i = 0 ; i < outer_springs.size(); i++)
			{
			//	cout<<"i================"<<i<<endl;
			if(i==0) 
				glColor3f(1.0,0.0,0.0);
			else
					glColor3f(1.0,1.0,0.0);
				glVertex2f(outer_springs[i]->sp1->r->x,outer_springs[i]->sp1->r->y);
			//	glVertex2f(outer_springs[i]->sp2->r->x,outer_springs[i]->sp2->r->y);
			}
		glEnd();

		glBegin(GL_LINES); // the draw of inner circle
			for(i=0 ; i<inner_springs.size(); i++)
			{
				glColor3f(0.2,0.2,1.0);
				glVertex2f(inner_springs[i]->sp1->r->x,inner_springs[i]->sp1->r->y);
				glVertex2f(inner_springs[i]->sp2->r->x,inner_springs[i]->sp2->r->y);
			}
		glEnd(); 


		glBegin(GL_POINTS);
			for(i = 0 ; i < inner_springs.size(); i++)
			{	glColor3f(1.0,0.0,0.0);
				glVertex2f(inner_springs[i]->sp1->r->x,inner_springs[i]->sp1->r->y);
		//		glVertex2f(inner_springs[i]->sp2->r->x,inner_springs[i]->sp2->r->y);
			}
		glEnd();

	glPopMatrix();
	
	
	glPushMatrix();
		glBegin(GL_LINES);				// the draw of radium lines from inner to outer
			for(i=0 ; i<radium_springs.size(); i++)
			{
				glColor3f(0.0,1.0,0.0);
				glVertex2f(radium_springs[i]->sp1->r->x, radium_springs[i]->sp1->r->y);
				glVertex2f(radium_springs[i]->sp2->r->x, radium_springs[i]->sp2->r->y);
			}
		glEnd();
	glPopMatrix();


	glPushMatrix();
		glBegin(GL_LINES);				// the left shear lines from inner to outer
			for(i=0 ; i<shear_springs_left.size(); i++)
			{
				glColor3f(1.0,0.0,0.0);
				glVertex2f(shear_springs_left[i]->sp1->r->x,shear_springs_left[i]->sp1->r->y);
				glVertex2f(shear_springs_left[i]->sp2->r->x,shear_springs_left[i]->sp2->r->y);
			}
		glEnd();
	glPopMatrix();



	glPushMatrix();
		glBegin(GL_LINES);				// the right shear lines from inner to outer
			for(i=0 ; i<shear_springs_right.size(); i++)
			{
				glColor3f(0.0,0.0,1.0);
				glVertex2f(shear_springs_right[i]->sp1->r->x,shear_springs_right[i]->sp1->r->y);
				glVertex2f(shear_springs_right[i]->sp2->r->x,shear_springs_right[i]->sp2->r->y);
			}
		glEnd();
	glPopMatrix();
	
	if(integrator->dragExists)
	{if(findOnce == true)
			{
				FindClosestPoint();
				findOnce = false;
			}
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


	glEnable(GL_DEPTH_TEST);
}

/* Function of adding a new spring on the inner rings*/

void Object2D::Add_Structural_Spring(int index, int h, int t)
{

   	inner_springs.push_back( new Spring(inner_points[h],inner_points[t]));
	outer_springs.push_back( new Spring(outer_points[h],outer_points[t]));

	inner_springs[index]->setRestLen();					//set the inner spring's length
	outer_springs[index]->setRestLen();					//set the outer spring's length
}


void Object2D::Add_Radium_Spring(int index)
{
   	
	radium_springs.push_back( new Spring(inner_points[index],outer_points[index]));
	radium_springs[index]->setRestLen();						//set the radium spring's length
} 


void Object2D::Add_Shear_Spring(int index, int h, int t )
{
      
	
	shear_springs_left.push_back(new Spring(inner_points[h],outer_points[t]));
	shear_springs_right.push_back(new Spring(inner_points[t],outer_points[h]));


	shear_springs_left[index]->setRestLen();					//set the shear left spring's length
	shear_springs_right[index]->setRestLen();				//set the shear right spring's length
 
} 

/* Create 2 2D-rings (points + springs) */
void Object2D::SetObject(void)
{
	float tix, tiy, tiz, tox,toy, toz;
	
	tix=tiy=tiz=tox=toy=toz=0;
	outer_points.clear();
	inner_points.clear();
	outer_springs.clear();
	inner_springs.clear();
	int i;
	for(i=0; i<numParticles ; i++)							// create NUMP points into 2D circle 
	{	
	


		tix = 1*RING_RADIUS*cos(i*(2.0*PI)/numParticles);	// outer point X coordiation
		tiy = 1*RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// outer point Y coordiation
		tiz = 0;//2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// outer point Y coordiation

		tox = 2*RING_RADIUS*cos(i*(2.0*PI)/numParticles);	// outer point X coordiation
		toy = 2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// outer point Y coordiation
		toz = 0;//2*RING_RADIUS*sin(i*(2.0*PI)/numParticles);	// outer point Y coordiation


	//	cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
		outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
	}

	

	for(i=0; i<numParticles ;i++)						//add the springs for outer & inner
	{  
		Add_Structural_Spring(i,i,(i+1) % numParticles); 
		Add_Radium_Spring(i) ;
		Add_Shear_Spring(i,i,(i+1) % numParticles);
		Add_Faces(i, (i+1) % numParticles, (numParticles/2 + i) % numParticles) ;

	}


	for(i=0;i<inner_faces.size();i++)
	{
	
		inner_faces[i]->CalNormalNField();

	outer_faces[i]->CalNormalNField();
//		cout<<"outer_faces[i]->normal->x==="<<outer_faces[i]->normal->x<<"=== outer_faces[i]->normal->y==="<<outer_faces[i]->normal->y<<"===outer_faces[i]->normal->z===="<<outer_faces[i]->normal->z<<endl;

	
	}

/*	cout<<"outer_faces[0]->fp1->r->x=="<<outer_faces[0]->fp1->r->x<<"==outer_faces[0]->fp1->r->y=="<<outer_faces[0]->fp1->r->y<<"==outer_faces[0]->fp1->r->z=="<<outer_faces[0]->fp1->r->z<<endl;
		cout<<"outer_faces[0]->fp2->r->x=="<<outer_faces[0]->fp2->r->x<<"==outer_faces[0]->fp2->r->y=="<<outer_faces[0]->fp2->r->y<<"==outer_faces[0]->fp2->r->z=="<<outer_faces[0]->fp2->r->z<<endl;
		cout<<"outer_faces[0]->fp3->r->x=="<<outer_faces[0]->fp3->r->x<<"==outer_faces[0]->fp3->r->y=="<<outer_faces[0]->fp3->r->y<<"==outer_faces[0]->fp3->r->z=="<<outer_faces[0]->fp3->r->z<<endl;

	outer_faces[0]->CalNormalNField();
	cout<<"outer_faces[0]->normal->x==="<<outer_faces[0]->normal->x<<"=== outer_faces[0]->normal->y==="<<outer_faces[0]->normal->y<<"===outer_faces[0]->normal->z===="<<outer_faces[0]->normal->z<<endl;
*/

}


void Object2D::Add_Faces(int f1, int f2, int f3)
{
	inner_faces.push_back(new Face(inner_points[f1], inner_points[f2], inner_points[f3]));
	
	outer_faces.push_back(new Face(outer_points[f1], outer_points[f2], outer_points[f3]));
} 
