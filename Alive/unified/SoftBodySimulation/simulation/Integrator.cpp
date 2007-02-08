#include "Integrator.h"
#include "Object2D.h"


Integrator::Integrator(Object& object) : dragExists(false)
{

	this->object = &object;
//	memcpy(temp_inner_points0, object.inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points0, object.outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);

	dim = DIM1D;
}

Integrator::~Integrator()
{
//	delete this->initObject;
}

void Integrator::integrate(float deltaT, bool drag, float xDrag, float yDrag)
{
	dragExists = drag;
	mDragX = xDrag;
	mDragY = yDrag;

	AccumulateForces();   // accumulate forces acted on 
	Derivatives(deltaT, 1.0);
 }


void Integrator::AccumulateForces()   // accumulate forces acted on 
{
	ExternalForces();
	SpringForces();	

	switch(dim)
	{
		case DIM1D:
			break;

		case DIM2D:
		case DIM3D:
			PressureForces();
	}
}


void Integrator::ExternalForces()
{
	int i;    // runing index


	float outer_x1,outer_x2,outer_y1,outer_y2;	// points outer_p1, outer_p2 on the outer circle
  
    float outer_rd12;			            	// length of outer_p1, outer_p2

    float outer_Fx,outer_Fy;		            // force vector

	float f;				        // external force 


	for(i = 0; i < object->GetNumberOfParticles(); i++)
	{
/*		object->inner_points[i].f->x = 0;//40*sin(25*i);
		object->inner_points[i].f->y = 0;//(object->inner_points[i].mass)*GY;     
*/
		object->outer_points[i].f->x = 0;//40*sin(25*i);
		object->outer_points[i].f->y = MASS * GY ;//10;//(object->outer_points[i].mass)*GY;
     

	}

	i = 0;
		if(dragExists)			// if user clicked
		{
			outer_x1 = object->outer_points[ i ].r->x;		// get points X-coord
			outer_y1 = object->outer_points[ i ].r->y;        // get points Y-coord
			outer_x2 = mDragX;                      // get Mouse  X-coord
			outer_y2 = mDragY;                      // get Mouse  Y-coord

			outer_rd12 =
				sqrt((outer_x1-outer_x2) * (outer_x1-outer_x2)
					+(outer_y1-outer_y2) * (outer_y1-outer_y2)); // distance

			f = (outer_rd12 - MOUSE_REST) * MOUSE_KS
			  + (
					  object->outer_points[i].v->x * (outer_x1-outer_x2)
					+ object->outer_points[i].v->y * (outer_y1-outer_y2)
				) * MOUSE_KD / outer_rd12;

			// calculate spring force
			outer_Fx = ((outer_x1 - outer_x2) / outer_rd12 ) * f;
			outer_Fy = ((outer_y1 - outer_y2) / outer_rd12 ) * f;

			// accumulate gravity + hooke forces
			object->outer_points[i].f->x -= outer_Fx; // from the closet point to the Mouse point
			object->outer_points[i].f->y -= outer_Fy;
		}
}


void Integrator::SpringForces()
{

	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2;	// points inner_p1, inner_p2 on the inner circle
    float outer_x1,outer_x2,outer_y1,outer_y2;
    
	float inner_rd12;			            	// length of inner_p1, inner_p2
    float outer_rd12;
    float radium_rd12;
	float shear_left_rd12;
	float shear_right_rd12;
	


	// Three parts for computing the spring forces on all the points
	
	
	for(i=0; i<object->GetNumberOfSprings(); i++)  // Part #1, tangent spring force constribution 
	{
/*		inner_x1 = object->inner_springs[i].sp1->r->x;
		inner_y1 = object->inner_springs[i].sp1->r->y;
		inner_x2 = object->inner_springs[i].sp2->r->x;
		inner_y2 = object->inner_springs[i].sp2->r->y;
 */    
		outer_x1 = object->outer_springs[i].sp1->r->x;
		outer_y1 = object->outer_springs[i].sp1->r->y;
		outer_x2 = object->outer_springs[i].sp2->r->x;
		outer_y2 = object->outer_springs[i].sp2->r->y;

/*		inner_rd12 = sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2)
					 +(inner_y1-inner_y2)*(inner_y1-inner_y2));	 // distance on inner
*/
		outer_rd12 = sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2)
					 +(outer_y1-outer_y2)*(outer_y1-outer_y2));	 // distance on outer

		switch(dim)
		{
			case DIM1D:
			{
				radium_rd12 = 0;
				shear_left_rd12 = 0;
				shear_right_rd12 = 0;
				break;
			}

			default:
			{
				radium_rd12 = ((Object2D*)object)->radium_springs[i].restLen;
				shear_left_rd12 = ((Object2D*)object)->shear_springs_left[i].restLen;
				shear_right_rd12 = ((Object2D*)object)->shear_springs_right[i].restLen;
			}
		}

/*		if(inner_rd12!=0) // spring force on points of inner ring
		{
			CalculateSpringForces
			(
				object->inner_springs,
				i,
				inner_rd12,
				inner_x1,
				inner_y1,
				inner_x2,
				inner_y2
			);
		}
*/
		if(outer_rd12!=0) // spring force on points of outer ring
		{
			CalculateSpringForces
			(
				object->outer_springs,
				i,
				outer_rd12,
				outer_x1,
				outer_y1,
				outer_x2,
				outer_y2
			);
		}

/*		if(radium_rd12!=0)
		{
			CalculateSpringForces
			(
				((Object2D*)object)->radium_springs,
				i,
				radium_rd12,
				inner_x1,
				inner_y1,
				outer_x1,
				outer_y1
			);
		}

		//  Part #3 shear spring constribution
		if(shear_left_rd12!=0)
		{
			CalculateSpringForces
			(
				((Object2D*)object)->shear_springs_left,
				i,
				shear_left_rd12,
				inner_x1,
				inner_y1,
				outer_x2,
				outer_y2
			);
		}

		if(shear_right_rd12!=0)
		{
			CalculateSpringForces
			(
				((Object2D*)object)->shear_springs_right,
				i,
				shear_right_rd12,
				inner_x1,
				inner_y1,
				outer_x2,
				outer_y2
			);
		}
*/
		/* Calculate normal vectors to springs */	
	
/*		object->inner_springs[i].normal.x =  -(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y) / inner_rd12;  // Normal Y-vector
		object->inner_springs[i].normal.y =  +(object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x) / inner_rd12;  // Normal X-vector 
*/	
		/* Calculate normal vectors to springs */
		
		object->outer_springs[i].normal.x =  -(object->outer_springs[i].sp1->r->y - object->outer_springs[i].sp2->r->y) / outer_rd12;  // Normal Y-vector
		object->outer_springs[i].normal.y =  +(object->outer_springs[i].sp1->r->x - object->outer_springs[i].sp2->r->x) / outer_rd12;  // Normal X-vector 
	}
}

void Integrator::CalculateSpringForces(Spring springs[], int i, float rd12, float x1, float y1, float x2, float y2)
{
	float vx12, vy12;
	float Fx, Fy;
	float fx, fy;

/*	vx12 = springs[i].sp1->v->x - springs[i].sp2->v->x;
	vy12 = springs[i].sp1->v->y - springs[i].sp2->v->y;

	f =
		(rd12 - springs[i].restLen) * KS
		
		+

		(
			  vx12 * (x1 - x2)
			+ vy12 * (y1 - y2)
		) * KD / rd12;

	Fx = ((x1 - x2) / rd12) * f;
	Fy = ((y1 - y2) / rd12) * f;

*/

	vx12 = springs[i].sp1->v->x - springs[i].sp2->v->x;
	vy12 = springs[i].sp1->v->y - springs[i].sp2->v->y;

	fx =  (rd12 - springs[i].restLen) * KS + vx12 * (x1 - x2)* KD / rd12;
	fy =  (rd12 - springs[i].restLen) * KS + vy12 * (y1 - y2)* KD / rd12;

	Fx = ((x1 - x2) / rd12) * fx;
	Fy = ((y1 - y2) / rd12) * fy;

	cout<<"Fx-------------"<<Fx<<endl;
	cout<<"Fy-------------"<<Fy<<endl;


	springs[i].sp1->f->x -= Fx;
	springs[i].sp1->f->y -= Fy;

	springs[i].sp2->f->x += Fx;
	springs[i].sp2->f->y += Fy;
}

void Integrator::PressureForces()
{
/*	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2;	// points inner_p1, inner_p2 on the inner circle
    float outer_x1,outer_x2,outer_y1,outer_y2;	// points outer_p1, outer_p2 on the outer circle

// 	float radium_rd12;                          // length of inner_p1, outer_p1 

	float inner_rd12;			            	// length of inner_p1, inner_p2
	float outer_rd12;			            	// length of outer_p1, outer_p2    

	float inner_volume=0.0;           // inner circle inner_volume
	float outer_volume=0.0;		    // outer circle outer_volume 

	float inner_p_accu;             // pressure force accumulation 
	float outer_p_accu;         	// pressure force accumulation


	// pressure force for the inner circle 
	
	for(i=0; i<object->GetNumberOfSprings(); i++) // calculation of inner circle volume
	{
        inner_x1 = object->inner_springs[i].sp1->r->x;	
		inner_y1 = object->inner_springs[i].sp1->r->y;
		inner_x2 = object->inner_springs[i].sp2->r->x;	
		inner_y2 = object->inner_springs[i].sp2->r->y;

		inner_rd12=sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2)
		+(inner_y1-inner_y2)*(inner_y1-inner_y2));	
														
		inner_volume+=0.5*fabs(inner_x1-inner_x2)*fabs(object->inner_springs[i].normal.x)*(inner_rd12);

		outer_x1 = object->outer_springs[i].sp1->r->x;	
		outer_y1 = object->outer_springs[i].sp1->r->y;
		outer_x2 = object->outer_springs[i].sp2->r->x;	
		outer_y2 = object->outer_springs[i].sp2->r->y;

		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2)
		+(outer_y1-outer_y2)*(outer_y1-outer_y2));	
														
		outer_volume+=0.5*fabs(outer_x1-outer_x2)*fabs(object->outer_springs[i].normal.x)*(outer_rd12);

	} 

	



	for(i=0; i<object->GetNumberOfSprings(); i++)  // calculation inner pressure force 
	{
        inner_x1 = object->inner_springs[i].sp1->r->x;
		inner_y1 = object->inner_springs[i].sp1->r->y;
		inner_x2 = object->inner_springs[i].sp2->r->x;	
		inner_y2 = object->inner_springs[i].sp2->r->y;

		inner_rd12=sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2) 
		+  (inner_y1-inner_y2)*(inner_y1-inner_y2));	
													

		inner_p_accu=inner_rd12*((Object2D*)object)->getPressure()*(1.0f/inner_volume);
	
		object->inner_springs[i].sp1->f->x += object->inner_springs[i].normal.x*inner_p_accu;
		object->inner_springs[i].sp1->f->y += object->inner_springs[i].normal.y*inner_p_accu;
		object->inner_springs[i].sp2->f->x += object->inner_springs[i].normal.x*inner_p_accu;
		object->inner_springs[i].sp2->f->y += object->inner_springs[i].normal.y*inner_p_accu;

		////////////////////////////////////////////
		outer_x1 = object->outer_springs[i].sp1->r->x;
		outer_y1 = object->outer_springs[i].sp1->r->y;
		outer_x2 = object->outer_springs[i].sp2->r->x;	
		outer_y2 = object->outer_springs[i].sp2->r->y;

		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2) 
		+  (outer_y1-outer_y2)*(outer_y1-outer_y2));	
													

		outer_p_accu=outer_rd12*((Object2D*)object)->getPressure()*(1.0f/outer_volume);
	
		object->outer_springs[i].sp1->f->x += object->outer_springs[i].normal.x*outer_p_accu;
		object->outer_springs[i].sp1->f->y += object->outer_springs[i].normal.y*outer_p_accu;
		object->outer_springs[i].sp2->f->x += object->outer_springs[i].normal.x*outer_p_accu;
		object->outer_springs[i].sp2->f->y += object->outer_springs[i].normal.y*outer_p_accu;

	
	}
*/

}

void Integrator::CollisionDetection(int i)
{


	bool changed = false;

	// Check #1 - X boundaries
	if((object->outer_points[i].r->x + object->outer_points[i].dr->x) < -LIMIT)
	{
		object->outer_points[i].dr->x = -LIMIT - object->outer_points[i].r->x;
		changed = true;
	}
	else if((object->outer_points[i].r->x + object->outer_points[i].dr->x) > LIMIT)
	{
		object->outer_points[i].dr->x = LIMIT - object->outer_points[i].r->x;
		changed = true;
	} 

	if(changed)
	{
	/*	object->outer_points[i].v->x = - 0.2 * object->outer_points[i].v->x;
		object->outer_points[i].v->y =   0.8 * object->outer_points[i].v->y;
		//  object->outer_points[i].v.z =   0.9 * object->outer_points[i].v.z;
	*/	object->outer_points[i].v->x = -0.5 * object->outer_points[i].v->x;
		object->outer_points[i].v->y = 0.5 * object->outer_points[i].v->y;


	//	object->outer_points[i].r->x = object->outer_points[i].r->x + object->outer_points[i].dr->x;
		changed = false;
	}

	
	// Check #2 - Y boundaries	
	if((object->outer_points[i].r->y + object->outer_points[i].dr->y) < -LIMIT)
	{
		object->outer_points[i].dr->y = -LIMIT - object->outer_points[i].r->y;
		changed = true;
	}
	else if((object->outer_points[i].r->y + object->outer_points[i].dr->y) > LIMIT)
	{
		object->outer_points[i].dr->y = LIMIT - object->outer_points[i].r->y;
		changed = true;
	}

	if(changed)
	{
	/*	object->outer_points[i].v->x =    0.8 * object->outer_points[i].v->x;   
		object->outer_points[i].v->y =  - 0.2 * object->outer_points[i].v->y;
	*/	//     object->outer_points[i].v->z =   0.9 * object->outer_points[i].v->z;
		object->outer_points[i].v->x =    0.5 * object->outer_points[i].v->x;   
		object->outer_points[i].v->y =  - 0.5 * object->outer_points[i].v->y;
		
	//	object->outer_points[i].r->y  = object->outer_points[i].r->y + object->outer_points[i].dr->y;
		changed = false;
	}
	

	// Check #3 - Z boundary
		
 /*   if ((object->outer_points[i].r->z + object->outer_points[i].dr->z) < -LIMIT )
	{
       object->outer_points[i].dr->z = -LIMIT - object->outer_points[i].r->z;
	   object->outer_points[i].v->z = - 0.2 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.9 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.9 * object->outer_points[i].v->y;   
	}else
    if ((object->outer_points[i].r->z + object->outer_points[i].dr->z) > LIMIT )
	{
       object->outer_points[i].dr->z = LIMIT - object->outer_points[i].r->z;
	   object->outer_points[i].v->z = - 0.2 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.9 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.9 * object->outer_points[i].v->y;   
	}

    object->outer_points[i].r->z  = object->outer_points[i].r->z + object->outer_points[i].dr->z;

*/
	// Check #4 - Boundary limitations

	if (object->outer_points[i].r->x < -LIMIT) object->outer_points[i].r->x = -LIMIT;
	if (object->outer_points[i].r->y < -LIMIT) object->outer_points[i].r->y = -LIMIT;
//	if (object->outer_points[i].r->z < -LIMIT) object->outer_points[i].r->z = -LIMIT;

	if (object->outer_points[i].r->x > LIMIT) object->outer_points[i].r->x = LIMIT;
	if (object->outer_points[i].r->y > LIMIT) object->outer_points[i].r->y = LIMIT;
//	if (object->outer_points[i].r->z > LIMIT) object->outer_points[i].r->z = LIMIT;



	// Check #1 - X boundaries
/*	if((object->inner_points[i].r->x + object->inner_points[i].dr->x) < -LIMIT )
	{
		object->inner_points[i].dr->x = -LIMIT - object->inner_points[i].r->x;
		changed = true;
	}
	else if((object->inner_points[i].r->x + object->inner_points[i].dr->x) > LIMIT )
	{
		object->inner_points[i].dr->x = LIMIT - object->inner_points[i].r->x;
		changed = true;
	} 

	if(changed)
	{
		object->inner_points[i].v->x = - 0.2 * object->inner_points[i].v->x;
		object->inner_points[i].v->y =   0.9 * object->inner_points[i].v->y;
		//  object->inner_points[i].v.z =   0.9 * object->inner_points[i].v.z;   

		object->inner_points[i].r->x  = object->inner_points[i].r->x + object->inner_points[i].dr->x;
		changed = false;
	}

	
	// Check #2 - Y boundaries	
	if((object->inner_points[i].r->y + object->inner_points[i].dr->y) < -LIMIT )
	{
		object->inner_points[i].dr->y = -LIMIT - object->inner_points[i].r->y;
		changed = true;
	}
	else if((object->inner_points[i].r->y + object->inner_points[i].dr->y) > LIMIT )
	{
		object->inner_points[i].dr->y = LIMIT - object->inner_points[i].r->y;
		changed = true;
	}

	if(changed)
	{
		object->inner_points[i].v->y = - 0.2 * object->inner_points[i].v->y;
		//     object->inner_points[i].v->z =   0.9 * object->inner_points[i].v->z;
		object->inner_points[i].v->x =   0.9 * object->inner_points[i].v->x;   

		object->inner_points[i].r->y  = object->inner_points[i].r->y + object->inner_points[i].dr->y;
		changed = false;
	}
	
*/
	// Check #3 - Z boundary
		
 /*   if ((object->inner_points[i].r->z + object->inner_points[i].dr->z) < -LIMIT )
	{
       object->inner_points[i].dr->z = -LIMIT - object->inner_points[i].r->z;
	   object->inner_points[i].v->z = - 0.2 * object->inner_points[i].v->z;
       object->inner_points[i].v->x =   0.9 * object->inner_points[i].v->x;
       object->inner_points[i].v->y =   0.9 * object->inner_points[i].v->y;   
	}else
    if ((object->inner_points[i].r->z + object->inner_points[i].dr->z) > LIMIT )
	{
       object->inner_points[i].dr->z = LIMIT - object->inner_points[i].r->z;
	   object->inner_points[i].v->z = - 0.2 * object->inner_points[i].v->z;
       object->inner_points[i].v->x =   0.9 * object->inner_points[i].v->x;
       object->inner_points[i].v->y =   0.9 * object->inner_points[i].v->y;   
	}

    object->inner_points[i].r->z  = object->inner_points[i].r->z + object->inner_points[i].dr->z;

*/
	// Check #4 - Boundary limitations

/*	if (object->inner_points[i].r->x < -LIMIT) object->inner_points[i].r->x = -LIMIT;
	if (object->inner_points[i].r->y < -LIMIT) object->inner_points[i].r->y = -LIMIT;
//	if (object->inner_points[i].r->z < -LIMIT) object->inner_points[i].r->z = -LIMIT;

	if (object->inner_points[i].r->x > LIMIT) object->inner_points[i].r->x = LIMIT;
	if (object->inner_points[i].r->y > LIMIT) object->inner_points[i].r->y = LIMIT;
//	if (object->inner_points[i].r->z > L
*/		
}

