#include "Object3D.h"

#include <assert.h>

Object3D::Object3D() 
{	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*	pa = new Particle(new Vector(0,0,0), MASS);
	pb = new Particle(new Vector(0,0,0), MASS);
	pc = new Particle(new Vector(0,0,0), MASS);
*/
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


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





//==============================================================================
void Object3D::Iteration()
{
	// Spring triplets counter for older springs particle replacements
//	static int j = 0;

	for (int it=0; it<iterations;it++)
	{
		int initialFacesCount = outer_faces.size();
		int i;

		for(i=0;i<initialFacesCount;i++)
		{

			// Here we subdivide the initial face into four faces by
			pa = new Particle();
			pb = new Particle();
			pc = new Particle();


			// first getting the midpoints on each edge of the original face

			pa->r->x=(outer_faces[i]->fp1->r->x + outer_faces[i]->fp2->r->x)/2;
			pa->r->y=(outer_faces[i]->fp1->r->y + outer_faces[i]->fp2->r->y)/2;
			pa->r->z=(outer_faces[i]->fp1->r->z + outer_faces[i]->fp2->r->z)/2;

			pb->r->x=(outer_faces[i]->fp2->r->x + outer_faces[i]->fp3->r->x)/2;
			pb->r->y=(outer_faces[i]->fp2->r->y + outer_faces[i]->fp3->r->y)/2;
			pb->r->z=(outer_faces[i]->fp2->r->z + outer_faces[i]->fp3->r->z)/2;

			pc->r->x=(outer_faces[i]->fp1->r->x + outer_faces[i]->fp3->r->x)/2;
			pc->r->y=(outer_faces[i]->fp1->r->y + outer_faces[i]->fp3->r->y)/2;
			pc->r->z=(outer_faces[i]->fp1->r->z + outer_faces[i]->fp3->r->z)/2;
			//

	/*		 cout<<"before normalization: "<<endl;
			  cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
		   //

*/
		 

		  

			// Each new point's coordinates are normalized
			pa->r->Normalize();
			pb->r->Normalize();
			pc->r->Normalize();

	/*		 cout<<"after normalization: "<<endl;

		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;

*/

			bool a = false, b = false, c = false;
			for(int o = 0; o < outer_points.size(); o++)
			{
				if
				(
					   outer_points[o]->r->x == pa->r->x
					&& outer_points[o]->r->y == pa->r->y
					&& outer_points[o]->r->z == pa->r->z
				)
				{
					delete pa;
					pa = outer_points[o];
					a = true;
				}

				if
				(
					   outer_points[o]->r->x == pb->r->x
					&& outer_points[o]->r->y == pb->r->y
					&& outer_points[o]->r->z == pb->r->z
				)
				{
					delete pb;
					pb = outer_points[o];
					b = true;
				}

				if
				(
					   outer_points[o]->r->x == pc->r->x
					&& outer_points[o]->r->y == pc->r->y
					&& outer_points[o]->r->z == pc->r->z
				)
				{
					delete pc;
					pc = outer_points[o];
					c = true;
				}
			}

			// The new points are added to the general collection of points
			if(!a) outer_points.push_back(pa); 
			if(!b) outer_points.push_back(pb); 
			if(!c) outer_points.push_back(pc); 


			// Create three new faces; these represent the three outer triangles
			outer_faces.push_back(new Face(outer_faces[i]->fp1, pa, pc, outer_springs)); // Top
			outer_faces.push_back(new Face(pa, outer_faces[i]->fp2, pb, outer_springs)); // Bottom-left
//			outer_faces.push_back(new Face(pb, outer_faces[i]->fp3, pc, outer_springs)); // Bottom-right
			outer_faces.push_back(new Face(pc, pb, outer_faces[i]->fp3, outer_springs)); // Bottom-right


			// Replace the original face's points with its new one in the middle

			outer_faces[i]->fp1 = pa;
			outer_faces[i]->fp2 = pb;
			outer_faces[i]->fp3 = pc;


			outer_faces[i]->fs1->sp1 = pa;
			outer_faces[i]->fs1->sp2 = pb;

			outer_faces[i]->fs2->sp1 = pb;
			outer_faces[i]->fs2->sp2 = pc;

			outer_faces[i]->fs3->sp1 = pc;
			outer_faces[i]->fs3->sp2 = pa;
		}

		initialFacesCount = inner_faces.size();

	 for(i=0;i<initialFacesCount;i++)
		{

			// Here we subdivide the initial face into four faces by
			pa = new Particle();
			pb = new Particle();
			pc = new Particle();


			// first getting the midpoints on each edge of the original face

			pa->r->x=(inner_faces[i]->fp1->r->x + inner_faces[i]->fp2->r->x)/2;
			pa->r->y=(inner_faces[i]->fp1->r->y + inner_faces[i]->fp2->r->y)/2;
			pa->r->z=(inner_faces[i]->fp1->r->z + inner_faces[i]->fp2->r->z)/2;

			pb->r->x=(inner_faces[i]->fp2->r->x + inner_faces[i]->fp3->r->x)/2;
			pb->r->y=(inner_faces[i]->fp2->r->y + inner_faces[i]->fp3->r->y)/2;
			pb->r->z=(inner_faces[i]->fp2->r->z + inner_faces[i]->fp3->r->z)/2;

			pc->r->x=(inner_faces[i]->fp1->r->x + inner_faces[i]->fp3->r->x)/2;
			pc->r->y=(inner_faces[i]->fp1->r->y + inner_faces[i]->fp3->r->y)/2;
			pc->r->z=(inner_faces[i]->fp1->r->z + inner_faces[i]->fp3->r->z)/2;
			//

			 cout<<"inner iteration before normalization: "<<endl;
			  cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;
		   //


		 

		  

			// Each new point's coordinates are normalized
			pa->r->Normalize();
			pb->r->Normalize();
			pc->r->Normalize();

			 cout<<"inner iteration after normalization: "<<endl;

		   cout<<"pa->x="<<pa->r->x<<"; pa->y="<<pa->r->y<<"; pa->z="<<pa->r->z<<endl;
		   cout<<"pb->x="<<pb->r->x<<"; pb->y="<<pb->r->y<<"; pb->z="<<pb->r->z<<endl;
		   cout<<"pc->x="<<pc->r->x<<"; pc->y="<<pc->r->y<<"; pc->z="<<pc->r->z<<endl;



			bool a = false, b = false, c = false;
			for(int o = 0; o < inner_points.size(); o++)
			{
				if
				(
					   inner_points[o]->r->x == pa->r->x
					&& inner_points[o]->r->y == pa->r->y
					&& inner_points[o]->r->z == pa->r->z
				)
				{
					delete pa;
					pa = inner_points[o];
					a = true;
				}

				if
				(
					   inner_points[o]->r->x == pb->r->x
					&& inner_points[o]->r->y == pb->r->y
					&& inner_points[o]->r->z == pb->r->z
				)
				{
					delete pb;
					pb = inner_points[o];
					b = true;
				}

				if
				(
					   inner_points[o]->r->x == pc->r->x
					&& inner_points[o]->r->y == pc->r->y
					&& inner_points[o]->r->z == pc->r->z
				)
				{
					delete pc;
					pc = inner_points[o];
					c = true;
				}
			}

			// The new points are added to the general collection of points
			if(!a) inner_points.push_back(pa); 
			if(!b) inner_points.push_back(pb); 
			if(!c) inner_points.push_back(pc); 


			// Create three new faces; these represent the three inner triangles
			inner_faces.push_back(new Face(inner_faces[i]->fp1, pa, pc, inner_springs)); // Top
			inner_faces.push_back(new Face(pa, inner_faces[i]->fp2, pb, inner_springs)); // Bottom-left
//			inner_faces.push_back(new Face(pb, inner_faces[i]->fp3, pc, inner_springs)); // Bottom-right
			inner_faces.push_back(new Face(pc, pb, inner_faces[i]->fp3, inner_springs)); // Bottom-right


			// Replace the original face's points with its new one in the middle

			inner_faces[i]->fp1 = pa;
			inner_faces[i]->fp2 = pb;
			inner_faces[i]->fp3 = pc;


			inner_faces[i]->fs1->sp1 = pa;
			inner_faces[i]->fs1->sp2 = pb;

			inner_faces[i]->fs2->sp1 = pb;
			inner_faces[i]->fs2->sp2 = pc;

			inner_faces[i]->fs3->sp1 = pc;
			inner_faces[i]->fs3->sp2 = pa;
		}





	}


	int i;
for(i=0; i<inner_points.size();i++)
cout<<"inner_points"<<i<<"----="<<inner_points[i]->r->x<<";"<<inner_points[i]->r->y<<";"<<inner_points[i]->r->z<<endl;

for(i=0; i<inner_faces.size();i++)
{
cout<<"inner_faces fp1: "<<i<<"----="<<inner_faces[i]->fp1->r->x<<";"<<inner_faces[i]->fp1->r->y<<";"<<inner_faces[i]->fp1->r->z<<endl;
cout<<"inner_faces fp2: "<<i<<"----="<<inner_faces[i]->fp2->r->x<<";"<<inner_faces[i]->fp2->r->y<<";"<<inner_faces[i]->fp2->r->z<<endl;
cout<<"inner_faces fp3: "<<i<<"----="<<inner_faces[i]->fp3->r->x<<";"<<inner_faces[i]->fp3->r->y<<";"<<inner_faces[i]->fp3->r->z<<endl;
}

}



void Object3D::nonunitsphere()
{

	float tix, tiy, tiz, tox,toy, toz;
	float theta, phi;


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
		
	
	}



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


}

///////////////==================================================================
void Object3D::SetObject(void) // [M+2][N] array for M*N+2 Points 
{
		
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
 
	/////////////////////////////////////////////////////////

//	Pyramid3();

//	Pyramid4();

	Tetrahedron();

	cout<<"outer_spring size ======="<<outer_springs.size()<<endl;
	Iteration();
		cout<<"interation after outer_spring size ======="<<outer_springs.size()<<endl;

	this->numParticles = this->outer_points.size();
	this->numSprings = this->outer_springs.size();

	cout<<"this->numParticles ==="<<this->numParticles<<"-----this->numSprings===="<<this->numSprings<<"-------this->numFaces===="<<this->outer_faces.size()<<endl;
	//	assert(false);
	for(i=0; i<numSprings ;i++)						//add the springs for outer & inner
	{  
		//Add_Structural_Spring(i,i,(i+1) % numParticles); 
	
		Add_Radium_Spring(i) ;
		Add_Shear_Spring(i);
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


void Object3D::Tetrahedron()
{

	double a;
	int i;

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
	//	outer_points[i]->r->z *= a;
		
		inner_points[i]->r->x *= a;
		inner_points[i]->r->y *= a;
	//	inner_points[i]->r->z *= a;
	}


	outer_faces.push_back(new Face(outer_points[0], outer_points[3], outer_points[4], outer_springs));
	outer_faces.push_back(new Face(outer_points[0], outer_points[4], outer_points[5], outer_springs));
	outer_faces.push_back(new Face(outer_points[0], outer_points[5], outer_points[2], outer_springs));
	outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3], outer_springs));
	outer_faces.push_back(new Face(outer_points[1], outer_points[4], outer_points[3], outer_springs));
	outer_faces.push_back(new Face(outer_points[1], outer_points[5], outer_points[4], outer_springs));
	outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[5], outer_springs));
	outer_faces.push_back(new Face(outer_points[1], outer_points[3], outer_points[2], outer_springs));


	inner_faces.push_back(new Face(inner_points[0], inner_points[3], inner_points[4], inner_springs));
	inner_faces.push_back(new Face(inner_points[0], inner_points[4], inner_points[5], inner_springs));
	inner_faces.push_back(new Face(inner_points[0], inner_points[5], inner_points[2], inner_springs));
	inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3], inner_springs));
	inner_faces.push_back(new Face(inner_points[1], inner_points[4], inner_points[3], inner_springs));
	inner_faces.push_back(new Face(inner_points[1], inner_points[5], inner_points[4], inner_springs));
	inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[5], inner_springs));
	inner_faces.push_back(new Face(inner_points[1], inner_points[3], inner_points[2], inner_springs));


	this->numSprings = this->outer_springs.size();

}


void Object3D::Pyramid3()
{

	double a;

	int i;


	outer_points.push_back( new Particle(new Vector(-2 * RING_RADIUS, 0,  2 * RING_RADIUS), MASS));
	outer_points.push_back( new Particle(new Vector(-2 * RING_RADIUS, 0, -2 * RING_RADIUS), MASS));
	outer_points.push_back( new Particle(new Vector( 2 * RING_RADIUS, 0, 0), MASS));
	outer_points.push_back( new Particle(new Vector( 0, 2 * RING_RADIUS,0), MASS));

	// XXX: must match above
	inner_points.push_back( new Particle(new Vector(0,0,RING_RADIUS), MASS));
	inner_points.push_back( new Particle(new Vector(0,0,-RING_RADIUS), MASS));
	inner_points.push_back( new Particle(new Vector(-RING_RADIUS,-RING_RADIUS,0), MASS));
	inner_points.push_back( new Particle(new Vector(RING_RADIUS,-RING_RADIUS,0), MASS));


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


	// Bottom face
	outer_faces.push_back(new Face(outer_points[0], outer_points[1], outer_points[2], outer_springs));

	// Left face
	outer_faces.push_back(new Face(outer_points[0], outer_points[1], outer_points[3], outer_springs));


	// Front face
	outer_faces.push_back(new Face(outer_points[0], outer_points[2], outer_points[3], outer_springs));

	// Back face
	outer_faces.push_back(new Face(outer_points[1], outer_points[2], outer_points[3], outer_springs));


	//-----------------------------

///*

	inner_faces.push_back(new Face(inner_points[0], inner_points[1], inner_points[2], inner_springs));

	// Left face
	inner_faces.push_back(new Face(inner_points[0], inner_points[1], inner_points[3], inner_springs));

	// Front face
	inner_faces.push_back(new Face(inner_points[0], inner_points[2], inner_points[3], inner_springs));

	// Back face
	inner_faces.push_back(new Face(inner_points[1], inner_points[2], inner_points[3], inner_springs));

//*/



	this->numSprings = this->outer_springs.size();
}


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
	    for(i=0; i<outer_points.size(); i++)
		{
		glVertex3f(outer_points[i]->r->x, outer_points[i]->r->y, outer_points[i]->r->z);	
		}

 	glEnd();

	glColor4f(0,0,0,1); 
	
/*	glBegin(GL_POINTS); // Draw inner points which built the Object3D
		glPointSize(10);
	    for(i=0; i<inner_points.size(); i++)
		{
		glVertex3f(inner_points[i]->r->x, inner_points[i]->r->y, inner_points[i]->r->z);		
		}
 	glEnd();		*/
	
	glPopMatrix();
//===================================================================================
 	
	
//	cout<<"Object3D spring size is : "<<outer_springs.size()<<endl;
/*
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
	//*/
///========================================draw inner structural springs==========================================
	
/*	glPushMatrix();
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
	glPushMatrix();
		glBegin(GL_LINES);				// the draw of radium lines from inner to outer
			glLineWidth(10);
			for(i=0 ; i<radium_springs.size(); i++)
			{
				glColor3f(0.0,1.0,0.0);
				glVertex3f(radium_springs[i]->sp1->r->x, radium_springs[i]->sp1->r->y, radium_springs[i]->sp1->r->z);
				glVertex3f(radium_springs[i]->sp2->r->x, radium_springs[i]->sp2->r->y, radium_springs[i]->sp2->r->z);
			}
		glEnd();
	glPopMatrix();
	
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
/////----------------------------------------- Draw inner faces ----------------------------------------------
//	cout<<"inner_faces.size()???????????????"<<inner_faces.size()<<endl;
	glPushMatrix();
	glBegin(GL_TRIANGLES);  	  
			for(i=0; i<inner_faces.size(); i++)
			{
				glColor4f(1.0,1.0,1.0,.5);     	    // Yellow color face distribution
		 //     glNormal3f(inner_faces[i]->normal->x,inner_faces[i]->normal->y,inner_faces[i]->normal->z);
				glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
				glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
				glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);

			}
		glEnd();
/////----------------------------------------- Draw inner faces normals----------------------------------------------

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
			//	break;
				glColor4f(1.0,1.0,1.0,.5);     	    // Yellow color face distribution
				//     glNormal3f(outer_faces[i]->normal->x,outer_faces[i]->normal->y,outer_faces[i]->normal->z);
				glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
				glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
				glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);

			}
		glEnd();
/////----------------------------------------- Draw outer faces normals----------------------------------------------


		glColor3f(1,0,0);
		glBegin(GL_LINES);
			for(i=0 ; i<outer_faces.size(); i++)
			{
				glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
				glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);

				glVertex3f(outer_faces[i]->fp2->r->x, outer_faces[i]->fp2->r->y, outer_faces[i]->fp2->r->z);
				glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);

				glVertex3f(outer_faces[i]->fp3->r->x, outer_faces[i]->fp3->r->y, outer_faces[i]->fp3->r->z);
				glVertex3f(outer_faces[i]->fp1->r->x, outer_faces[i]->fp1->r->y, outer_faces[i]->fp1->r->z);
			
//				glVertex3f((outer_faces[i]->normal->x + outer_faces[i]->fp1->r->x),
//						   (outer_faces[i]->normal->y + outer_faces[i]->fp1->r->y),
//						   (outer_faces[i]->normal->z + outer_faces[i]->fp1->r->z));


				glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
				glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);

				glVertex3f(inner_faces[i]->fp2->r->x, inner_faces[i]->fp2->r->y, inner_faces[i]->fp2->r->z);
				glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);

				glVertex3f(inner_faces[i]->fp3->r->x, inner_faces[i]->fp3->r->y, inner_faces[i]->fp3->r->z);
				glVertex3f(inner_faces[i]->fp1->r->x, inner_faces[i]->fp1->r->y, inner_faces[i]->fp1->r->z);
			}
		glEnd();
	
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

