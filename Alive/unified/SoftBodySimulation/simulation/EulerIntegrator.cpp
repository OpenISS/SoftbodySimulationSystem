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
{

	int NUMP = object->GetNumberOfParticles();

	for(int i=0; i<NUMP; i++)	
	{
		ynew(i, k, deltaT);
		CollisionDetection(i);
	}
}


void EulerIntegrator::k1(int i, float k, float deltaT)
{
//	memcpy(temp_inner_points0, object->inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points0, object->outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);

/*	temp_inner_points1[i].v->x = k * (temp_inner_points0[i].f->x/temp_inner_points0[i].mass) * deltaT;
	temp_inner_points1[i].v->y = k * (temp_inner_points0[i].f->y/temp_inner_points0[i].mass) * deltaT;
	temp_inner_points1[i].r->x = k * temp_inner_points0[i].v->x * deltaT;
	temp_inner_points1[i].r->y = k * temp_inner_points0[i].v->y * deltaT;

*/
	temp_outer_points1[i].dv->x = k * (temp_outer_points0[i].f->x/temp_outer_points0[i].mass) * deltaT;
	temp_outer_points1[i].dv->y = k * (temp_outer_points0[i].f->y/temp_outer_points0[i].mass) * deltaT;
	
	temp_outer_points1[i].dr->x = k * temp_outer_points0[i].v->x * deltaT;
	temp_outer_points1[i].dr->y = k * temp_outer_points0[i].v->y * deltaT;

	/*
	object->outer_points[i].dv->x = k * (object->outer_points[i].f->x/object->outer_points[i].mass) * deltaT;
	object->outer_points[i].dv->y = k * (object->outer_points[i].f->y/object->outer_points[i].mass) * deltaT;
	
	object->outer_points[i].dr->x = k * object->outer_points[i].v->x * deltaT;
	object->outer_points[i].dr->y = k * object->outer_points[i].v->y * deltaT;
	*/
}

void EulerIntegrator::ynew(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

/*	object->inner_points[i].v->x = temp_inner_points0[i].v->x + temp_inner_points1[i].v->x;				// Change in velocity is added to the velocity.
	object->inner_points[i].v->y = temp_inner_points0[i].v->y + temp_inner_points1[i].v->y;		
	object->inner_points[i].r->x = temp_inner_points0[i].r->x + temp_inner_points1[i].r->x; 											// Change in position is velocity times the change in time
	object->inner_points[i].r->y = temp_inner_points0[i].r->y + temp_inner_points1[i].r->y;
*/

	object->outer_points[i].v->x = temp_outer_points0[i].v->x + temp_outer_points1[i].dv->x;				// Change in velocity is added to the velocity.
	object->outer_points[i].v->y = temp_outer_points0[i].v->y + temp_outer_points1[i].dv->y;		

	object->outer_points[i].r->x = temp_outer_points0[i].r->x + temp_outer_points1[i].dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].r->y = temp_outer_points0[i].r->y + temp_outer_points1[i].dr->y;

	object->outer_points[i].dv->x = temp_outer_points1[i].dv->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].dv->y = temp_outer_points1[i].dv->y;

	object->outer_points[i].dr->x = temp_outer_points1[i].dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].dr->y = temp_outer_points1[i].dr->y;


  /*
	object->outer_points[i].v->x += object->outer_points[i].dv->x;				// Change in velocity is added to the velocity.
	object->outer_points[i].v->y += object->outer_points[i].dv->y;		

	object->outer_points[i].r->x += object->outer_points[i].dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].r->y += object->outer_points[i].dr->y;
*/
}
