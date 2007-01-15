#include "Integrator.h"
#include "global.h"
#include "Object2D.h"

#define FIXMEPLEASE 123.1

Integrator::Integrator(Object& object) : dragExists(false)
{
	this->object = &object;
}

Integrator::~Integrator()
{
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
	PressureForces();
}


void Integrator::ExternalForces()
{
	//GravityForce();
	///DragForce();

	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2;	// points inner_p1, inner_p2 on the inner circle
  
    float inner_rd12;			            	// length of inner_p1, inner_p2

    float inner_Fx,inner_Fy;		            // force vector

	float f;				        // external force 

	// Gravity force computation
	
//	for(i=0; i<NUMP; i++)
	for(i=0; i<object->GetNumberOfParticles(); i++)
	{    
	  object->inner_points[i].f->x = 0;//40*sin(25*i);

    // OneDSpring[i].fx = 0.0;
	 object->inner_points[i].f->y = 0;//(object->inner_points[i].mass)*GY;     
     
	
//	    when mouse is clicked (mouse spring) 
//		if(i==closest_i)		// closest point on outer ring 
		if(i==0)		// closest point on outer ring 

		if(dragExists)			// if user clicked
		{
			inner_x1 = object->inner_points[ i ].r->x;		// get points X-coord
			inner_y1 = object->inner_points[ i ].r->y;        // get points Y-coord
			inner_x2 = mDragX;                      // get Mouse  X-coord
			inner_y2 = mDragY;                      // get Mouse  Y-coord

			inner_rd12=sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2)
				        +(inner_y1-inner_y2)*(inner_y1-inner_y2)); // distance

			f=(inner_rd12-MOUSE_REST)*MOUSE_KS+(object->inner_points[i].v->x*(inner_x1-inner_x2)
				+object->inner_points[i].v->y*(inner_y1-inner_y2))*MOUSE_KD/inner_rd12;

			// calculate spring force
			inner_Fx = ((inner_x1 - inner_x2) / inner_rd12 ) * f;
			inner_Fy = ((inner_y1 - inner_y2) / inner_rd12 ) * f;

			// accumulate gravity + hooke forces
			object->inner_points[i].f->x -= inner_Fx; // from the closet point to the Mouse point
			object->inner_points[i].f->y -= inner_Fy;

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
  
    float inner_rd12;			            	// length of inner_p1, inner_p2

    float inner_vx12,inner_vy12;    // speed difference vx1-vx2, vy1-vy2 on inner ring  
	// 

    float inner_Fx,inner_Fy;		            // force vector

	float f;				        // external force 

	// Three parts for computing the spring forces on all the points
	
	
//	 for(i=0; i<NUMS; i++)  // Part #1, tangent spring force constribution 
	 for(i=0; i<object->GetNumberOfSprings(); i++)  // Part #1, tangent spring force constribution 
	 {
	
	  /*  inner_x1 = OneDSpring[ inner_springs[i].head ].px;
		inner_y1 = OneDSpring[ inner_springs[i].head ].py;
		inner_x2 = OneDSpring[ inner_springs[i].tail ].px;
		inner_y2 = OneDSpring[ inner_springs[i].tail ].py;
		*/

			 
		inner_x1 = object->inner_springs[i].sp1->r->x;
		inner_y1 = object->inner_springs[i].sp1->r->y;
		inner_x2 = object->inner_springs[i].sp2->r->x;
		inner_y2 = object->inner_springs[i].sp2->r->y;
     
    

		inner_rd12 = sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2)
					 +(inner_y1-inner_y2)*(inner_y1-inner_y2));	 // distance on inner
 

 
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

		
		/* Calculate normal vectors to springs */
		object->inner_springs[i].normal.y =  -(object->inner_springs[i].sp1->r->x - object->inner_springs[i].sp2->r->x) / inner_rd12;  // Normal X-vector 
		object->inner_springs[i].normal.x =  +(object->inner_springs[i].sp1->r->y - object->inner_springs[i].sp2->r->y) / inner_rd12;  // Normal Y-vector
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
