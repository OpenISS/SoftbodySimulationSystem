#include "Object3D.h"

//using vector pointers


// Mouse variables
/*int mousedown =0;                // for GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON
float xMouse, yMouse, zMouse;    // for mouse point r(x,y,z) 
int closest_i, closest_j;        // Closest point index i, j 
*/
// Keyboard variables
/*int   GoDir;           // for GLUT_KEY_LEFT,GLUT_KEY_RIGHT,GLUT_KEY_UP,GLUT_KEY_DOWN
float RotateRegX=0;    // for glRotatef() rotating direction
float RotateRegY=0;    // for glRotatef() rotating direction
float RotateRegZ=0;    // for glRotatef() rotating direction
*/

//extern Object3D inner;


/*vector<Point> t_outer_points;
//vector <Spring>  spring; 
vector<Face> t_Face; 
//Face t_Face;*/

Object3D::Object3D() 
{	
	pa=new Particle(new Vector(0,0,0), MASS);
	pb=new Particle(new Vector(0,0,0), MASS);
	pc=new Particle(new Vector(0,0,0), MASS);

	numParticles = NUMPOINTS;
	numSprings =  NUMSPRINGS;
	SetObject();
	dim = DIM3D;
}
/*


Object3D::Object3D(float MASS, float ks, float kd)
{
	pressure=0;
//	KS=KS;
//	KD=KD;
	MASS=MASS;


SetParticles();
	dim = DIM3D;
}*/


Object3D::~Object3D()
{
/*	delete pa;
	delete pb;
	delete pc;
*/
}



void Object3D::Add_Structural_Spring(int index, int h, int t)
{

   	inner_springs.push_back( new Spring(inner_points[h],inner_points[t]));
	outer_springs.push_back( new Spring(outer_points[h],outer_points[t]));

	inner_springs[index]->setRestLen();					//set the inner spring's length
	outer_springs[index]->setRestLen();					//set the outer spring's length
}



void Object3D::SetObject(void) // [M+2][N] array for M*N+2 Points 
{
	outer_points.clear();
	inner_points.clear();
	outer_faces.clear();
	inner_faces.clear();
	outer_springs.clear();
	inner_springs.clear();

	double a;
	int nt=0/*, ntold*/;
	int i;
  
 
	//outer_points.addElement();


	outer_points.push_back( new Particle(new Vector(0,0,0.5), MASS));
	outer_points.push_back( new Particle(new Vector(0,0,-0.5), MASS));
	outer_points.push_back( new Particle(new Vector(-0.5,-0.5,0), MASS));
	outer_points.push_back( new Particle(new Vector(0.5,-0.5,0), MASS));
	outer_points.push_back( new Particle(new Vector(0.5,0.5,0), MASS));
	outer_points.push_back( new Particle(new Vector(-0.5,0.5,0), MASS));

	inner_points.push_back( new Particle(new Vector(0,0,1), MASS));
	inner_points.push_back( new Particle(new Vector(0,0,-1), MASS));
	inner_points.push_back( new Particle(new Vector(-1,-1,0), MASS));
	inner_points.push_back( new Particle(new Vector(1,-1,0), MASS));
	inner_points.push_back( new Particle(new Vector(1,1,0), MASS));
	inner_points.push_back( new Particle(new Vector(-1,1,0), MASS));

	this->numSprings = this->numParticles = inner_points.size();
	

/*	cout<<"outer_points so far: " <<outer_points.size()<<endl; 

	a = 1 / sqrt(2.0);

	for (i=0;i<outer_points.size();i++)
	{
		outer_points[i]->r->x *= a;
		outer_points[i]->r->y *= a;

	}

*/

/*	for(i=0; i<numParticles ;i++)						//add the springs for outer & inner
	{  
		Add_Structural_Spring(i,i,(i+1) % numParticles); 
		Add_Radium_Spring(i) ;
		Add_Shear_Spring(i,i,(i+1) % numParticles);
		Add_Faces(i, (i+1) % numParticles, (numParticles/2 + i) % numParticles) ;

	}
*/
//	/*
	outer_faces.push_back(new Face(outer_points[0], outer_points[3], outer_points[4]));
	outer_faces.push_back(new Face(outer_points[0], outer_points[4], outer_points[5]));
	outer_faces.push_back(new Face(outer_points[0], outer_points[5], outer_points[2]));
	outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3]));
	outer_faces.push_back(new Face(outer_points[1], outer_points[4], outer_points[3]));
	outer_faces.push_back(new Face(outer_points[1], outer_points[5], outer_points[4]));
	outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[5]));
	outer_faces.push_back(new Face(outer_points[1], outer_points[3], outer_points[2]));
//*/

	inner_faces.push_back(new Face(inner_points[0], inner_points[3], inner_points[4]));
	inner_faces.push_back(new Face(inner_points[0], inner_points[4], inner_points[5]));
	inner_faces.push_back(new Face(inner_points[0], inner_points[5], inner_points[2]));
	inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3]));
	inner_faces.push_back(new Face(inner_points[1], inner_points[4], inner_points[3]));
	inner_faces.push_back(new Face(inner_points[1], inner_points[5], inner_points[4]));
	inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[5]));
	inner_faces.push_back(new Face(inner_points[1], inner_points[3], inner_points[2]));



	for (i=0; i<outer_faces.size(); i++) // On each horizonal plane, N tangent springs
		{
	     
		    outer_springs.push_back(new Spring(outer_faces[i]->fp1, outer_faces[i]->fp2,KS,KD));     // row i with offset j
			outer_springs.push_back(new Spring(outer_faces[i]->fp2, outer_faces[i]->fp3,KS,KD));
			outer_springs.push_back(new Spring(outer_faces[i]->fp3, outer_faces[i]->fp1,KS,KD));
	
			
	        inner_springs.push_back(new Spring(inner_faces[i]->fp1, inner_faces[i]->fp2,KS,KD));     // row i with offset j
			inner_springs.push_back(new Spring(inner_faces[i]->fp2, inner_faces[i]->fp3,KS,KD));
			inner_springs.push_back(new Spring(inner_faces[i]->fp3, inner_faces[i]->fp1,KS,KD));
	
		}

/*	cout<<"spring size="<<spring.size()<<endl;
	cout<<"outer_points so far: " <<outer_points.size()<<endl; 
 
	for (int it=0; it<iterations;it++){

		int ntold=outer_faces.size();
		static int j=0;
	   for(int i=0;i<1;i++){

		   pa->r->x=(outer_faces[i]->fp1->r->x+outer_faces[i]->fp2->r->x)/2;
		   pa->r->y=(outer_faces[i]->fp1->r->y+outer_faces[i]->fp2->r->y)/2;
		   pa->r->z=(outer_faces[i]->fp1->r->z+outer_faces[i]->fp2->r->z)/2;
		   
		   pb->r->x=(outer_faces[i]->fp2->r->x+outer_faces[i]->fp3->r->x)/2;
		   pb->r->y=(outer_faces[i]->fp2->r->y+outer_faces[i]->fp3->r->y)/2;
		   pb->r->z=(outer_faces[i]->fp2->r->z+outer_faces[i]->fp3->r->z)/2;

		   pc->r->x=(outer_faces[i]->fp1->r->x+outer_faces[i]->fp3->r->x)/2;
		   pc->r->y=(outer_faces[i]->fp1->r->y+outer_faces[i]->fp3->r->y)/2;
		   pc->r->z=(outer_faces[i]->fp1->r->z+outer_faces[i]->fp3->r->z)/2;

		  
		 
		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
*//*		   pa->r->Normalize();
		   pb->r->Normalize();
		   pc->r->Normalize();
*/
/*		   cout<<"after normalization: "<<endl;

		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
*/
/**/
 /*          outer_points.push_back(new Particle(new Vector(pa->r->x, pa->r->y, pa->r->z), MASS)); 
		   outer_points.push_back(new Particle(new Vector(pb->r->x, pb->r->y, pb->r->z), MASS)); 
		   outer_points.push_back(new Particle(new Vector(pc->r->x, pc->r->y, pc->r->z), MASS)); 
 */
		   

          /* outer_faces.push_back(new Face(outer_faces[i]->fp1,pa,pc));
	       outer_faces.push_back(new Face(pa,outer_faces[i]->fp2,pb));
	       outer_faces.push_back(new Face(pb,outer_faces[i]->fp3,pc)); 
 
		   spring.push_back(new Spring(outer_faces[i]->fp1, pa,KS,KD));     // row i with offset j
		   spring.push_back(new Spring(pa, outer_faces[i]->fp2,KS,KD));
		   spring.push_back(new Spring(outer_faces[i]->fp2, pb,KS,KD));
		   spring.push_back(new Spring(pb, outer_faces[i]->fp3,KS,KD));
		   spring.push_back(new Spring(outer_faces[i]->fp3, pc,KS,KD));
		   spring.push_back(new Spring(pc, outer_faces[i]->fp1,KS,KD));
		   */


/*		   Face* f1=new Face(outer_faces[i]->fp1,pa,pc);
		   outer_faces.push_back(f1);
		  //delete f1;
		   Face* f2=new Face(pa,outer_faces[i]->fp2,pb);
	       outer_faces.push_back(f2);
		   Face* f3=new Face(pb,outer_faces[i]->fp3,pc);
	       outer_faces.push_back(f3); 
 
		   //Spring *s1
		   spring.push_back(new Spring(outer_faces[i]->fp1, pa,KS,KD));     // row i with offset j
		   spring.push_back(new Spring(pa, outer_faces[i]->fp2,KS,KD));
		   spring.push_back(new Spring(outer_faces[i]->fp2, pb,KS,KD));
		   spring.push_back(new Spring(pb, outer_faces[i]->fp3,KS,KD));
		   spring.push_back(new Spring(outer_faces[i]->fp3, pc,KS,KD));
		   spring.push_back(new Spring(pc, outer_faces[i]->fp1,KS,KD));
		   
		   
		   spring[j]->sp1=pa;
		   spring[j]->sp2=pb;
		   j++;
		   spring[j]->sp1=pb;
		   spring[j]->sp2=pc;
		   j++;
		   spring[j]->sp1=pc;
		   spring[j]->sp2=pa;
		   j++;

	       outer_faces[i]->fp1=pa;
	       outer_faces[i]->fp2=pb;
	       outer_faces[i]->fp3=pc;
 
		  
	   }
	}
	//
  */

 
  
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
	

	for(i=0; i<outer_points.size(); i++)      //  external forces are calculated here 
	{
		outer_points[i]->ClearForce();  // reset any existing forces

		if ((pressure-PRESSURE)>=0)
		{
			outer_points[i]->AccumuForce (Vector(0,-GY,0) * (outer_points[i]->MASS));  // Gravity

	  // cout<<"point MASS"<<outer_points[i].MASS<<endl;

			switch(GoDir) {
	  
				case 1:     
				outer_points[i]->AccumuForce(  Vector(0,WIND,0)*(outer_points[i]->MASS));  // Up force
				break;
	  
	  
				case 2:     
       outer_points[i]->AccumuForce(Vector(0,-WIND,0) * (outer_points[i]->MASS));  // Down force
	  break;
	  
	  case 3:   
       outer_points[i]->AccumuForce(  Vector(-WIND,0,0)*(outer_points[i]->MASS));  // Left force
	  break;
	  
	  case 4:    
       outer_points[i]->AccumuForce(  Vector(WIND,0,0)*(outer_points[i]->MASS));  // Right force
	  break;
	  
	  default:
      break;                                       // Do nothing
	  }
      


      // When mouse is clicked, we apply a spring force (mouse spring) 
		if(i==closest_i) // closest point on the Object3D to the mouse  
		if(mousedown)			
		{
		  x1 = outer_points[i]->r->x;		// get point X-coord
		  y1 = outer_points[i]->r->y;        // get point Y-coord
		  z1 = outer_points[i]->r->z;        // get point Z-coord

		  x2 = xMouse;                      // get Mouse  X-coord
		  y2 = yMouse;                      // get Mouse  Y-coord
          z2 = zMouse;                      // get Mouse  Z-coord

		r12d=sqrt( (x1-x2)*(x1-x2)
				 + (y1-y2)*(y1-y2)
				 + (z1-z2)*(z1-z2));        // distance between the two

			f=(r12d-RESTLEN) * KS + 
				( outer_points[i]->v->x*(x1-x2)
			   +  outer_points[i]->v->y*(y1-y2)
			   +  outer_points[i]->v->z*(z1-z2) ) * (KD/r12d);

			// calculate spring force
			Fx = ((x1 - x2) / r12d ) * f;
			Fy = ((y1 - y2) / r12d ) * f;
            Fz = ((z1 - z2) / r12d ) * f;

			// accumulate this spring forces
			outer_points[i]->f->x -= Fx; // from the closet point to the Mouse point
			outer_points[i]->f->y -= Fy;
			outer_points[i]->f->z -= Fz;
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

	for(i=0; i<outer_points.size(); i++)
	{
	
		{

			outer_points[i]->AccumuForce(*outer_points[i]->norm * pressure);		
		
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

	for(i=0; i<outer_points.size(); i++)
	{		

		{
/*	outer_points[i]->dv = &(*outer_points[i]->f * outer_points[i]->OneOverMASS * dt);
	outer_points[i]->v  = &(*outer_points[i]->v + *outer_points[i]->dv);
    outer_points[i]->dr = &(*outer_points[i]->v * dt);
 */

// Check #1 - X boundaries
 /* if ((outer_points[i].r->x + outer_points[i].dr->x) < -LIMIT )
	{
       outer_points[i].dr->x = -LIMIT - outer_points[i].r->x;
	   outer_points[i].v->x = - 0.2 * outer_points[i].v->x;
       outer_points[i].v->y =   0.9 * outer_points[i].v->y;
       outer_points[i].v->z =   0.9 * outer_points[i].v->z;   
	}
	else if ((outer_points[i].r->x + outer_points[i].dr->x) > LIMIT )
	{
       outer_points[i].dr->x = LIMIT - outer_points[i].r->x;
	   outer_points[i].v->x = - 0.2 * outer_points[i].v->x;
       outer_points[i].v->y =   0.9 * outer_points[i].v->y;
       outer_points[i].v->z =   0.9 * outer_points[i].v->z;   
	} 

        outer_points[i].r->x  = outer_points[i].r->x + outer_points[i].dr->x;

// Check #2 - Y boundaries	

	if ((outer_points[i].r->y + outer_points[i].dr->y) < -LIMIT )
	{
       outer_points[i].dr->y = -LIMIT - outer_points[i].r->y;
	   outer_points[i].v->y = - 0.2 * outer_points[i].v->y;
       outer_points[i].v->z =   0.9 * outer_points[i].v->z;
       outer_points[i].v->x =   0.9 * outer_points[i].v->x;   
	}else
    if ((outer_points[i].r->y + outer_points[i].dr->y) > LIMIT )
	{
       outer_points[i].dr->y = LIMIT - outer_points[i].r->y;
	   outer_points[i].v->y = - 0.2 * outer_points[i].v->y;
       outer_points[i].v->z =   0.9 * outer_points[i].v->z;
       outer_points[i].v->x =   0.9 * outer_points[i].v->x;   
	}

        outer_points[i].r->y  = outer_points[i].r->y + outer_points[i].dr->y;
	
// Check #3 - Z boundary
		
      if ((outer_points[i].r->z + outer_points[i].dr->z) < -LIMIT )
	{
       outer_points[i].dr.z = -LIMIT - outer_points[i].r->z;
	   outer_points[i].v.z = - 0.2 * outer_points[i].v->z;
       outer_points[i].v.x =   0.9 * outer_points[i].v->x;
       outer_points[i].v.y =   0.9 * outer_points[i].v->y;   
	}else
    if ((outer_points[i].r.z + outer_points[i].dr.z) > LIMIT )
	{
       outer_points[i].dr.z = LIMIT - outer_points[i].r.z;
	   outer_points[i].v.z = - 0.2 * outer_points[i].v.z;
       outer_points[i].v.x =   0.9 * outer_points[i].v.x;
       outer_points[i].v.y =   0.9 * outer_points[i].v.y;   
	}

        outer_points[i].r.z  = outer_points[i].r.z + outer_points[i].dr->z;

// Check #4 - Boundary limitations

      if (outer_points[i].r->x < -LIMIT) outer_points[i].r->x = -LIMIT;
      if (outer_points[i].r->y < -LIMIT) outer_points[i].r->y = -LIMIT;
      if (outer_points[i].r->z < -LIMIT) outer_points[i].r->z = -LIMIT;

      if (outer_points[i].r->x > LIMIT) outer_points[i].r->x = LIMIT;
      if (outer_points[i].r->y > LIMIT) outer_points[i].r->y = LIMIT;
      if (outer_points[i].r->z > LIMIT) outer_points[i].r->z = LIMIT;

		*//*	}		
	}
}	
*/







//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//================================================================================

void Object3D::Draw()
{		 

 	int i;
 //===============================================================================
	glPushMatrix();
	glColor4f(0,0,1,1);   // Blue color point distribution
	glBegin(GL_POINTS); // Draw points which built the Object3D
		glPointSize(10);
	
	     for(i=0; i<outer_points.size(); i++)
		{
	//	  cout<<"Object3D size is : "<<i<<endl;
		glVertex3f(outer_points[i]->r->x, outer_points[i]->r->y, outer_points[i]->r->z);	
			
//		glVertex3f(inner_points[i]->r->x, inner_points[i]->r->y, inner_points[i]->r->z);	
	
		}

 	glEnd();
	glPopMatrix();
//===================================================================================
 
/*	glColor4f(1,1,1,1);   // White color line for normal at each of the points

	glBegin(GL_LINES);  
		
    for(i=0; i<outer_points.size(); i++)
		{
	 
		 {

glVertex3f(outer_points[i].r.x, outer_points[i].r.y, outer_points[i].r.z);
glVertex3f(outer_points[i].r.x+outer_points[i].norm.x, 
		   outer_points[i].r.y+outer_points[i].norm.y, 
		   outer_points[i].r.z+outer_points[i].norm.z);
	   	   
			}
		}
   
	glEnd();*/
//=======================================================================================





 //=================================================================================  
	 // Red color line distribution

/*	glBegin(GL_LINES);  // draw the Horizonal and Tangent springs 
		
    for(i=0; i<spring.size(); i++)
		{
//	 cout<<"spring size: "<<spring.size()<<endl;
	   glVertex3f(spring[i]->sp1->r->x, spring[i]->sp1->r->y, spring[i]->sp1->r->z);
	   glVertex3f(spring[i]->sp2->r->x, spring[i]->sp2->r->y, spring[i]->sp2->r->z);
			
		}

//cout<<spring[0].sp1->r.x<<"; "<<spring[0].sp1->r.y<<";  "<<spring[0].sp1->r.z<<endl;
//cout<<spring[0].sp2->r.x<<";  "<<spring[0].sp2->r.y<<";  "<<spring[0].sp2->r.z<<endl;
//	cout<<"springsize: "<<spring.size()<<",  points size: "<<outer_points.size()<<endl;

	glEnd();

*/
/* glBegin(GL_TRIANGLES);  	  
	 for(i=0; i<outer_faces.size(); i++)
		{
	//	 if(i==0)
	//		 glColor4f(0,0,0,1);
		//	glNormal3f (tri[i].normal.x, tri[i].normal.y, tri[i].normal.z);
	//	 else
		 glColor4f(1,0.8,0.2,.8);     	    // Yellow color face distribution
	     glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
		 glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
		 glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
	
		}
	glEnd();*/
	glPushMatrix();
	glColor4f(1,0,0,1);  
	  for(i=0; i<outer_faces.size(); i++)
	  {
		glBegin(GL_LINES);
		
			 glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
			 glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
		glEnd();

		glBegin(GL_LINES);
			 glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
			
			 glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
		 		glEnd();


		glBegin(GL_LINES);
			 glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
			
			 glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
		 		glEnd();



	}
	  glPopMatrix();
//=======================================================================================

//=======================================================================================

/*	if(mousedown)
	{
	  glColor3f(1,1,1);      // A white line between the Object3D point and the mouse point
	  glBegin(GL_LINES);
		glVertex3f(xMouse,yMouse, zMouse);
   	   	glVertex3f(outer_points[closest_i].r.x,
			       outer_points[closest_i].r.y,
				   outer_points[closest_i].r.z);
       glEnd();
	}                   
*/
//======================================================================================



//cout<<"outer_faces.size======="<<outer_faces.size()<<endl;
	
 	glPushMatrix();
 glBegin(GL_TRIANGLES);  	  
	 for(i=0; i<outer_faces.size(); i++)
		{
		
		 glColor4f(1.0,1.0,1.0,.8);     	    // Yellow color face distribution
	     glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
		 glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
		 glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
	
		}
	glEnd();

	glPopMatrix();
//---------------------------------------------------------------------------------------

}

