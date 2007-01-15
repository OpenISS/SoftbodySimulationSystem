#include "MidpointIntegrator.h"
#include "Object2D.h"

MidpointIntegrator::MidpointIntegrator(Object& object) : EulerIntegrator(object)
{
}

MidpointIntegrator::~MidpointIntegrator()
{
}

void MidpointIntegrator::AccumulateForces()   // accumulate forces acted on 
{
	EulerIntegrator::AccumulateForces();
//	PressureForces();
}


void MidpointIntegrator::Derivatives(float deltaT, float k)
{
	EulerIntegrator::Derivatives(deltaT, 0.5);
	EulerIntegrator::Derivatives(deltaT, 1.0);
}
