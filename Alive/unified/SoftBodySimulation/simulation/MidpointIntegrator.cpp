#include "MidpointIntegrator.h"

MidpointIntegrator::MidpointIntegrator(Object& object) : EulerIntegrator(object)
{
}

MidpointIntegrator::~MidpointIntegrator()
{
}

//void MidpointIntegrator::integrate()
//{
//}

void MidpointIntegrator::AccumulateForces()   // accumulate forces acted on 
{
	EulerIntegrator::AccumulateForces();
	PressureForces();
}

void MidpointIntegrator::PressureForces()
{
}
