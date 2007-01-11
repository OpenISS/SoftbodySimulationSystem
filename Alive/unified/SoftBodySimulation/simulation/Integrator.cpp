#include "Integrator.h"

#define FIXMEPLEASE 123.1

Integrator::Integrator(Object& object)
{
	this->object = &object;
}

Integrator::~Integrator()
{
}

void Integrator::integrate(float deltaT)
{
	AccumulateForces();   // accumulate forces acted on 
	Derivatives(deltaT);
}

void Integrator::AccumulateForces()   // accumulate forces acted on 
{
	ExternalForces();
//	PressureForces();
	SpringForces();
}

//void Integrator::Derivatives(float)
//{
//}

void Integrator::ExternalForces()
{
	GravityForce();
	DragForce();
}

void Integrator::GravityForce()
{
}

void Integrator::DragForce()
{
}

void Integrator::SpringForces()
{
}
