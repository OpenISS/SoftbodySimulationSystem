#include "EulerIntegrator.h"

EulerIntegrator::EulerIntegrator(Object& object):Integrator(object)
{
}

EulerIntegrator::~EulerIntegrator()
{
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/***********************
 * Euler Integrator *
 ***********************/
//void EulerIntegrator::Derivatives(Particle[] points, int NUMP, float DT)
//void EulerIntegrator::integrate(Object object, int NUMP)

void EulerIntegrator::Derivatives(float deltaT, float k)
{cout<<"derivatives.............."<<endl;
	int NUMP = object->GetNumberOfParticles();

	for(int i=0; i<NUMP; i++)	
	{
		ynew(i, k, deltaT);
//		CollisionDetection(i);
	
	}
}


void EulerIntegrator::k1(int i, float k, float deltaT)
{
	memcpy(temp_inner_points0, object->inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points0, object->outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);

	temp_inner_points1[i].v->x = k * (temp_inner_points0[i].f->x/temp_inner_points0[i].mass) * deltaT;
	temp_inner_points1[i].v->y = k * (temp_inner_points0[i].f->y/temp_inner_points0[i].mass) * deltaT;
	temp_inner_points1[i].r->x = k * temp_inner_points0[i].v->x * deltaT;
	temp_inner_points1[i].r->y = k * temp_inner_points0[i].v->y * deltaT;

	temp_outer_points1[i].v->x = k * (temp_outer_points0[i].f->x/temp_outer_points0[i].mass) * deltaT;
	temp_outer_points1[i].v->y = k * (temp_outer_points0[i].f->y/temp_outer_points0[i].mass) * deltaT;
	temp_outer_points1[i].r->x = k * temp_outer_points0[i].v->x * deltaT;
	temp_outer_points1[i].r->y = k * temp_outer_points0[i].v->y * deltaT;
}

void EulerIntegrator::ynew(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

	object->inner_points[i].v->x = temp_inner_points0[i].v->x + temp_inner_points1[i].v->x;				// Change in velocity is added to the velocity.
	object->inner_points[i].v->y = temp_inner_points0[i].v->y + temp_inner_points1[i].v->y;		
	object->inner_points[i].r->x = temp_inner_points0[i].r->x + temp_inner_points1[i].r->x; 											// Change in position is velocity times the change in time
	object->inner_points[i].r->y = temp_inner_points0[i].r->y + temp_inner_points1[i].r->y;

	object->outer_points[i].v->x = temp_outer_points0[i].v->x + temp_outer_points1[i].v->x;				// Change in velocity is added to the velocity.
	object->outer_points[i].v->y = temp_outer_points0[i].v->y + temp_outer_points1[i].v->y;		
	object->outer_points[i].r->x = temp_outer_points0[i].r->x + temp_outer_points1[i].r->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].r->y = temp_outer_points0[i].r->y + temp_outer_points1[i].r->y;

	if ((object->outer_points[i].r->x + object->outer_points[i].dr->x) < -LIMIT )
	{
       object->outer_points[i].dr->x = -LIMIT + object->outer_points[i].r->x;
	   object->outer_points[i].v->x = - 0.2 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.8 * object->outer_points[i].v->y;
     //  object->outer_points[i].v.z =   0.9 * object->outer_points[i].v.z;   
	}else 
	if ((object->outer_points[i].r->x + object->outer_points[i].dr->x) > LIMIT )
	{
       object->outer_points[i].dr->x = LIMIT - object->outer_points[i].r->x;
	   object->outer_points[i].v->x = - 0.2 * object->outer_points[i].v->x;
       object->outer_points[i].v->y =   0.8 * object->outer_points[i].v->y;
    //   ballpoints[i].v->z =   0.9 * ballpoints[i].v->z;   
	} 

    object->outer_points[i].r->x  = object->outer_points[i].r->x + object->outer_points[i].dr->x;

	
	// Check #2 - Y boundaries	
	if ((object->outer_points[i].r->y + object->outer_points[i].dr->y) < -LIMIT )
	{
       object->outer_points[i].dr->y = -LIMIT + object->outer_points[i].r->y;
	   object->outer_points[i].v->y = - 0.2 * object->outer_points[i].v->y;
  //     object->outer_points[i].v->z =   0.9 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.8 * object->outer_points[i].v->x;   
	}else
    if ((object->outer_points[i].r->y + object->outer_points[i].dr->y) > LIMIT )
	{
       object->outer_points[i].dr->y = LIMIT - object->outer_points[i].r->y;
	   object->outer_points[i].v->y = - 0.2 * object->outer_points[i].v->y;
  //     object->outer_points[i].v->z =   0.9 * object->outer_points[i].v->z;
       object->outer_points[i].v->x =   0.8 * object->outer_points[i].v->x;   
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
