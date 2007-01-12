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
		object->inner_points[i].v->x += k * (object->inner_points[i].f->x/object->inner_points[i].mass) * deltaT;				// Change in velocity is added to the velocity.
		object->inner_points[i].v->y += k * (object->inner_points[i].f->y/object->inner_points[i].mass) * deltaT;	
		object->inner_points[i].r->x += k * object->inner_points[i].v->x * deltaT;  											// Change in position is velocity times the change in time
		object->inner_points[i].r->y += k * object->inner_points[i].v->y * deltaT;
	}
}
