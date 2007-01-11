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

void EulerIntegrator::Derivatives(float deltaT)
{
	int NUMP = object->GetNumberOfParticles();
	for(int i=0; i<NUMP; i++)	
	{
		object->OneDPoint[i].v->x += (object->OneDPoint[i].f->x/object->OneDPoint[i].mass) * deltaT;				// Change in velocity is added to the velocity.
		object->OneDPoint[i].v->y += (object->OneDPoint[i].f->y/object->OneDPoint[i].mass) * deltaT;	
		object->OneDPoint[i].r->x +=  object->OneDPoint[i].v->x * deltaT;  											// Change in position is velocity times the change in time
		object->OneDPoint[i].r->y +=  object->OneDPoint[i].v->y * deltaT;
	}
}
