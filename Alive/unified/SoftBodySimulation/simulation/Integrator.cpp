#include "Integrator.h"
#include "global.h"
#include "Object2D.h"

#define FIXMEPLEASE 123.1

Integrator::Integrator(Object& object) : dragExists(false)
{
	this->object = &object;
	memcpy(temp_inner_points0, object.inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points0, object.outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);

	dim = DIM2D;
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
 //   memcpy(temp_inner_points0, object->inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
//	memcpy(temp_outer_points0, object->outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
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
	//GravityForce();
	///DragForce();

	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2;	// points inner_p1, inner_p2 on the inner circle
  
    float inner_rd12;			            	// length of inner_p1, inner_p2

    float inner_Fx,inner_Fy;		            // force vector


	float outer_x1,outer_x2,outer_y1,outer_y2;	// points outer_p1, outer_p2 on the outer circle
  
    float outer_rd12;			            	// length of outer_p1, outer_p2

    float outer_Fx,outer_Fy;		            // force vector


	float radium_Fx, radium_Fy;                 // force vector

	float f;				        // external force 

	// Gravity force computation
	
//	for(i=0; i<NUMP; i++)
	for(i=0; i<object->GetNumberOfParticles(); i++)
	{    
	  object->inner_points[i].f->x = 0;//40*sin(25*i);

    // OneDSpring[i].fx = 0.0;
	 object->inner_points[i].f->y = 0;//(object->inner_points[i].mass)*GY;     
     
	 object->outer_points[i].f->x = 0;//40*sin(25*i);

    // OneDSpring[i].fx = 0.0;
	 object->outer_points[i].f->y = 0;//(object->outer_points[i].mass)*GY;
     
//	    when mouse is clicked (mouse spring) 
//		if(i==closest_i)		// closest point on outer ring 
	//	if(i==0)		// closest point on outer ring 

		if(dragExists)			// if user clicked
		{
			outer_x1 = object->outer_points[ i ].r->x;		// get points X-coord
			outer_y1 = object->outer_points[ i ].r->y;        // get points Y-coord
			outer_x2 = mDragX;                      // get Mouse  X-coord
			outer_y2 = mDragY;                      // get Mouse  Y-coord

			outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2)
				        +(outer_y1-outer_y2)*(outer_y1-outer_y2)); // distance

			f=(outer_rd12-MOUSE_REST)*MOUSE_KS+(object->outer_points[i].v->x*(outer_x1-outer_x2)
				+object->outer_points[i].v->y*(outer_y1-outer_y2))*MOUSE_KD/outer_rd12;

			// calculate spring force
			outer_Fx = ((outer_x1 - outer_x2) / outer_rd12 ) * f;
			outer_Fy = ((outer_y1 - outer_y2) / outer_rd12 ) * f;

			// accumulate gravity + hooke forces
			object->outer_points[i].f->x -= outer_Fx; // from the closet point to the Mouse point
			object->outer_points[i].f->y -= outer_Fy;

		}
	}
}

void Integrator::GravityForce()
{
}

void Integrator::DragForce()
{
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
	
	


	float inner_vx12,inner_vy12;    // speed difference vx1-vx2, vy1-vy2 on inner ring  
	float outer_vx12,outer_vy12; 
	float radium_vx12, radium_vy12; // on radium springs
	float shear_left_vx12, shear_left_vy12;   // shear pair
	float shear_right_vx12, shear_right_vy12;

    float inner_Fx,inner_Fy;		            // force vector
	float outer_Fx,outer_Fy;
	float radium_Fx, radium_Fy;                 // force vector
	float shear_left_Fx, shear_left_Fy;         // force vector  
    float shear_right_Fx, shear_right_Fy;       // force vector  

	float f;				        // external force 

	// Three parts for computing the spring forces on all the points
	
	
//	 for(i=0; i<NUMS; i++)  // Part #1, tangent spring force constribution 
	 for(i=0; i<object->GetNumberOfSprings(); i++)  // Part #1, tangent spring force constribution 
	 {
	
	 

			 
		inner_x1 = object->inner_springs[i].sp1->r->x;
		inner_y1 = object->inner_springs[i].sp1->r->y;
		inner_x2 = object->inner_springs[i].sp2->r->x;
		inner_y2 = object->inner_springs[i].sp2->r->y;
     
		outer_x1 = object->outer_springs[i].sp1->r->x;
		outer_y1 = object->outer_springs[i].sp1->r->y;
		outer_x2 = object->outer_springs[i].sp2->r->x;
		outer_y2 = object->outer_springs[i].sp2->r->y;
     

		inner_rd12 = sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2)
					 +(inner_y1-inner_y2)*(inner_y1-inner_y2));	 // distance on inner
 

		outer_rd12 = sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2)
					 +(outer_y1-outer_y2)*(outer_y1-outer_y2));	 // distance on outer
 
		radium_rd12 =((Object2D*)object)->radium_springs[i].restLen;

	    shear_left_rd12 = ((Object2D*)object)->shear_springs_left[i].restLen;

		shear_right_rd12 = ((Object2D*)object)->shear_springs_right[i].restLen;

		if(inner_rd12!=0) // spring force on points of inner ring
		{
			 inner_vx12=object->inner_springs[i].sp1->v->x - object->inner_springs[i].sp2->v->x;
			 inner_vy12=object->inner_springs[i].sp1->v->y - object->inner_springs[i].sp2->v->y;

			f=(inner_rd12-object->inner_springs[i].restLen)*KS
			 +(inner_vx12*(inner_x1-inner_x2)+inner_vy12*(inner_y1-inner_y2))*KD/inner_rd12;

			inner_Fx=((inner_x1-inner_x2)/inner_rd12)*f;
			inner_Fy=((inner_y1-inner_y2)/inner_rd12)*f;


			object->inner_springs[i].sp1->f->x -= inner_Fx;
			object->inner_springs[i].sp1->f->y -= inner_Fy;

			object->inner_springs[i].sp2->f->x += inner_Fx;
			object->inner_springs[i].sp2->f->y += inner_Fy;

		}

		if(outer_rd12!=0) // spring force on points of outer ring
		{
			 outer_vx12=object->outer_springs[i].sp1->v->x - object->outer_springs[i].sp2->v->x;
			 outer_vy12=object->outer_springs[i].sp1->v->y - object->outer_springs[i].sp2->v->y;

			f=(outer_rd12-object->outer_springs[i].restLen)*KS
			 +(outer_vx12*(outer_x1-outer_x2)+outer_vy12*(outer_y1-outer_y2))*KD/outer_rd12;

			outer_Fx=((outer_x1-outer_x2)/outer_rd12)*f;
			outer_Fy=((outer_y1-outer_y2)/outer_rd12)*f;


			object->outer_springs[i].sp1->f->x -= outer_Fx;
			object->outer_springs[i].sp1->f->y -= outer_Fy;

			object->outer_springs[i].sp2->f->x += outer_Fx;
			object->outer_springs[i].sp2->f->y += outer_Fy;

		}


	if(radium_rd12!=0)
	{
	radium_vx12=((Object2D*)object)->radium_springs[i].sp1->v->x - ((Object2D*)object)->radium_springs[i].sp2->v->x;
	radium_vy12=((Object2D*)object)->radium_springs[i].sp1->v->y - ((Object2D*)object)->radium_springs[i].sp2->v->y;

	f=(radium_rd12-((Object2D*)object)->radium_springs[i].restLen)*RKS
	 +(radium_vx12*(inner_x1-outer_x1)+radium_vy12*(inner_y1-outer_y1))*RKD/radium_rd12;

	radium_Fx=((inner_x1-outer_x1)/radium_rd12)*f;
	radium_Fy=((inner_y1-outer_y1)/radium_rd12)*f;


	((Object2D*)object)->radium_springs[i].sp1->f->x-=radium_Fx;
	((Object2D*)object)->radium_springs[i].sp1->f->y-=radium_Fy;

	((Object2D*)object)->radium_springs[i].sp2->f->x+=radium_Fx;
	((Object2D*)object)->radium_springs[i].sp2->f->y+=radium_Fy;

	 
	}


  //  Part #3 shear spring constribution


		if(shear_left_rd12!=0)
	{
shear_left_vx12=((Object2D*)object)->shear_springs_left[i].sp1->v->x - ((Object2D*)object)->shear_springs_left[i].sp2->v->x;
shear_left_vy12=((Object2D*)object)->shear_springs_left[i].sp1->v->y - ((Object2D*)object)->shear_springs_left[i].sp2->v->y;

	f=(shear_left_rd12-((Object2D*)object)->shear_springs_left[i].restLen)*RKS
	 +(shear_left_vx12*(inner_x1-outer_x2)+
	   shear_left_vy12*(inner_y1-outer_y2))*RKD/shear_left_rd12;

	shear_left_Fx=((inner_x1-outer_x2)/shear_left_rd12)*f;
	shear_left_Fy=((inner_y1-outer_y2)/shear_left_rd12)*f;


	((Object2D*)object)->shear_springs_left[i].sp1->f->x-=shear_left_Fx;
	((Object2D*)object)->shear_springs_left[i].sp1->f->y-=shear_left_Fy;

	((Object2D*)object)->shear_springs_left[i].sp2->f->x+=shear_left_Fx;
	((Object2D*)object)->shear_springs_left[i].sp2->f->y+=shear_left_Fy;


	 
	}

    if(shear_right_rd12!=0)
	{
shear_right_vx12=((Object2D*)object)->shear_springs_right[i].sp1->v->x - ((Object2D*)object)->shear_springs_right[i].sp2->v->x;
shear_right_vy12=((Object2D*)object)->shear_springs_right[i].sp1->v->y - ((Object2D*)object)->shear_springs_right[i].sp2->v->y;

	f=(shear_right_rd12-((Object2D*)object)->shear_springs_right[i].restLen)*RKS
	 +(shear_right_vx12*(inner_x1-outer_x2)+
	   shear_right_vy12*(inner_y1-outer_y2))*RKD/shear_right_rd12;

	shear_right_Fx=((inner_x1-outer_x2)/shear_right_rd12)*f;
	shear_right_Fy=((inner_y1-outer_y2)/shear_right_rd12)*f;


	((Object2D*)object)->shear_springs_right[i].sp1->f->x-=shear_right_Fx;
	((Object2D*)object)->shear_springs_right[i].sp1->f->y-=shear_right_Fy;

	((Object2D*)object)->shear_springs_right[i].sp2->f->x+=shear_right_Fx;
	((Object2D*)object)->shear_springs_right[i].sp2->f->y+=shear_right_Fy;

	 
	}






		/* Calculate normal vectors to springs */
		object->inner_springs[i].normal.y =  +(object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x) / inner_rd12;  // Normal X-vector 
		object->inner_springs[i].normal.x =  -(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y) / inner_rd12;  // Normal Y-vector

		/* Calculate normal vectors to springs */
		object->outer_springs[i].normal.y =  +(object->outer_springs[i].sp1->r->x - object->outer_springs[i].sp2->r->x) / outer_rd12;  // Normal X-vector 
		object->outer_springs[i].normal.x =  -(object->outer_springs[i].sp1->r->y - object->outer_springs[i].sp2->r->y) / outer_rd12;  // Normal Y-vector
		
	
	}
}

void Integrator::PressureForces()
{
	
	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2;	// points inner_p1, inner_p2 on the inner circle
    float outer_x1,outer_x2,outer_y1,outer_y2;	// points outer_p1, outer_p2 on the outer circle

 	float radium_rd12;                          // length of inner_p1, outer_p1 

	float inner_rd12;			            	// length of inner_p1, inner_p2
	float outer_rd12;			            	// length of outer_p1, outer_p2    

	float inner_volume=0.0;           // inner circle inner_volume
	float outer_volume=0.0;		    // outer circle outer_volume 

	float inner_p_accu;             // pressure force accumulation 
	float outer_p_accu;         	// pressure force accumulation


//	if(true) return;
//
//	for(i=0; i<NUMS; i++)
//	{
		/* Calculate normal vectors to springs */
/*
		object->outer_springs[i].normal.x =  -(outer_y1 - outer_y2) / outer_rd12;  // Normal X-vector 
		object->outer_springs[i].normal.y =  +(outer_x1 - outer_x2) / outer_rd12;  // Normal Y-vector
		object->inner_springs[i].normal.x =  -(inner_y1 - inner_y2) / inner_rd12;  // Normal X-vector 
		object->inner_springs[i].normal.y =  +(inner_x1 - inner_x2) / inner_rd12;  // Normal Y-vector*/

//		inner_rd12 = sqrt((object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x)*(object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x)
//					 +(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y)*(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y));	 // distance on inner
 
/*		outer_rd12 = sqrt((object->outer_springs[i].sp1->r->x - object->outer_springs[i].sp2->r->x)*(object->outer_springs[i].sp1->r->x - object->outer_springs[i].sp2->r->x)
					 +(object->outer_springs[i].sp1->r->y - object->outer_springs[i].sp2->r->y)*(object->outer_springs[i].sp1->r->y - object->outer_springs[i].sp2->r->y));	 // distance on outer
*/
//		object->outer_springs[i].normal.x =  -(object->outer_springs[i].sp1->r->x - object->outer_springs[i].sp2->r->x) / outer_rd12;  // Normal X-vector 
//		object->outer_springs[i].normal.y =  +(object->outer_springs[i].sp1->r->y - object->outer_springs[i].sp2->r->y) / outer_rd12;  // Normal Y-vector
//		object->inner_springs[i].normal.y =  -(object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x) / inner_rd12;  // Normal X-vector 
//		object->inner_springs[i].normal.x =  +(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y) / inner_rd12;  // Normal Y-vector
//	}

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

	
	/* pressure force for the outer circle */
	/*
	for(i=1; i<=object->GetNumberOfParticles(); i++) // calculation of outer circle volume
	{
        outer_x1 = outer_points[ outer_springs[i].head ].px;	
		outer_y1 = outer_points[ outer_springs[i].head ].py;
		outer_x2 = outer_points[ outer_springs[i].tail ].px;	
		outer_y2 = outer_points[ outer_springs[i].tail ].py;
		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2)
		+(outer_y1-outer_y2)*(outer_y1-outer_y2));	
														
		outer_volume+=0.5*fabs(outer_x1-outer_x2)*fabs(outer_springs[i].nx)*(outer_rd12);
	} */


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


/*
	for(i=1; i<=NUMP; i++)  // calculation outer pressure force 
	{
        outer_x1 = outer_points[ outer_springs[i].head ].px;
		outer_y1 = outer_points[ outer_springs[i].head ].py;
		outer_x2 = outer_points[ outer_springs[i].tail ].px;	
		outer_y2 = outer_points[ outer_springs[i].tail ].py;
		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2) 
		+  (outer_y1-outer_y2)*(outer_y1-outer_y2));	
														
		outer_p_accu=outer_rd12*pressure*(1.0f/outer_volume)/1.5;
		outer_points[outer_springs[i].head].fx+=outer_springs[i].nx*outer_p_accu;
		outer_points[outer_springs[i].head].fy+=outer_springs[i].ny*outer_p_accu;
		outer_points[outer_springs[i].tail].fx+=outer_springs[i].nx*outer_p_accu;
		outer_points[outer_springs[i].tail].fy+=outer_springs[i].ny*outer_p_accu;
	}
	*/
}

void Integrator::CollisionDetection(int i)
{


	// Check #1 - X boundaries
	if ((object->outer_points[i].r->x + object->outer_points[i].dr->x) < -LIMIT )
	{
       object->outer_points[i].dr->x = -LIMIT - object->outer_points[i].r->x;
	   object->outer_points[i].v->x = - 0.2 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.9 * object->outer_points[i].v->y;
     //  object->outer_points[i].v.z =   0.9 * object->outer_points[i].v.z;   
	}else 
	if ((object->outer_points[i].r->x + object->outer_points[i].dr->x) > LIMIT )
	{
       object->outer_points[i].dr->x = LIMIT - object->outer_points[i].r->x;
	   object->outer_points[i].v->x = - 0.2 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.9 * object->outer_points[i].v->y;
    //   ballpoints[i].v->z =   0.9 * ballpoints[i].v->z;   
	} 

    object->outer_points[i].r->x  = object->outer_points[i].r->x + object->outer_points[i].dr->x;

	
	// Check #2 - Y boundaries	
	if ((object->outer_points[i].r->y + object->outer_points[i].dr->y) < -LIMIT )
	{
       object->outer_points[i].dr->y = -LIMIT - object->outer_points[i].r->y;
	   object->outer_points[i].v->y = - 0.2 * object->outer_points[i].v->y;
  //     object->outer_points[i].v->z =   0.9 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.9 * object->outer_points[i].v->x;   
	}else
    if ((object->outer_points[i].r->y + object->outer_points[i].dr->y) > LIMIT )
	{
       object->outer_points[i].dr->y = LIMIT - object->outer_points[i].r->y;
	   object->outer_points[i].v->y = - 0.2 * object->outer_points[i].v->y;
  //     object->outer_points[i].v->z =   0.9 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.9 * object->outer_points[i].v->x;   
	}

    object->outer_points[i].r->y  = object->outer_points[i].r->y + object->outer_points[i].dr->y;
	

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
	if ((object->inner_points[i].r->x + object->inner_points[i].dr->x) < -LIMIT )
	{
       object->inner_points[i].dr->x = -LIMIT - object->inner_points[i].r->x;
	   object->inner_points[i].v->x = - 0.2 * object->inner_points[i].v->x;
       object->inner_points[i].v->y =   0.9 * object->inner_points[i].v->y;
     //  object->inner_points[i].v.z =   0.9 * object->inner_points[i].v.z;   
	}else 
	if ((object->inner_points[i].r->x + object->inner_points[i].dr->x) > LIMIT )
	{
       object->inner_points[i].dr->x = LIMIT - object->inner_points[i].r->x;
	   object->inner_points[i].v->x = - 0.2 * object->inner_points[i].v->x;
       object->inner_points[i].v->y =   0.9 * object->inner_points[i].v->y;
    //   ballpoints[i].v->z =   0.9 * ballpoints[i].v->z;   
	} 

    object->inner_points[i].r->x  = object->inner_points[i].r->x + object->inner_points[i].dr->x;

	
	// Check #2 - Y boundaries	
	if ((object->inner_points[i].r->y + object->inner_points[i].dr->y) < -LIMIT )
	{
       object->inner_points[i].dr->y = -LIMIT - object->inner_points[i].r->y;
	   object->inner_points[i].v->y = - 0.2 * object->inner_points[i].v->y;
  //     object->inner_points[i].v->z =   0.9 * object->inner_points[i].v->z;
       object->inner_points[i].v->x =   0.9 * object->inner_points[i].v->x;   
	}else
    if ((object->inner_points[i].r->y + object->inner_points[i].dr->y) > LIMIT )
	{
       object->inner_points[i].dr->y = LIMIT - object->inner_points[i].r->y;
	   object->inner_points[i].v->y = - 0.2 * object->inner_points[i].v->y;
  //     object->inner_points[i].v->z =   0.9 * object->inner_points[i].v->z;
       object->inner_points[i].v->x =   0.9 * object->inner_points[i].v->x;   
	}

    object->inner_points[i].r->y  = object->inner_points[i].r->y + object->inner_points[i].dr->y;
	

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

	if (object->inner_points[i].r->x < -LIMIT) object->inner_points[i].r->x = -LIMIT;
	if (object->inner_points[i].r->y < -LIMIT) object->inner_points[i].r->y = -LIMIT;
//	if (object->inner_points[i].r->z < -LIMIT) object->inner_points[i].r->z = -LIMIT;

	if (object->inner_points[i].r->x > LIMIT) object->inner_points[i].r->x = LIMIT;
	if (object->inner_points[i].r->y > LIMIT) object->inner_points[i].r->y = LIMIT;
//	if (object->inner_points[i].r->z > L



  
		
}