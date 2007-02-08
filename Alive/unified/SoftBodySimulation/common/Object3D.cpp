#include "Object3D.h"

//using vector pointers


// Mouse variables
/*int mousedown =0;                // for GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
float xMouse, yMouse, zMouse;    // for mouse point r(x,y,z) 
int closest_i, closest_j;        // Closest point index i, j 
*/
// Keyboard variables
int   GoDir;           // for GLUT_KEY_LEFT,GLUT_KEY_RIGHT,GLUT_KEY_UP,GLUT_KEY_DOWN
float RotateRegX=0;    // for glRotatef() rotating direction
float RotateRegY=0;    // for glRotatef() rotating direction
float RotateRegZ=0;    // for glRotatef() rotating direction
//int static npoints=6;
int iterations=1 ;

//extern Object3D inner;


/*vector<Point> t_Object3DParticles;
//vector <Spring>  spring; 
vector<Face> t_Face; 
//Face t_Face;*/

void Object3D::SetParticles(void) // [M+2][N] array for M*N+2 Points 
{
	cout<<"3D setparticle"<<endl;
	double a;
	int nt=0/*, ntold*/;
	int i;
  
 
	//Object3DParticles.addElement();


	Object3DParticles.push_back( new Particle(new Vector(0,0,1), Bmass));
	Object3DParticles.push_back( new Particle(new Vector(0,0,-1), Bmass));
	Object3DParticles.push_back( new Particle(new Vector(-1,-1,0), Bmass));
	Object3DParticles.push_back( new Particle(new Vector(1,-1,0), Bmass));
	Object3DParticles.push_back( new Particle(new Vector(1,1,0), Bmass));
	Object3DParticles.push_back( new Particle(new Vector(-1,1,0), Bmass));

	cout<<"Object3DParticles so far: " <<Object3DParticles.size()<<endl; 

	a = 1 / sqrt(2.0);

	for (i=0;i<Object3DParticles.size();i++)
	{
		Object3DParticles[i]->r->x *= a;
		Object3DParticles[i]->r->y *= a;

	}//*/



//	/*
	face.push_back(new Face(Object3DParticles[0], Object3DParticles[3], Object3DParticles[4]));
	face.push_back(new Face(Object3DParticles[0], Object3DParticles[4], Object3DParticles[5]));
	face.push_back(new Face(Object3DParticles[0], Object3DParticles[5], Object3DParticles[2]));
	face.push_back(new Face(Object3DParticles[0], Object3DParticles[2], Object3DParticles[3]));
	face.push_back(new Face(Object3DParticles[1], Object3DParticles[4], Object3DParticles[3]));
	face.push_back(new Face(Object3DParticles[1], Object3DParticles[5], Object3DParticles[4]));
	face.push_back(new Face(Object3DParticles[1], Object3DParticles[2], Object3DParticles[5]));
	face.push_back(new Face(Object3DParticles[1], Object3DParticles[3], Object3DParticles[2]));
//*/


	for (i=0; i<face.size(); i++) // On each horizonal plane, N tangent springs
		{
	     
		    spring.push_back(new Spring(face[i]->fp1, face[i]->fp2,ks,kd));     // row i with offset j
			spring.push_back(new Spring(face[i]->fp2, face[i]->fp3,ks,kd));
			spring.push_back(new Spring(face[i]->fp3, face[i]->fp1,ks,kd));
		
		}

	cout<<"spring size="<<spring.size()<<endl;
	cout<<"Object3DParticles so far: " <<Object3DParticles.size()<<endl; 
 
	for (int it=0; it<iterations;it++){

		int ntold=face.size();
		static int j=0;
	   for(int i=0;i<1;i++){

		   pa->r->x=(face[i]->fp1->r->x+face[i]->fp2->r->x)/2;
		   pa->r->y=(face[i]->fp1->r->y+face[i]->fp2->r->y)/2;
		   pa->r->z=(face[i]->fp1->r->z+face[i]->fp2->r->z)/2;
		   
		   pb->r->x=(face[i]->fp2->r->x+face[i]->fp3->r->x)/2;
		   pb->r->y=(face[i]->fp2->r->y+face[i]->fp3->r->y)/2;
		   pb->r->z=(face[i]->fp2->r->z+face[i]->fp3->r->z)/2;

		   pc->r->x=(face[i]->fp1->r->x+face[i]->fp3->r->x)/2;
		   pc->r->y=(face[i]->fp1->r->y+face[i]->fp3->r->y)/2;
		   pc->r->z=(face[i]->fp1->r->z+face[i]->fp3->r->z)/2;

		  
		 
		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
/*		   pa->r->Normalize();
		   pb->r->Normalize();
		   pc->r->Normalize();
*/
		   cout<<"after normalization: "<<endl;

		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;

/**/
           Object3DParticles.push_back(new Particle(new Vector(pa->r->x, pa->r->y, pa->r->z), Bmass)); 
		   Object3DParticles.push_back(new Particle(new Vector(pb->r->x, pb->r->y, pb->r->z), Bmass)); 
		   Object3DParticles.push_back(new Particle(new Vector(pc->r->x, pc->r->y, pc->r->z), Bmass)); 
 
		   

          /* face.push_back(new Face(face[i]->fp1,pa,pc));
	       face.push_back(new Face(pa,face[i]->fp2,pb));
	       face.push_back(new Face(pb,face[i]->fp3,pc)); 
 
		   spring.push_back(new Spring(face[i]->fp1, pa,ks,kd));     // row i with offset j
		   spring.push_back(new Spring(pa, face[i]->fp2,ks,kd));
		   spring.push_back(new Spring(face[i]->fp2, pb,ks,kd));
		   spring.push_back(new Spring(pb, face[i]->fp3,ks,kd));
		   spring.push_back(new Spring(face[i]->fp3, pc,ks,kd));
		   spring.push_back(new Spring(pc, face[i]->fp1,ks,kd));
		   */


		   Face* f1=new Face(face[i]->fp1,pa,pc);
		   face.push_back(f1);
		  //delete f1;
		   Face* f2=new Face(pa,face[i]->fp2,pb);
	       face.push_back(f2);
		   Face* f3=new Face(pb,face[i]->fp3,pc);
	       face.push_back(f3); 
 
		   //Spring *s1
		   spring.push_back(new Spring(face[i]->fp1, pa,ks,kd));     // row i with offset j
		   spring.push_back(new Spring(pa, face[i]->fp2,ks,kd));
		   spring.push_back(new Spring(face[i]->fp2, pb,ks,kd));
		   spring.push_back(new Spring(pb, face[i]->fp3,ks,kd));
		   spring.push_back(new Spring(face[i]->fp3, pc,ks,kd));
		   spring.push_back(new Spring(pc, face[i]->fp1,ks,kd));
		   
		   
		   spring[j]->sp1=pa;
		   spring[j]->sp2=pb;
		   j++;
		   spring[j]->sp1=pb;
		   spring[j]->sp2=pc;
		   j++;
		   spring[j]->sp1=pc;
		   spring[j]->sp2=pa;
		   j++;

	       face[i]->fp1=pa;
	       face[i]->fp2=pb;
	       face[i]->fp3=pc;
 
		  
	   }
	}
	//
  

 
  
}



//###########################################################
/*
	void Object3D::ExternalForces()     // Such as gravity, wind, pulling or pushing  etc.,
{ 
	int i;
	float x1,x2,y1,y2,z1,z2;   // between the point and the mouse position 
	float  r12d;               // length of this vector 
	float  f;                  // acting force, 
	float Fx, Fy, Fz;          // force vector coordinatings
	

	for(i=0; i<Object3DParticles.size(); i++)      //  external forces are calculated here 
	{
		Object3DParticles[i]->ClearForce();  // reset any existing forces

		if ((pressure-PRESSURE)>=0)
		{
			Object3DParticles[i]->AccumuForce (Vector(0,-GY,0) * (Object3DParticles[i]->mass));  // Gravity

	  // cout<<"point mass"<<Object3DParticles[i].mass<<endl;

			switch(GoDir) {
	  
				case 1:     
				Object3DParticles[i]->AccumuForce(  Vector(0,WIND,0)*(Object3DParticles[i]->mass));  // Up force
				break;
	  
	  
				case 2:     
       Object3DParticles[i]->AccumuForce(Vector(0,-WIND,0) * (Object3DParticles[i]->mass));  // Down force
	  break;
	  
	  case 3:   
       Object3DParticles[i]->AccumuForce(  Vector(-WIND,0,0)*(Object3DParticles[i]->mass));  // Left force
	  break;
	  
	  case 4:    
       Object3DParticles[i]->AccumuForce(  Vector(WIND,0,0)*(Object3DParticles[i]->mass));  // Right force
	  break;
	  
	  default:
      break;                                       // Do nothing
	  }
      


      // When mouse is clicked, we apply a spring force (mouse spring) 
		if(i==closest_i) // closest point on the Object3D to the mouse  
		if(mousedown)			
		{
		  x1 = Object3DParticles[i]->r->x;		// get point X-coord
		  y1 = Object3DParticles[i]->r->y;        // get point Y-coord
		  z1 = Object3DParticles[i]->r->z;        // get point Z-coord

		  x2 = xMouse;                      // get Mouse  X-coord
		  y2 = yMouse;                      // get Mouse  Y-coord
          z2 = zMouse;                      // get Mouse  Z-coord

		r12d=sqrt( (x1-x2)*(x1-x2)
				 + (y1-y2)*(y1-y2)
				 + (z1-z2)*(z1-z2));        // distance between the two

			f=(r12d-RESTLEN) * KS + 
				( Object3DParticles[i]->v->x*(x1-x2)
			   +  Object3DParticles[i]->v->y*(y1-y2)
			   +  Object3DParticles[i]->v->z*(z1-z2) ) * (KD/r12d);

			// calculate spring force
			Fx = ((x1 - x2) / r12d ) * f;
			Fy = ((y1 - y2) / r12d ) * f;
            Fz = ((z1 - z2) / r12d ) * f;

			// accumulate this spring forces
			Object3DParticles[i]->f->x -= Fx; // from the closet point to the Mouse point
			Object3DParticles[i]->f->y -= Fy;
			Object3DParticles[i]->f->z -= Fz;
		} // closing end of mouse down

		} // closing end of (pressure>PRESSURE)

	  } // closing end for the loop for all the [i][j]
	 } // closing end of ExternalForces()


//####################################################################

void Object3D::PressureForces()     // pressure
{
	int i;

	 //	distribute a pressure forces to each of the points uniformly
	 // the pressure force is applied along its normal vector direction to maintain the
	 // object shape

	for(i=0; i<Object3DParticles.size(); i++)
	{
	
		{

			Object3DParticles[i]->AccumuForce(*Object3DParticles[i]->norm * pressure);		
		
		}
	}

}

//##########################################################

void Object3D::SpringForces()       // spring forces 
{
 /*  int j;

        	for (j=0; j<spring.size(); j++)
			{
            spring[j]->InverseConstraints();    // Inverse Dynamics Constraits 
			spring[j]->CalculateSpringForceT(); // Top end springs
	
			}

     */
/*
}

  
//###############################################################################


void Object3D::AccumulateForces(void)
{
//	ExternalForces();
//	PressureForces();   
//	SpringForces(); 
}

//#################################################################################

 
void Object3D::Derivatives(float dt)
{//cout<<"Object3D.derivative"<<endl;
	int i, j;

	for(i=0; i<Object3DParticles.size(); i++)
	{		

		{
/*	Object3DParticles[i]->dv = &(*Object3DParticles[i]->f * Object3DParticles[i]->OneOverMass * dt);
	Object3DParticles[i]->v  = &(*Object3DParticles[i]->v + *Object3DParticles[i]->dv);
    Object3DParticles[i]->dr = &(*Object3DParticles[i]->v * dt);
 */

// Check #1 - X boundaries
 /* if ((Object3DParticles[i].r->x + Object3DParticles[i].dr->x) < -LIMIT )
	{
       Object3DParticles[i].dr->x = -LIMIT - Object3DParticles[i].r->x;
	   Object3DParticles[i].v->x = - 0.2 * Object3DParticles[i].v->x;
       Object3DParticles[i].v->y =   0.9 * Object3DParticles[i].v->y;
       Object3DParticles[i].v->z =   0.9 * Object3DParticles[i].v->z;   
	}
	else if ((Object3DParticles[i].r->x + Object3DParticles[i].dr->x) > LIMIT )
	{
       Object3DParticles[i].dr->x = LIMIT - Object3DParticles[i].r->x;
	   Object3DParticles[i].v->x = - 0.2 * Object3DParticles[i].v->x;
       Object3DParticles[i].v->y =   0.9 * Object3DParticles[i].v->y;
       Object3DParticles[i].v->z =   0.9 * Object3DParticles[i].v->z;   
	} 

        Object3DParticles[i].r->x  = Object3DParticles[i].r->x + Object3DParticles[i].dr->x;

// Check #2 - Y boundaries	

	if ((Object3DParticles[i].r->y + Object3DParticles[i].dr->y) < -LIMIT )
	{
       Object3DParticles[i].dr->y = -LIMIT - Object3DParticles[i].r->y;
	   Object3DParticles[i].v->y = - 0.2 * Object3DParticles[i].v->y;
       Object3DParticles[i].v->z =   0.9 * Object3DParticles[i].v->z;
       Object3DParticles[i].v->x =   0.9 * Object3DParticles[i].v->x;   
	}else
    if ((Object3DParticles[i].r->y + Object3DParticles[i].dr->y) > LIMIT )
	{
       Object3DParticles[i].dr->y = LIMIT - Object3DParticles[i].r->y;
	   Object3DParticles[i].v->y = - 0.2 * Object3DParticles[i].v->y;
       Object3DParticles[i].v->z =   0.9 * Object3DParticles[i].v->z;
       Object3DParticles[i].v->x =   0.9 * Object3DParticles[i].v->x;   
	}

        Object3DParticles[i].r->y  = Object3DParticles[i].r->y + Object3DParticles[i].dr->y;
	
// Check #3 - Z boundary
		
      if ((Object3DParticles[i].r->z + Object3DParticles[i].dr->z) < -LIMIT )
	{
       Object3DParticles[i].dr.z = -LIMIT - Object3DParticles[i].r->z;
	   Object3DParticles[i].v.z = - 0.2 * Object3DParticles[i].v->z;
       Object3DParticles[i].v.x =   0.9 * Object3DParticles[i].v->x;
       Object3DParticles[i].v.y =   0.9 * Object3DParticles[i].v->y;   
	}else
    if ((Object3DParticles[i].r.z + Object3DParticles[i].dr.z) > LIMIT )
	{
       Object3DParticles[i].dr.z = LIMIT - Object3DParticles[i].r.z;
	   Object3DParticles[i].v.z = - 0.2 * Object3DParticles[i].v.z;
       Object3DParticles[i].v.x =   0.9 * Object3DParticles[i].v.x;
       Object3DParticles[i].v.y =   0.9 * Object3DParticles[i].v.y;   
	}

        Object3DParticles[i].r.z  = Object3DParticles[i].r.z + Object3DParticles[i].dr->z;

// Check #4 - Boundary limitations

      if (Object3DParticles[i].r->x < -LIMIT) Object3DParticles[i].r->x = -LIMIT;
      if (Object3DParticles[i].r->y < -LIMIT) Object3DParticles[i].r->y = -LIMIT;
      if (Object3DParticles[i].r->z < -LIMIT) Object3DParticles[i].r->z = -LIMIT;

      if (Object3DParticles[i].r->x > LIMIT) Object3DParticles[i].r->x = LIMIT;
      if (Object3DParticles[i].r->y > LIMIT) Object3DParticles[i].r->y = LIMIT;
      if (Object3DParticles[i].r->z > LIMIT) Object3DParticles[i].r->z = LIMIT;

		*//*	}		
	}
}	
*/
void Object3D::GetClosestParticle(void)
{
/*	float dmin;
//	float dtomouse;      // the clicked mouse position
	int i,j;

	// find closest point
	dmin = sqrt( pow(Object3DParticles[closest_i].r.x - xMouse,2)
		       + pow(Object3DParticles[closest_i].r.y - yMouse,2)
			   + pow(Object3DParticles[closest_i].r.y - yMouse,2) );


    for(i=0; i<Object3DParticles.size(); i++)
	{

		{
           
      dtomouse = sqrt( pow(Object3DParticles[i].r.x - xMouse,2)
		          +    pow(Object3DParticles[i].r.y - xMouse,2)
				  +    pow(Object3DParticles[i].r.z - xMouse,2) );
						
		   if(dtomouse < dmin)
			{
			dmin = dtomouse;
			closest_i = i;
			closest_j = j;
			}


		}		
	}*/
}



void Object3D::Mouse(int button, int state, int x, int y)
{
/*	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mousedown = 1;

			xMouse =  LIMIT * 2.0 * ( (float)x/(float)Width  - 0.5);
			yMouse = -LIMIT * 2.0 * ( (float)y/(float)Height - 0.5);
            zMouse = 0.0;
			
	//		inner.Object3DParticles.push_back( Point(Vector(xMouse, yMouse, zMouse),0)); 
	//		inner.spring.push_back( Spring(&inner.Object3DParticles[Object3DParticles.size()-1],&inner.Object3DParticles[0], KS,KD));
                                          
		}

		 

		else if (state == GLUT_UP)
		{
	//		GetClosestPoint();
	       	mousedown = 0;


	  	}
     }*/
}




void Object3D::Motion (int x, int y)
{
/*   if(mousedown)
   {

     xMouse =   LIMIT * 2.0 * ( (float)x/(float)Width  - 1/2.0 );
     yMouse = - LIMIT * 2.0 * ( (float)y/(float)Height - 1/2.0 );
     zMouse = 0.0;

     glutPostRedisplay();
   }*/
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Object3D::Rotated(void)
{  
   cout<<"3D rotate"<<endl;
   glRotated(RotateRegX, 1.0, 0.0, 0.0);  // Rotate 90 about X-axis 
   glRotated(RotateRegY, 0.0, 1.0, 0.0);  // Rotate 90 about X-axis 
   glRotated(RotateRegZ, 0.0, 0.0, 1.0);  // Rotate 90 about X-axis 
	
} 

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Object3D::Keyboard(unsigned char key, int x, int y)
{
	cout<<"3D keyboard"<<endl;
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
		break;                           // do nothing
	}
} 
  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void Object3D::SpecialKeys(int key, int x, int y)
{

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


//================================================================================

void Object3D::Draw()
{		 

 	int i;
 //===============================================================================
	glColor4f(0,0,1,1);   // Blue color point distribution
	glBegin(GL_POINTS); // Draw points which built the Object3D
		glPointSize(10);
	
	     for(i=0; i<Object3DParticles.size(); i++)
		{
	//	  cout<<"Object3D size is : "<<i<<endl;
		glVertex3f(Object3DParticles[i]->r->x, Object3DParticles[i]->r->y, Object3DParticles[i]->r->z);	
		
		}

 	glEnd();
//===================================================================================
 
/*	glColor4f(1,1,1,1);   // White color line for normal at each of the points

	glBegin(GL_LINES);  
		
    for(i=0; i<Object3DParticles.size(); i++)
		{
	 
		 {

glVertex3f(Object3DParticles[i].r.x, Object3DParticles[i].r.y, Object3DParticles[i].r.z);
glVertex3f(Object3DParticles[i].r.x+Object3DParticles[i].norm.x, 
		   Object3DParticles[i].r.y+Object3DParticles[i].norm.y, 
		   Object3DParticles[i].r.z+Object3DParticles[i].norm.z);
	   	   
			}
		}
   
	glEnd();*/
//=======================================================================================





 //=================================================================================  
	glColor4f(1,0,0,1);   // Red color line distribution

	glBegin(GL_LINES);  // draw the Horizonal and Tangent springs 
		
    for(i=0; i<spring.size(); i++)
		{
//	 cout<<"spring size: "<<spring.size()<<endl;
	   glVertex3f(spring[i]->sp1->r->x, spring[i]->sp1->r->y, spring[i]->sp1->r->z);
	   glVertex3f(spring[i]->sp2->r->x, spring[i]->sp2->r->y, spring[i]->sp2->r->z);
			
		}

//cout<<spring[0].sp1->r.x<<"; "<<spring[0].sp1->r.y<<";  "<<spring[0].sp1->r.z<<endl;
//cout<<spring[0].sp2->r.x<<";  "<<spring[0].sp2->r.y<<";  "<<spring[0].sp2->r.z<<endl;
//	cout<<"springsize: "<<spring.size()<<",  points size: "<<Object3DParticles.size()<<endl;

	glEnd();


 glBegin(GL_TRIANGLES);  	  
	 for(i=0; i<face.size(); i++)
		{
	//	 if(i==0)
	//		 glColor4f(0,0,0,1);
		//	glNormal3f (tri[i].normal.x, tri[i].normal.y, tri[i].normal.z);
	//	 else
		 glColor4f(1,0.8,0.2,.8);     	    // Yellow color face distribution
	     glVertex3f(face[i]->fp1->r->x, face[i]->fp1->r->y, face[i]->fp1->r->z);
		 glVertex3f(face[i]->fp2->r->x, face[i]->fp2->r->y, face[i]->fp2->r->z);
		 glVertex3f(face[i]->fp3->r->x, face[i]->fp3->r->y, face[i]->fp3->r->z);
	
		}
	glEnd();


/*	glBegin(GL_LINES);
	
		 glVertex3f(face[i].fp2.r.x, face[i].fp2.r.y, face[i].fp2.r.z);
		 glVertex3f(face[i].fp3.r.x, face[i].fp3.r.y, face[i].fp3.r.z);
	glEnd();

	glBegin(GL_LINES);
		 glVertex3f(face[i].fp1.r.x, face[i].fp1.r.y, face[i].fp1.r.z);
		
		 glVertex3f(face[i].fp3.r.x, face[i].fp3.r.y, face[i].fp3.r.z);
		 	glEnd();
}*/
//=======================================================================================

//=======================================================================================

/*	if(mousedown)
	{
	  glColor3f(1,1,1);      // A white line between the Object3D point and the mouse point
	  glBegin(GL_LINES);
		glVertex3f(xMouse,yMouse, zMouse);
   	   	glVertex3f(Object3DParticles[closest_i].r.x,
			       Object3DParticles[closest_i].r.y,
				   Object3DParticles[closest_i].r.z);
       glEnd();
	}                   
*/
//======================================================================================




	
 /*
 glBegin(GL_TRIANGLES);  	  
	 for(i=0; i<face.size(); i++)
		{
		
		 glColor4f(.1,.6,.1,.8);     	    // Yellow color face distribution
	     glVertex3f(face[i].fp1.r.x, face[i].fp1.r.y, face[i].fp1.r.z);
		 glVertex3f(face[i].fp2.r.x, face[i].fp2.r.y, face[i].fp2.r.z);
		 glVertex3f(face[i].fp3.r.x, face[i].fp3.r.y, face[i].fp3.r.z);
	
		}
	glEnd();

	*/
//---------------------------------------------------------------------------------------

}

