#include "Integrator.h"
#include "Object2D.h"
#include <assert.h>
#include <vector>


//////////////// integrator constructor///////////////////////////////////////////////////////
//##ModelId=45F4D797039C
Integrator::Integrator(Object& objectToIntegrate) : dragExists(false)
{
	this->object = &objectToIntegrate;
	for(int j=0; j<objectToIntegrate.outer_points.size(); j++)
	{
		// temp outer vector<Particle*> container for integrator computation
		temp_outer_points0.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points1.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points2.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points3.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points4.push_back(new Particle (*this->object->outer_points[j]));

		// temp inner vector<Particle*> container for integrator computation
		temp_inner_points0.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points1.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points2.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points3.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points4.push_back(new Particle (*this->object->inner_points[j]));
	}
	dim = DIM1D;			// default object is 1D
}

//////////////// integrator destructor///////////////////////////////////////////////////////

//##ModelId=45F4D79703AB
Integrator::~Integrator()
{
	temp_outer_points0.clear();	// clear up the vector and free the memory
	temp_outer_points1.clear();
	temp_outer_points2.clear();
	temp_outer_points3.clear();
	temp_outer_points4.clear();

	temp_inner_points0.clear();
	temp_inner_points1.clear();
	temp_inner_points2.clear();
	temp_inner_points3.clear();
	temp_inner_points4.clear();
}

/////the calculation of the integration with/without external dragging force//////////////////
//##ModelId=45F4D79703AD
void Integrator::integrate(float deltaT, bool drag, float xDrag, float yDrag)
{
	dragExists = drag;			// if the mouse drag exist
	mDragX = xDrag;				// the mouse position x axis
	mDragY = yDrag;				// the mouse position y axis
	AccumulateForces();    			// accumulate all forces 
	Derivatives(deltaT, 1.0);		// compute the derivatives
}

//////////////////////// accumulate all forces ////////////////////////////////////////////////
//##ModelId=45F4D79703DA
void Integrator::AccumulateForces()   // accumulate forces acted on 
{
	ExternalForces();			  // accumulate gravity and dragging force
	SpringForces();	

	switch(dim)				  // there is addition pressure force for 2D&3D
	{
		case DIM1D:
			break;

		
		case DIM2D:			 // Pressure forces are applicable on 2D
		case DIM3D:			 // Pressure forces are applicable on 3D
			PressureForces();
			break;
	}
}

////////////////////// accumulate gravity and dragging force////////////////////////////////////////
//##ModelId=45F4D79703CA
void Integrator::ExternalForces()
{
	int i;    										// runing index
	float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2;	// points p1, p2 on the outer layer
  	float outer_rd12;			            				// distance between p1, p2
	float outer_Fx,outer_Fy,outer_Fz;		            		// force vector for outer layer
	float f;				        					// accumulated force 

	for(i = 0; i < object->GetNumberOfParticles(); i++)			// contribute gravity force
	{
		switch(dim)
		{
		case DIM2D:
		// for the inner layer
		object->inner_points[i]->f->x = 0;//80*sin(90*i);		// initial force on x axis
		object->inner_points[i]->f->y = 2.5* MASS * GY;     			// set the gravity along y axix
		object->inner_points[i]->f->z = 0; 					// set to 0    
		break;
		case DIM3D:
		// for the inner layer
		object->inner_points[i]->f->x = 0;//80*sin(90*i);		// initial force on x axis
		object->inner_points[i]->f->y = MASS * GY;     			// set the gravity along y axix
		object->inner_points[i]->f->z = 0; 					// set to 0    
		break;
		}
		// for the outer layer
		object->outer_points[i]->f->x = 0;//80* cos(25*i);		// initial force on x axis
	/*	if (i==1) 
		object->outer_points[i]->f->y = 0;//MASS * GY;			// set the gravity along y axix
		else
	*/	object->outer_points[i]->f->y = MASS * GY;			// set the gravity along y axix
		object->outer_points[i]->f->z = 0;					// set to 0    
		
		if(i == object->closest_i)						// if is the nearest particle to mouse 
		{
			if(dragExists)							// if user clicked
			{
				outer_x1 = object->outer_points[ i ]->r->x;	// get points X-coord
				outer_y1 = object->outer_points[ i ]->r->y;     // get points Y-coord
				outer_z1 = object->outer_points[ i ]->r->z;     // get points Z-coord

				outer_x2 = mDragX;                      		// get Mouse  X-coord
				outer_y2 = mDragY;                      		// get Mouse  Y-coord
				outer_z2 = 0;                      			// set Mouse  Z-coord

				outer_rd12 =						// the distance nearest/mouse
				sqrt((outer_x1-outer_x2) * (outer_x1-outer_x2)
				    +(outer_y1-outer_y2) * (outer_y1-outer_y2)
				    +(outer_z1-outer_z2) * (outer_z1-outer_z2)
					); 

				f = (outer_rd12 - MOUSE_REST) * MOUSE_KS		// the dragging force calculation
				  + (
				object->outer_points[i]->v->x * (outer_x1-outer_x2)
			    + object->outer_points[i]->v->y * (outer_y1-outer_y2)
			    + object->outer_points[i]->v->z * (outer_z1-outer_z2)
			    ) * MOUSE_KD / outer_rd12;

				// calculate spring force vector and its direction
				outer_Fx = ((outer_x1 - outer_x2) / outer_rd12) * f;
				outer_Fy = ((outer_y1 - outer_y2) / outer_rd12) * f;
				outer_Fz = ((outer_z1 - outer_z2) / outer_rd12) * f;

				// contribute the dragging forces to the dragged point
				object->outer_points[i]->f->x -= outer_Fx; 
				object->outer_points[i]->f->y -= outer_Fy;
				object->outer_points[i]->f->z -= outer_Fz;
			}
		}
	}
}

/////// general spring calculation function //////////////////////////////////////////////////
//##ModelId=45F4D79703CC
void Integrator::SpringForces()
{
	int i;    // runing index

	// Three parts for computing the spring forces on all the points
	for(i = 0; i<object->GetNumberOfSprings(); i++)  			
	{

		// Part #1 outer structual spring force contribution
		// exist for 1D, 2D outer structual, and 3D outer structual 
		CalculateSpringForces(object->outer_springs, i);	

		switch(dim)
		{
			case DIM1D:		// intentionally empty, no more other type of springs
			break;

			case DIM2D:      // for 2D include the following additional springs
			case DIM3D:	     // for 3D include the following additional springs

			{	
				// Part #2 inner structual spring force contribution
				CalculateSpringForces
				(
					((Object2D*)object)->inner_springs,
					i
				);

				// Part #3 radium spring contribution
				CalculateSpringForces
				(
					((Object2D*)object)->radium_springs,
					i,
					false
				);

				// Part #4 shear left spring contribution
				CalculateSpringForces				
				(
					((Object2D*)object)->shear_springs_left,
					i
				);

				// Part #5 shear right spring contribution
				CalculateSpringForces				
				(
					((Object2D*)object)->shear_springs_right,
					i
				);
				break;
			}
		}
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//##ModelId=45F4D7980004
void Integrator::CalculateSpringForces(vector<Spring *>springs, int i, bool special)
{
	float vx12, vy12, vz12;
	float Fx, Fy, Fz;
	float f;

	float x1 = springs[i]->sp1->r->x;		// tha head particle of the spring
	float y1 = springs[i]->sp1->r->y;
	float z1 = springs[i]->sp1->r->z;

	float x2 = springs[i]->sp2->r->x;		// the tail particle of the spring
	float y2 = springs[i]->sp2->r->y;
	float z2 = springs[i]->sp2->r->z;

	// the length of the spring
	float rd12 = (*springs[i]->sp1->r - *springs[i]->sp2->r).getLength();

	if(rd12 == 0)
	{
		return;
	}

	// Calculate normal vectors to springs 

	if(special)				////??????????????????????????
		dim = DIM2D;

	switch(dim)
	{
		case DIM1D:
		case DIM2D:
			springs[i]->normal.x = -(y1 - y2) / rd12;  	// Normal X-vector
			springs[i]->normal.y = +(x1 - x2) / rd12;  	// Normal Y-vector 
			springs[i]->normal.z = 0;  				// Normal Z-vector 
			break;

		case DIM3D:
			springs[i]->normal.x = -(x1 - x2) / rd12; 	// Normal X-vector
			springs[i]->normal.y = +(z1 - z2) / rd12;  	// Normal Y-vector 
			springs[i]->normal.z = +(y1 - y2) / rd12;  	// Normal Z-vector 
			break;
	}

	// velocity vector of the two ends of the spring
	vx12 = springs[i]->sp1->v->x - springs[i]->sp2->v->x;		
	vy12 = springs[i]->sp1->v->y - springs[i]->sp2->v->y;
	vz12 = springs[i]->sp1->v->z - springs[i]->sp2->v->z;

	// hook spring force of its damping force
	f = (rd12 - springs[i]->restLen) * KS
	  + (vx12 * (x1 - x2)
	  +  vy12 * (y1 - y2)
	  +  vz12 * (z1 - z2)) * KD / rd12;
	
	// spring vector on x, y, z axix
	Fx = ((x1 - x2) / rd12) * f;
	Fy = ((y1 - y2) / rd12) * f;
	Fz = ((z1 - z2) / rd12) * f;

	// accumulate the force on the start partilce of the spring
	springs[i]->sp1->f->x -= Fx;
	springs[i]->sp1->f->y -= Fy;
	springs[i]->sp1->f->z -= Fz;
	// accumulate the force on the end partilce of the spring
	springs[i]->sp2->f->x += Fx;
	springs[i]->sp2->f->y += Fy;
	springs[i]->sp2->f->z += Fz;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

//##ModelId=45F4D79703CE
void Integrator::PressureForces()
{
	int i;    										// runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2,inner_z1,inner_z2;	// points p1, p2 on the inner layer
    	float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2;	// points p1, p2 on the outer layer

	float inner_rd12;			            				// distance of innter p1, p2
	float outer_rd12;			            				// distance of outer p1, p2

	float inner_volume=0.0;          						// inner circle inner_volume
	float outer_volume=0.0;		    						// outer circle outer_volume 

	float inner_p_accu;               						// inner pressure force accumulation 
	float outer_p_accu;         	    						// outer pressure force accumulation


	// pressure force for the inner and outer circles
	
	for(i=0; i<object->GetNumberOfSprings(); i++) 				// for every spring on the object		
	{
            inner_x1 = object->inner_springs[i]->sp1->r->x;			// inner spring start particle 
		inner_y1 = object->inner_springs[i]->sp1->r->y;
		inner_z1 = object->inner_springs[i]->sp1->r->z;

		inner_x2 = object->inner_springs[i]->sp2->r->x;			// inner spring end particle 
		inner_y2 = object->inner_springs[i]->sp2->r->y;
		inner_z2 = object->inner_springs[i]->sp2->r->z;

		inner_rd12 =								// need the inner spring length for volume
			sqrt(
			    (inner_x1-inner_x2)*(inner_x1-inner_x2)
			   +(inner_y1-inner_y2)*(inner_y1-inner_y2)
			   +(inner_z1-inner_z2)*(inner_z1-inner_z2)
			   );

		// based on the Gauss Theorem??????????????????????????????// calculation of inner circle volume
		inner_volume += 40.5 *
			fabs(inner_x1 - inner_x2) *
			(
			fabs(object->inner_springs[i]->normal.x)
			+fabs(object->inner_springs[i]->normal.y)
			+fabs(object->inner_springs[i]->normal.z)
			) * 
			(inner_rd12);
	
		outer_x1 = object->outer_springs[i]->sp1->r->x;			// outer spring start particle 
		outer_y1 = object->outer_springs[i]->sp1->r->y;
		outer_z1 = object->outer_springs[i]->sp1->r->z;

		outer_x2 = object->outer_springs[i]->sp2->r->x;			// outer spring end particle 
		outer_y2 = object->outer_springs[i]->sp2->r->y;
		outer_z2 = object->outer_springs[i]->sp2->r->z;

		outer_rd12 = 								// need the outer spring length for volume
			sqrt(
				(outer_x1-outer_x2)*(outer_x1-outer_x2)
			   +(outer_y1-outer_y2)*(outer_y1-outer_y2)
			   +(outer_z1-outer_z2)*(outer_z1-outer_z2)
			   );	

		outer_volume +=	40.5 * 						// calculation of outer layer volume
			fabs(outer_x1 - outer_x2) * 
//			fabs(outer_y1 - outer_y2) * 
//			fabs(outer_z1 - outer_z2) * 
			(
			fabs(object->outer_springs[i]->normal.x)
			+fabs(object->outer_springs[i]->normal.y)
			+fabs(object->outer_springs[i]->normal.z)
			) * 
			(outer_rd12);	
	} 

	// calculation inner and outer layer pressure force 
	for(i=0; i<object->GetNumberOfSprings(); i++)  				
	{
        	inner_x1 = object->inner_springs[i]->sp1->r->x;			
		inner_y1 = object->inner_springs[i]->sp1->r->y;
		inner_z1 = object->inner_springs[i]->sp1->r->z;

		inner_x2 = object->inner_springs[i]->sp2->r->x;	
		inner_y2 = object->inner_springs[i]->sp2->r->y;
		inner_z2 = object->inner_springs[i]->sp2->r->z;

		inner_rd12=sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2) 
		+  (inner_y1-inner_y2)*(inner_y1-inner_y2)
		+  (inner_z1-inner_z2)*(inner_z1-inner_z2)
		);	

		inner_p_accu = inner_rd12 * ((Object2D*)object)->getPressure() * (1.0f / inner_volume);
		
		// contribute inner pressure to the start particle on this spring 
		object->inner_springs[i]->sp1->f->x += object->inner_springs[i]->normal.x*inner_p_accu;
		object->inner_springs[i]->sp1->f->y += object->inner_springs[i]->normal.y*inner_p_accu;
		object->inner_springs[i]->sp1->f->z += object->inner_springs[i]->normal.z*inner_p_accu;

		// contribute inner pressure to the end particle on this spring
		object->inner_springs[i]->sp2->f->x += object->inner_springs[i]->normal.x*inner_p_accu;
		object->inner_springs[i]->sp2->f->y += object->inner_springs[i]->normal.y*inner_p_accu;
		object->inner_springs[i]->sp2->f->z += object->inner_springs[i]->normal.z*inner_p_accu;

		////////////////////////////////////////////
		outer_x1 = object->outer_springs[i]->sp1->r->x;
		outer_y1 = object->outer_springs[i]->sp1->r->y;
		outer_z1 = object->outer_springs[i]->sp1->r->z;

		outer_x2 = object->outer_springs[i]->sp2->r->x;	
		outer_y2 = object->outer_springs[i]->sp2->r->y;
		outer_z2 = object->outer_springs[i]->sp2->r->z;

		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2) 
		+  (outer_y1-outer_y2)*(outer_y1-outer_y2)
		+  (outer_z1-outer_z2)*(outer_z1-outer_z2)
		);	
													

		outer_p_accu = outer_rd12 * ((Object2D*)object)->getPressure() * (1.0f / outer_volume);
	
		// contribute outer pressure to the start particle on this spring
		object->outer_springs[i]->sp1->f->x += object->outer_springs[i]->normal.x * outer_p_accu;
		object->outer_springs[i]->sp1->f->y += object->outer_springs[i]->normal.y * outer_p_accu;
		object->outer_springs[i]->sp1->f->z += object->outer_springs[i]->normal.z * outer_p_accu;
		
		// contribute outer pressure to the end particle on this spring
		object->outer_springs[i]->sp2->f->x += object->outer_springs[i]->normal.x * outer_p_accu;
		object->outer_springs[i]->sp2->f->y += object->outer_springs[i]->normal.y * outer_p_accu;
		object->outer_springs[i]->sp2->f->z += object->outer_springs[i]->normal.z * outer_p_accu;
	}
}
//*/

/*
//////////////////////////////another unused pressure function based on the triangle face normal////////////
void Integrator::PressureForces()
{
	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2,inner_z1,inner_z2; // points inner_p1, inner_p2 on the inner circle
      float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2; // points outer_p1, outer_p2 on the outer circle

	float inner_rd12;			            			 // length of inner_p1, inner_p2
	float outer_rd12;			            			 // length of outer_p1, outer_p2    

	float inner_volume=0.0;           					 // inner circle inner_volume
	float outer_volume=0.0;		    					 // outer circle outer_volume 

	float inner_p_accu=0;;             					 // pressure force accumulation 
	float outer_p_accu=0;;         					 // pressure force accumulation

	for(i=0;i<object->inner_faces.size();i++)
	{
		object->inner_faces[i]->CalNormalNField();
		object->outer_faces[i]->CalNormalNField();
	}

	// pressure force for the inner circle 
	
	for(i=0; i<object->outer_faces.size(); i++) 			// calculation of inner circle volume
	{
		inner_volume += 0.5 * (object->inner_faces[i]->fp1->r->x +
					     object->inner_faces[i]->fp2->r->x +
					     object->inner_faces[i]->fp3->r->x)*
					    (object->inner_faces[i]->normal->x) * 
					    (object->inner_faces[i]->normal->getLength());

		outer_volume += 0.5 * (object->outer_faces[i]->fp1->r->x +
					     object->outer_faces[i]->fp2->r->x +
					     object->outer_faces[i]->fp3->r->x)*
					    (object->outer_faces[i]->normal->x) * 
					    (object->outer_faces[i]->normal->getLength());
	}

	
	for(i = 0; i < object->outer_faces.size(); i++)  // calculation inner pressure force 
	{
		inner_p_accu=(object->inner_faces[i]->normal->x) * 
				 (object->inner_faces[i]->normal->getLength())*
				((Object2D*)object)->getPressure()*(1.0f/inner_volume);

		object->inner_faces[i]->fp1->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp1->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp1->f->z += 0.5 * inner_p_accu;

		object->inner_faces[i]->fp2->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp2->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp2->f->z += 0.5 * inner_p_accu;

		object->inner_faces[i]->fp3->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp3->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp3->f->z += 0.5 * inner_p_accu;

		////////////////////////////////////////////
	
		outer_p_accu=(object->outer_faces[i]->normal->x) *
				 (object->outer_faces[i]->normal->getLength()) *
				((Object2D*)object)->getPressure() * (1.0f/outer_volume);

		object->outer_faces[i]->fp1->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp1->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp1->f->z += 0.5 * outer_p_accu;

		object->outer_faces[i]->fp2->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp2->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp2->f->z += 0.5 * outer_p_accu;

		object->outer_faces[i]->fp3->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp3->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp3->f->z += 0.5 * outer_p_accu;
	}
}


//*/




///////// calculate the collision detection //////////////////////////////////////////////////
//##ModelId=45F4D7980001
void Integrator::CollisionDetection(int i)
{
	bool changed = false;
	float decay = 0.5;


/////////////////////check the outer layer particle if collide with the wall////////////////
		// Check #1 - X boundaries left
	if((object->outer_points[i]->r->x + object->outer_points[i]->dr->x) < -LIMIT)
	{
		object->outer_points[i]->dr->x = -LIMIT - object->outer_points[i]->r->x;
		changed = true;
	}	// Check #1 - X boundaries right
	else if((object->outer_points[i]->r->x + object->outer_points[i]->dr->x) > LIMIT)
	{
		object->outer_points[i]->dr->x = LIMIT - object->outer_points[i]->r->x;
		changed = true;
	} 

	if(changed)
	{
		object->outer_points[i]->v->x = -decay * object->outer_points[i]->v->x;
		object->outer_points[i]->v->y =  0.5 * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z =  0.5 * object->outer_points[i]->v->z;

	/*	if(object->dim == 1){
			if(i==1){
			object->outer_points[i]->r->x = 0;//object->outer_points[i]->r->x + object->outer_points[i]->dr->x;
			}
		
		}
		else{
		object->outer_points[i]->r->x = object->outer_points[i]->r->x + object->outer_points[i]->dr->x;
		}*/
		object->outer_points[i]->r->x = object->outer_points[i]->r->x + object->outer_points[i]->dr->x;
		changed = false;
	}

	
		// Check #2 - Y boundaries left	
	if((object->outer_points[i]->r->y + object->outer_points[i]->dr->y) < -LIMIT)
	{
		object->outer_points[i]->dr->y = -LIMIT - object->outer_points[i]->r->y;
		changed = true;
	}	// Check #2 - Y boundaries right
	else if((object->outer_points[i]->r->y + object->outer_points[i]->dr->y) > LIMIT)
	{
		object->outer_points[i]->dr->y = LIMIT - object->outer_points[i]->r->y;
		changed = true;
	}

	if(changed)
	{
		object->outer_points[i]->v->x =    0.5 * object->outer_points[i]->v->x;   
		object->outer_points[i]->v->y =  - decay * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z =    0.5 * object->outer_points[i]->v->z;   

		object->outer_points[i]->r->y  = object->outer_points[i]->r->y + object->outer_points[i]->dr->y;
		changed = false;
	}
	

		// Check #3 - Z boundary left	
    	if((object->outer_points[i]->r->z + object->outer_points[i]->dr->z) < -LIMIT )
	{
		object->outer_points[i]->dr->z = -LIMIT - object->outer_points[i]->r->z;
		changed = true;
	}	// Check #3 - Z boundary right
	else if((object->outer_points[i]->r->z + object->outer_points[i]->dr->z) > LIMIT )
	{
		object->outer_points[i]->dr->z = LIMIT - object->outer_points[i]->r->z;
		changed = true;
	}
 

	if(changed)
	{
		object->outer_points[i]->v->x =    0.5 * object->outer_points[i]->v->x;   
		object->outer_points[i]->v->y =    0.5 * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z = - decay * object->outer_points[i]->v->z;   
		
	    object->outer_points[i]->r->z  = object->outer_points[i]->r->z + object->outer_points[i]->dr->z;
		changed = false;
	}



	// Check #4 - Boundary limitations
	if (object->outer_points[i]->r->x < -LIMIT) object->outer_points[i]->r->x = -LIMIT;
	if (object->outer_points[i]->r->y < -LIMIT) object->outer_points[i]->r->y = -LIMIT;
	if (object->outer_points[i]->r->z < -LIMIT) object->outer_points[i]->r->z = -LIMIT;

	if (object->outer_points[i]->r->x > LIMIT) object->outer_points[i]->r->x = LIMIT;
	if (object->outer_points[i]->r->y > LIMIT) object->outer_points[i]->r->y = LIMIT;
	if (object->outer_points[i]->r->z > LIMIT) object->outer_points[i]->r->z = LIMIT;



/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////check the inner layer particle if collide with the wall////////////////
	
	// Check #1 - X boundaries
	if((object->inner_points[i]->r->x + object->inner_points[i]->dr->x) < -LIMIT)
	{
		object->inner_points[i]->dr->x = -LIMIT - object->inner_points[i]->r->x;
		changed = true;
	}
	else if((object->inner_points[i]->r->x + object->inner_points[i]->dr->x) > LIMIT)
	{
		object->inner_points[i]->dr->x = LIMIT - object->inner_points[i]->r->x;
		changed = true;
	} 

	if(changed)
	{
		object->inner_points[i]->v->x = -decay * object->inner_points[i]->v->x;
		object->inner_points[i]->v->y =  0.5 * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z =  0.5 * object->inner_points[i]->v->z;

		object->inner_points[i]->r->x = object->inner_points[i]->r->x + object->inner_points[i]->dr->x;
		changed = false;

	}

	
	// Check #2 - Y boundaries	
	if((object->inner_points[i]->r->y + object->inner_points[i]->dr->y) < -LIMIT)
	{
		object->inner_points[i]->dr->y = -LIMIT - object->inner_points[i]->r->y;
		changed = true;
	}
	else if((object->inner_points[i]->r->y + object->inner_points[i]->dr->y) > LIMIT)
	{
		object->inner_points[i]->dr->y = LIMIT - object->inner_points[i]->r->y;
		changed = true;
	}

	if(changed)
	{
		object->inner_points[i]->v->x =    0.5 * object->inner_points[i]->v->x;   
		object->inner_points[i]->v->y =  - decay * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z =    0.5 * object->inner_points[i]->v->z;   
		
		object->inner_points[i]->r->y  = object->inner_points[i]->r->y + object->inner_points[i]->dr->y;
		changed = false;
	}
	

	// Check #3 - Z boundary
		
    if((object->inner_points[i]->r->z + object->inner_points[i]->dr->z) < -LIMIT )
	{
		object->inner_points[i]->dr->z = -LIMIT - object->inner_points[i]->r->z;
		changed = true;
	}
	else if((object->inner_points[i]->r->z + object->inner_points[i]->dr->z) > LIMIT )
	{
		object->inner_points[i]->dr->z = LIMIT - object->inner_points[i]->r->z;
		changed = true;
	}


	if(changed)
	{
		object->inner_points[i]->v->x =    0.5 * object->inner_points[i]->v->x;   
		object->inner_points[i]->v->y =    0.5 * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z = - decay * object->inner_points[i]->v->z;   
		
	    object->inner_points[i]->r->z  = object->inner_points[i]->r->z + object->inner_points[i]->dr->z;
		changed = false;
	}



	// Check #4 - Boundary limitations
	if (object->inner_points[i]->r->x < -LIMIT) object->inner_points[i]->r->x = -LIMIT;
	if (object->inner_points[i]->r->y < -LIMIT) object->inner_points[i]->r->y = -LIMIT;
	if (object->inner_points[i]->r->z < -LIMIT) object->inner_points[i]->r->z = -LIMIT;

	if (object->inner_points[i]->r->x > LIMIT) object->inner_points[i]->r->x = LIMIT;
	if (object->inner_points[i]->r->y > LIMIT) object->inner_points[i]->r->y = LIMIT;
	if (object->inner_points[i]->r->z > LIMIT) object->inner_points[i]->r->z = LIMIT;

	
}

