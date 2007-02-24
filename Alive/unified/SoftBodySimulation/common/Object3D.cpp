#include "Object3D.h"

#include <assert.h>

Object3D::Object3D() 
{	
	pa = new Particle(new Vector(0,0,0), MASS);
	pb = new Particle(new Vector(0,0,0), MASS);
	pc = new Particle(new Vector(0,0,0), MASS);

	// It is *IMPORTANT* to realize that most of the time
	// the number of particles and springs are not the same
	// in 3D (unlike 2D) so these have to be updated to the
	// actual number of particles and springs when the geometry
	// is initially constructed or altered
	numParticles = NUMPOINTS;
	numSprings = NUMSPRINGS;

	iterations = 1;
	SetObject();

	dim = DIM3D;
}



Object3D::~Object3D()
{
/*	delete pa;
	delete pb;
	delete pc;
*/
}



void Object3D::Add_Structural_Spring(int index, int h, int t)
{
	// making sure nobody actuall calls it
/*	assert(false);

  	inner_springs.push_back( new Spring(inner_points[h],inner_points[t]));
	outer_springs.push_back( new Spring(outer_points[h],outer_points[t]));
 
*/
	
/*		inner_springs.push_back( new Spring());
	outer_springs.push_back( new Spring());
*/
/*	inner_springs[index]->setRestLen();					//set the inner spring's length
	outer_springs[index]->setRestLen();					//set the outer spring's length
*/
}


////////////////////////////////////////////////////



void Object3D::Add_Radium_Spring(int index)
{
   	
	radium_springs.push_back( new Spring(inner_springs[index]->sp1,outer_springs[index]->sp1));
	radium_springs[index]->setRestLen();						//set the radium spring's length
} 


void Object3D::Add_Shear_Spring(int index )
{
      
	
	shear_springs_left.push_back(new Spring(inner_springs[index]->sp1,outer_springs[index]->sp2));
	shear_springs_right.push_back(new Spring(inner_springs[index]->sp2, outer_springs[index]->sp1));


	shear_springs_left[index]->setRestLen();					//set the shear left spring's length
	shear_springs_right[index]->setRestLen();				//set the shear right spring's length

} 




/*
	for (int it=0; it<iterations;it++){

		int ntold=triface.size();
		static int j=0;
	   for(int i=0;i<ntold;i++){

		   pa.r=(triface[i].fp1.r+triface[i].fp2.r)/2;
		   pb.r=(triface[i].fp2.r+triface[i].fp3.r)/2;
		   pc.r=(triface[i].fp3.r+triface[i].fp1.r)/2;
		 
           cout<<"pa.x="<<pa.r.x<<"; pa.y="<<pa.r.y<<"; pa.z="<<pa.r.z<<endl;
		   cout<<"pb.x="<<pb.r.x<<"; pb.y="<<pb.r.y<<"; pb.z="<<pb.r.z<<endl;
		   cout<<"pc.x="<<pc.r.x<<"; pc.y="<<pc.r.y<<"; pc.z="<<pc.r.z<<endl;
		   

		   
		   pa.r.Normalize();
		   pb.r.Normalize();
		   pc.r.Normalize();


		   cout<<"after normalization: "<<endl;

		   cout<<"pa.x="<<pa.r.x<<"; pa.y="<<pa.r.y<<"; pa.z="<<pa.r.z<<endl;
		   cout<<"pb.x="<<pb.r.x<<"; pb.y="<<pb.r.y<<"; pb.z="<<pb.r.z<<endl;
		   cout<<"pc.x="<<pc.r.x<<"; pc.y="<<pc.r.y<<"; pc.z="<<pc.r.z<<endl;


         //  ballpoints.push_back(Point(Vector(0,0,1), Bmass));
           ballpoints.push_back(Point(Vector(pa.r.x, pa.r.y, pa.r.z), Bmass)); 
		   ballpoints.push_back(Point(Vector(pb.r.x, pb.r.y, pb.r.z), Bmass)); 
		   ballpoints.push_back(Point(Vector(pc.r.x, pc.r.y, pc.r.z), Bmass)); 

		   

    
 
		   triface.push_back(Triface(triface[i].fp1,pa,pc));
	       triface.push_back(Triface(pa,triface[i].fp2,pb));
	       triface.push_back(Triface(pb,triface[i].fp3,pc)); 


		   spring.push_back(Spring(triface[i].fp1, pa,ks,kd));     // row i with offset j
		   spring.push_back(Spring(pa, triface[i].fp2,ks,kd));
		   spring.push_back(Spring(triface[i].fp2, pb,ks,kd));
		   spring.push_back(Spring(pb, triface[i].fp3,ks,kd));
		   spring.push_back(Spring(triface[i].fp3, pc,ks,kd));
		   spring.push_back(Spring(pc, triface[i].fp1,ks,kd));
		   
		   spring[j].sp1=pa;
		   spring[j].sp2=pb;
		   j++;
		   spring[j].sp1=pb;
		   spring[j].sp2=pc;
		   j++;
		   spring[j].sp1=pc;
		   spring[j].sp2=pa;
	       j++;


		   triface[i].fp1=pa;
	       triface[i].fp2=pb;
	       triface[i].fp3=pc;
 
	   }
	}

*/


//==============================================================================
void Object3D::Iteration()
{
	// Spring triplets counter for older springs particle replacements
	static int j = 0;

	for (int it=0; it<iterations;it++)
	{
	   int initialFacesCount = 2;//outer_faces.size();

	   for(int i=0;i<initialFacesCount;i++)
	   {

		   pa->r->x=(outer_faces[i]->fp1->r->x + outer_faces[i]->fp2->r->x)/2;
		   pa->r->y=(outer_faces[i]->fp1->r->y+outer_faces[i]->fp2->r->y)/2;
		   pa->r->z=(outer_faces[i]->fp1->r->z+outer_faces[i]->fp2->r->z)/2;
		   
		   pb->r->x=(outer_faces[i]->fp2->r->x+outer_faces[i]->fp3->r->x)/2;
		   pb->r->y=(outer_faces[i]->fp2->r->y+outer_faces[i]->fp3->r->y)/2;
		   pb->r->z=(outer_faces[i]->fp2->r->z+outer_faces[i]->fp3->r->z)/2;

		   pc->r->x=(outer_faces[i]->fp1->r->x+outer_faces[i]->fp3->r->x)/2;
		   pc->r->y=(outer_faces[i]->fp1->r->y+outer_faces[i]->fp3->r->y)/2;
		   pc->r->z=(outer_faces[i]->fp1->r->z+outer_faces[i]->fp3->r->z)/2;

		  
			///*
		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
		   //*/
		   
		   pa->r->Normalize();
		   pb->r->Normalize();
		   pc->r->Normalize();

	/*	   cout<<"after normalization: "<<endl;

		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
*/
/**/
           outer_points.push_back(new Particle(new Vector(pa->r->x, pa->r->y, pa->r->z), MASS)); 
		   outer_points.push_back(new Particle(new Vector(pb->r->x, pb->r->y, pb->r->z), MASS)); 
		   outer_points.push_back(new Particle(new Vector(pc->r->x, pc->r->y, pc->r->z), MASS)); 
 
		   // CXXXX: out of the blue
           inner_points.push_back(new Particle(new Vector(pa->r->x, pa->r->y, pa->r->z), MASS)); 
		   inner_points.push_back(new Particle(new Vector(pb->r->x, pb->r->y, pb->r->z), MASS)); 
		   inner_points.push_back(new Particle(new Vector(pc->r->x, pc->r->y, pc->r->z), MASS)); 

		   // Create three new faces
		   outer_faces.push_back(new Face(outer_faces[i]->fp1,pa,pc));
		   outer_faces.push_back(new Face(pa,outer_faces[i]->fp2,pb));
		   outer_faces.push_back(new Face(pb,outer_faces[i]->fp3,pc));
 
		   // New springs added after subdivision
/*		   outer_springs.push_back(new Spring(outer_faces[i]->fp1, pa,KS,KD));     // row i with offset j
		   outer_springs.push_back(new Spring(pa, outer_faces[i]->fp2,KS,KD));
		   outer_springs.push_back(new Spring(outer_faces[i]->fp2, pb,KS,KD));
		   outer_springs.push_back(new Spring(pb, outer_faces[i]->fp3,KS,KD));
		   outer_springs.push_back(new Spring(outer_faces[i]->fp3, pc,KS,KD));
		   outer_springs.push_back(new Spring(pc, outer_faces[i]->fp1,KS,KD));


		   inner_springs.push_back(new Spring(outer_faces[i]->fp1, pa,KS,KD));     // row i with offset j
		   inner_springs.push_back(new Spring(pa, outer_faces[i]->fp2,KS,KD));
		   inner_springs.push_back(new Spring(outer_faces[i]->fp2, pb,KS,KD));
		   inner_springs.push_back(new Spring(pb, outer_faces[i]->fp3,KS,KD));
		   inner_springs.push_back(new Spring(outer_faces[i]->fp3, pc,KS,KD));
		   inner_springs.push_back(new Spring(pc, outer_faces[i]->fp1,KS,KD));

		   // Replacement springs for the originals
		   outer_springs[j]->sp1=pa;
		   outer_springs[j]->sp2=pb;
		   j++;
		   outer_springs[j]->sp1=pb;
		   outer_springs[j]->sp2=pc;
		   j++;
		   outer_springs[j]->sp1=pc;
		   outer_springs[j]->sp2=pa;
		   j++;

		   // Replace the original face's points with its new one
	       outer_faces[i]->fp1=pa;
	       outer_faces[i]->fp2=pb;
	       outer_faces[i]->fp3=pc;
 */
	   }
	}

//	this->numParticles = this->outer_points.size();
//	this->numSprings = this->outer_springs.size();
	
}




///////////////==================================================================
void Object3D::SetObject(void) // [M+2][N] array for M*N+2 Points 
{
		
	float tix, tiy, tiz, tox,toy, toz;
	float theta, phi;

	int tempsp1, tempsp2;
	
	outer_points.clear();
	inner_points.clear();
	
	outer_faces.clear();
	inner_faces.clear();

	outer_springs.clear();
	inner_springs.clear();

	radium_springs.clear();
	shear_springs_left.clear();
	shear_springs_right.clear();

	double a;
	int nt=0/*, ntold*/;
	int i, j;
 /* float M=4;
  float N=4;
	for(i=0; i<M ; i++)		
//	for(i=0; i<numParticles ;i++)
  {// create NUMP points into 2D circle 
		for(j=0;j<N; j++)
//	for(j=0; j<numParticles ;j++)
	  {	
	


		tix = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*cos(j*(2.0*PI)/N);	// outer point X coordiation
		tiy = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*sin(j*(2.0*PI)/N);	// outer point Y coordiation
		tiz = 1*RING_RADIUS*sin(((i-M/2)*2.0*PI)/N);	// outer point Y coordiation

		tox = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*cos(j*(2.0*PI)/N);	// outer point X coordiation
		toy = 1*RING_RADIUS*cos(((i-M/2)*2.0*PI)/N)*sin(j*(2.0*PI)/N);	// outer point Y coordiation
		toz = 1*RING_RADIUS*sin(((i-M/2)*2.0*PI)/N);	// outer point Y coordiation


		cout<<"i---"<<i<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
			outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
				
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
	
	//	cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
		}
		
	
	}*/




	/////////////////////////////////////////////////////////
/*
float dtheta = 180/3;
float dphi = 360/3;
  	for(theta=-90; theta<=90-dtheta; theta+=dtheta)	
	{
//	for(i=0; i<numParticles ;i++)
  // create NUMP points into 2D circle 
		for(phi=0;phi<=360-dphi; phi+=dphi)
//	for(j=0; j<numParticles ;j++)
	  {	
	


		tix = 1*RING_RADIUS*cos(theta)*cos(phi);	// outer point X coordiation
		tiy = 1*RING_RADIUS*cos(theta)*sin(phi);	// outer point Y coordiation
		tiz = 1*RING_RADIUS*sin(theta);	// outer point Y coordiation

		tox = 1*RING_RADIUS*cos(theta)*cos(phi);
		toy = 1*RING_RADIUS*cos(theta)*sin(phi);	// outer point Y coordiation
		toz = 1*RING_RADIUS*sin(theta);	// outer point Y coordiation

		outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
				
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
	

		tix = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi);	// outer point X coordiation
		tiy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi);	// outer point Y coordiation
		tiz = 1*RING_RADIUS*sin(theta+dtheta);	// outer point Y coordiation

		tox = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi);
		toy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi);	// outer point Y coordiation
		toz = 1*RING_RADIUS*sin(theta+dtheta);	// outer point Y coordiation

		outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
				
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));

	
		tix = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi+dphi);	// outer point X coordiation
		tiy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi+dphi);	// outer point Y coordiation
		tiz = 1*RING_RADIUS*sin(theta+dtheta);	// outer point Y coordiation

		tox = 1*RING_RADIUS*cos(theta+dtheta)*cos(phi+dphi);
		toy = 1*RING_RADIUS*cos(theta+dtheta)*sin(phi+dphi);	// outer point Y coordiation
		toz = 1*RING_RADIUS*sin(theta+dtheta);	// outer point Y coordiation

		outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
				
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));


		if(theta>-90 && theta<90)
		{
		tix = 1*RING_RADIUS*cos(theta)*cos(phi+dphi);	// outer point X coordiation
		tiy = 1*RING_RADIUS*cos(theta)*sin(phi+dphi);	// outer point Y coordiation
		tiz = 1*RING_RADIUS*sin(theta);	// outer point Y coordiation

		tox = 1*RING_RADIUS*cos(theta)*cos(phi+dphi);
		toy = 1*RING_RADIUS*cos(theta)*sin(phi+dphi);	// outer point Y coordiation
		toz = 1*RING_RADIUS*sin(theta);	// outer point Y coordiation

		outer_points.push_back( new Particle(new Vector(tox, toy, toz), MASS));
				
		inner_points.push_back( new Particle(new Vector(tix, tiy, tiz), MASS));
		}

		//	cout<<"tox=="<<tox<<"==toy=="<<toy<<"==toz=="<<toz<<endl;
		}
		
	
	}*/



	outer_points.push_back( new Particle(new Vector(0,0,2*RING_RADIUS), MASS));
	outer_points.push_back( new Particle(new Vector(0,0,-2*RING_RADIUS), MASS));
	outer_points.push_back( new Particle(new Vector(-2*RING_RADIUS,-2*RING_RADIUS,0), MASS));
	outer_points.push_back( new Particle(new Vector(2*RING_RADIUS,-2*RING_RADIUS,0), MASS));
	outer_points.push_back( new Particle(new Vector(2*RING_RADIUS,2*RING_RADIUS,0), MASS));
	outer_points.push_back( new Particle(new Vector(-2*RING_RADIUS,2*RING_RADIUS,0), MASS));

	inner_points.push_back( new Particle(new Vector(0,0,RING_RADIUS), MASS));
	inner_points.push_back( new Particle(new Vector(0,0,-RING_RADIUS), MASS));
	inner_points.push_back( new Particle(new Vector(-RING_RADIUS,-RING_RADIUS,0), MASS));
	inner_points.push_back( new Particle(new Vector(RING_RADIUS,-RING_RADIUS,0), MASS));
	inner_points.push_back( new Particle(new Vector(RING_RADIUS,RING_RADIUS,0), MASS));
	inner_points.push_back( new Particle(new Vector(-RING_RADIUS,RING_RADIUS,0), MASS));

	this->numParticles = outer_points.size();
	



	a = 1 / sqrt(2.0);

	for (i=0;i<outer_points.size();i++)
	{
		outer_points[i]->r->x *= a;
		outer_points[i]->r->y *= a;
		outer_points[i]->r->z *= a;

		
		inner_points[i]->r->x *= a;
		inner_points[i]->r->y *= a;
		inner_points[i]->r->z *= a;

	}

	outer_faces.push_back(new Face(outer_points[0], outer_points[3], outer_points[4]));
	
	outer_springs.push_back(new Spring(outer_points[0], outer_points[3], KS,KD));     // row i with offset j
	outer_springs.push_back(new Spring(outer_points[3], outer_points[4], KS,KD));     // row i with offset j
	outer_springs.push_back(new Spring(outer_points[0], outer_points[4], KS,KD));     // row i with offset j


	outer_faces.push_back(new Face(outer_points[0], outer_points[4], outer_points[5]));

	outer_springs.push_back(new Spring(outer_points[0], outer_points[5], KS,KD));     // row i with offset j
	outer_springs.push_back(new Spring(outer_points[4], outer_points[5], KS,KD));     // row i with offset j


	outer_faces.push_back(new Face(outer_points[0], outer_points[5], outer_points[2]));

	outer_springs.push_back(new Spring(outer_points[0], outer_points[2], KS,KD));     // row i with offset j
	outer_springs.push_back(new Spring(outer_points[5], outer_points[2], KS,KD));     // row i with offset j
	
	
	outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3]));

	outer_springs.push_back(new Spring(outer_points[2], outer_points[3], KS,KD));     // row i with offset j

	
	outer_faces.push_back(new Face(outer_points[1], outer_points[4], outer_points[3]));

	outer_springs.push_back(new Spring(outer_points[1], outer_points[3], KS,KD));     // row i with offset j
	outer_springs.push_back(new Spring(outer_points[1], outer_points[4], KS,KD));     // row i with offset j

	
	outer_faces.push_back(new Face(outer_points[1], outer_points[5], outer_points[4]));
	
	outer_springs.push_back(new Spring(outer_points[1], outer_points[5], KS,KD));     // row i with offset j

	
	outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[5]));
	
	outer_springs.push_back(new Spring(outer_points[1], outer_points[2], KS,KD));     // row i with offset j


	outer_faces.push_back(new Face(outer_points[1], outer_points[3], outer_points[2]));


	//-----------------------------
///*
	inner_faces.push_back(new Face(inner_points[0], inner_points[3], inner_points[4]));
	
	inner_springs.push_back(new Spring(inner_points[0], inner_points[3], KS,KD));     // row i with offset j
	inner_springs.push_back(new Spring(inner_points[3], inner_points[4], KS,KD));     // row i with offset j
	inner_springs.push_back(new Spring(inner_points[0], inner_points[4], KS,KD));     // row i with offset j


	inner_faces.push_back(new Face(inner_points[0], inner_points[4], inner_points[5]));

	inner_springs.push_back(new Spring(inner_points[0], inner_points[5], KS,KD));     // row i with offset j
	inner_springs.push_back(new Spring(inner_points[4], inner_points[5], KS,KD));     // row i with offset j


	inner_faces.push_back(new Face(inner_points[0], inner_points[5], inner_points[2]));

	inner_springs.push_back(new Spring(inner_points[0], inner_points[2], KS,KD));     // row i with offset j
	inner_springs.push_back(new Spring(inner_points[5], inner_points[2], KS,KD));     // row i with offset j
	
	
	inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3]));

	inner_springs.push_back(new Spring(inner_points[2], inner_points[3], KS,KD));     // row i with offset j

	
	inner_faces.push_back(new Face(inner_points[1], inner_points[4], inner_points[3]));

	inner_springs.push_back(new Spring(inner_points[1], inner_points[3], KS,KD));     // row i with offset j
	inner_springs.push_back(new Spring(inner_points[1], inner_points[4], KS,KD));     // row i with offset j

	
	inner_faces.push_back(new Face(inner_points[1], inner_points[5], inner_points[4]));
	
	inner_springs.push_back(new Spring(inner_points[1], inner_points[5], KS,KD));     // row i with offset j

	
	inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[5]));
	
	inner_springs.push_back(new Spring(inner_points[1], inner_points[2], KS,KD));     // row i with offset j


	inner_faces.push_back(new Face(inner_points[1], inner_points[3], inner_points[2]));
//*/



	this->numSprings = this->outer_springs.size();



	Iteration();

	this->numParticles = this->outer_points.size();
	this->numSprings = this->outer_springs.size();

	cout<<"this->numParticles ==="<<this->numParticles<<"-----this->numSprings===="<<this->numSprings<<"-------this->numFaces===="<<this->outer_faces.size()<<endl;
	//	assert(false);
	for(i=0; i<numSprings ;i++)						//add the springs for outer & inner
	{  
		//Add_Structural_Spring(i,i,(i+1) % numParticles); 
	
	//	Add_Radium_Spring(i) ;
	//	Add_Shear_Spring(i);
		//Add_Faces(i, (i+1) % numParticles, (numParticles/2 + i) % numParticles) ;

	}

	
	
	for(i=0;i<inner_faces.size();i++)
	{
		inner_faces[i]->CalNormalNField();
		outer_faces[i]->CalNormalNField();
//		cout<<"outer_faces[i]->normal->x==="<<outer_faces[i]->normal->x<<"=== outer_faces[i]->normal->y==="<<outer_faces[i]->normal->y<<"===outer_faces[i]->normal->z===="<<outer_faces[i]->normal->z<<endl;
	}
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//================================================================================

void Object3D::Draw()
{		 
	static bool findOnce = false;

 	int i;
 //===============================================================================
	glPushMatrix();
	glColor4f(0,0,1,1);   // Blue color point distribution
	glBegin(GL_POINTS); // Draw points which built the Object3D
		glPointSize(10);
		  cout<<"Object3D size is : "<<outer_points.size()<<endl;
	    for(i=0; i<outer_points.size(); i++)
		{
	
		glVertex3f(outer_points[i]->r->x, outer_points[i]->r->y, outer_points[i]->r->z);	
			
	
		}

 	glEnd();

	glColor4f(0,0,0,1); 
	/*
	glBegin(GL_POINTS); // Draw inner points which built the Object3D
		glPointSize(10);
	    for(i=0; i<inner_points.size(); i++)
		{
		glVertex3f(inner_points[i]->r->x, inner_points[i]->r->y, inner_points[i]->r->z);		
		}
 	glEnd();		
	*/
	glPopMatrix();
//===================================================================================
 	
	
//	cout<<"Object3D spring size is : "<<outer_springs.size()<<endl;
	glPushMatrix();
	glColor4f(1,0,0,1);  
	glBegin(GL_LINES);
	for(i = 0; i<outer_springs.size();i++)
	{
		 glVertex3f(outer_springs[i]->sp1->r->x, outer_springs[i]->sp1->r->y, outer_springs[i]->sp1->r->z);
		 glVertex3f(outer_springs[i]->sp2->r->x, outer_springs[i]->sp2->r->y, outer_springs[i]->sp2->r->z);
		
	
	}
	glEnd();
	glPopMatrix();
///========================================draw inner structural springs==========================================
	/*
	glPushMatrix();
	glColor4f(1,0,0,1);  
	glBegin(GL_LINES);
	for(i = 0; i<inner_springs.size();i++)
	{
		 glVertex3f(inner_springs[i]->sp1->r->x, inner_springs[i]->sp1->r->y, inner_springs[i]->sp1->r->z);
		 glVertex3f(inner_springs[i]->sp2->r->x, inner_springs[i]->sp2->r->y, inner_springs[i]->sp2->r->z);
		
	
	}
	glEnd();
	glPopMatrix();
	  */
///========================================draw radium springs==========================================
/*	glPushMatrix();
		glBegin(GL_LINES);				// the draw of radium lines from inner to outer
			glLineWidth(10);
			for(i=0 ; i<radium_springs.size(); i++)
			{
				glColor3f(0.0,1.0,0.0);
				glVertex3f(radium_springs[i]->sp1->r->x, radium_springs[i]->sp1->r->y, radium_springs[i]->sp1->r->z);
				glVertex3f(radium_springs[i]->sp2->r->x, radium_springs[i]->sp2->r->y, radium_springs[i]->sp2->r->z);
			}
		glEnd();
	glPopMatrix();*/
	
///========================================draw shear left springs==========================================
/*	glPushMatrix();
		glBegin(GL_LINES);				// the left shear lines from inner to outer
			for(i=0 ; i<shear_springs_left.size(); i++)
			{
				glColor3f(1.0,1.0,0.0);
				glVertex3f(shear_springs_left[i]->sp1->r->x,shear_springs_left[i]->sp1->r->y, shear_springs_left[i]->sp1->r->z);
				glVertex3f(shear_springs_left[i]->sp2->r->x,shear_springs_left[i]->sp2->r->y, shear_springs_left[i]->sp2->r->z);
			}
		glEnd();
	glPopMatrix();*/

///========================================draw shear right springs==========================================

/*	glPushMatrix();
		glBegin(GL_LINES);				// the right shear lines from inner to outer
			for(i=0 ; i<shear_springs_right.size(); i++)
			{
				glColor3f(0.0,0.0,1.0);
				glVertex3f(shear_springs_right[i]->sp1->r->x,shear_springs_right[i]->sp1->r->y, shear_springs_right[i]->sp1->r->z);
				glVertex3f(shear_springs_right[i]->sp2->r->x,shear_springs_right[i]->sp2->r->y, shear_springs_right[i]->sp2->r->z);
			}
		glEnd();
	glPopMatrix();*/



//=======================================================================================
/////----------------------------------------- Draw outer faces ----------------------------------------------
	glPushMatrix();
	/*	glBegin(GL_TRIANGLES);  	  
			for(i=0; i<inner_faces.size(); i++)
			{
				glColor4f(1.0,1.0,1.0,.5);     	    // Yellow color face distribution
				//     glNormal3f(inner_faces[i]->normal->x,inner_faces[i]->normal->y,inner_faces[i]->normal->z);
				glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
				glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
				glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);

			}
		glEnd();
/////----------------------------------------- Draw outer faces normals----------------------------------------------

/*		glBegin(GL_LINES);
			for(i=0 ; i<inner_faces.size(); i++)
			{
				glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
			
				glVertex3f((inner_faces[i]->normal->x + inner_faces[i]->fp1->r->x),
						   (inner_faces[i]->normal->y + inner_faces[i]->fp1->r->y),
						   (inner_faces[i]->normal->z + inner_faces[i]->fp1->r->z));
			}
		glEnd();*/

	glPopMatrix();


/////----------------------------------------- Draw outer faces ----------------------------------------------
 
 	glPushMatrix();
		glBegin(GL_TRIANGLES);  	  
			for(i=0; i<outer_faces.size(); i++)
			{
				glColor4f(1.0,1.0,1.0,.5);     	    // Yellow color face distribution
				//     glNormal3f(outer_faces[i]->normal->x,outer_faces[i]->normal->y,outer_faces[i]->normal->z);
				glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
				glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
				glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);

			}
		glEnd();
/////----------------------------------------- Draw outer faces normals----------------------------------------------


/*		glBegin(GL_LINES);
			for(i=0 ; i<outer_faces.size(); i++)
			{
				glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
			
				glVertex3f((outer_faces[i]->normal->x + outer_faces[i]->fp1->r->x),
						   (outer_faces[i]->normal->y + outer_faces[i]->fp1->r->y),
						   (outer_faces[i]->normal->z + outer_faces[i]->fp1->r->z));
			}
		glEnd();
	*/
	glPopMatrix();
//---------------------------------------------------------------------------------------

	if(integrator->dragExists)
	{
		if(findOnce == true)
		{
			FindClosestPoint();
			findOnce = false;
		}

		glColor3f(1,1,0);      // A white line between the Object3D point and the mouse point
		glBegin(GL_LINES);	
		glVertex2f(integrator->mDragX, integrator->mDragY);
		glVertex3f(outer_points[closest_i]->r->x,outer_points[closest_i]->r->y,outer_points[closest_i]->r->z);
		glEnd();
	}      
	else
	{
		FindClosestPoint();
		findOnce = true;
	}

}

