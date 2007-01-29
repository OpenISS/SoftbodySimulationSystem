#include "EulerIntegrator.h"

EulerIntegrator::EulerIntegrator(Object& object):Integrator(object)
{
}

EulerIntegrator::~EulerIntegrator()
{
}

void EulerIntegrator::AccumulateForces()   // accumulate forces acted on 
{
	Integrator::AccumulateForces();
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/***********************
 * Euler Integrator *
 ***********************/
//void EulerIntegrator::Derivatives(Particle[] points, int NUMP, float DT)
//void EulerIntegrator::integrate(Object object, int NUMP)

void EulerIntegrator::Derivatives(float deltaT, float k)
{
	int NUMP = object->GetNumberOfParticles();

	for(int i=0; i<NUMP; i++)	
	{
		/*
		object->OneDPoint[i].v->x += k * (object->OneDPoint[i].f->x/object->OneDPoint[i].mass) * deltaT;				// Change in velocity is added to the velocity.
		object->OneDPoint[i].v->y += k * (object->OneDPoint[i].f->y/object->OneDPoint[i].mass) * deltaT;	
		object->OneDPoint[i].r->x += k * object->OneDPoint[i].v->x * deltaT;  											// Change in position is velocity times the change in time
		object->OneDPoint[i].r->y += k * object->OneDPoint[i].v->y * deltaT;
*/
		/*
		object->inner_points[i].v->x += k * (object->inner_points[i].f->x/object->inner_points[i].mass) * deltaT;				// Change in velocity is added to the velocity.
		object->inner_points[i].v->y += k * (object->inner_points[i].f->y/object->inner_points[i].mass) * deltaT;	
		object->inner_points[i].r->x += k * object->inner_points[i].v->x * deltaT;  											// Change in position is velocity times the change in time
		object->inner_points[i].r->y += k * object->inner_points[i].v->y * deltaT;

		object->outer_points[i].v->x += k * (object->outer_points[i].f->x/object->outer_points[i].mass) * deltaT;				// Change in velocity is added to the velocity.
		object->outer_points[i].v->y += k * (object->outer_points[i].f->y/object->outer_points[i].mass) * deltaT;	
		object->outer_points[i].r->x += k * object->outer_points[i].v->x * deltaT;  											// Change in position is velocity times the change in time
		object->outer_points[i].r->y += k * object->outer_points[i].v->y * deltaT;
*/
		/*
		temp_inner_points1[i].v->x = k * (temp_inner_points0[i].f->x/temp_inner_points0[i].mass) * deltaT;
		temp_inner_points1[i].v->y = k * (temp_inner_points0[i].f->y/temp_inner_points0[i].mass) * deltaT;
		temp_inner_points1[i].r->x = k * temp_inner_points0[i].v->x * deltaT;
		temp_inner_points1[i].r->y = k * temp_inner_points0[i].v->y * deltaT;

		object->inner_points[i].v->x = temp_inner_points0[i].v->x + temp_inner_points1[i].v->x;				// Change in velocity is added to the velocity.
		object->inner_points[i].v->y = temp_inner_points0[i].v->y + temp_inner_points1[i].v->y;		
		object->inner_points[i].r->x = temp_inner_points0[i].r->x + temp_inner_points1[i].r->x; 											// Change in position is velocity times the change in time
		object->inner_points[i].r->y = temp_inner_points0[i].r->y + temp_inner_points1[i].r->y;


		temp_outer_points1[i].v->x = k * (temp_outer_points0[i].f->x/temp_outer_points0[i].mass) * deltaT;
		temp_outer_points1[i].v->y = k * (temp_outer_points0[i].f->y/temp_outer_points0[i].mass) * deltaT;
		temp_outer_points1[i].r->x = k * temp_outer_points0[i].v->x * deltaT;
		temp_outer_points1[i].r->y = k * temp_outer_points0[i].v->y * deltaT;

		object->outer_points[i].v->x = temp_outer_points0[i].v->x + temp_outer_points1[i].v->x;				// Change in velocity is added to the velocity.
		object->outer_points[i].v->y = temp_outer_points0[i].v->y + temp_outer_points1[i].v->y;		
		object->outer_points[i].r->x = temp_outer_points0[i].r->x + temp_outer_points1[i].r->x; 											// Change in position is velocity times the change in time
		object->outer_points[i].r->y = temp_outer_points0[i].r->y + temp_outer_points1[i].r->y;
		*/

		ynew(i, k, deltaT);
		CollisionDetection(i);
	}
}


void EulerIntegrator::k1(int i, float k, float deltaT)
{
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
}
