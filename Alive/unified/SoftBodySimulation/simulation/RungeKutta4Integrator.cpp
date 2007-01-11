#include "RungeKutta4Integrator.h"

RungeKutta4Integrator::RungeKutta4Integrator(Object& object) : MidpointIntegrator(object)
{
}

RungeKutta4Integrator::~RungeKutta4Integrator()
{
}

void RungeKutta4Integrator::Derivatives(float deltaT, float k)
{
//	EulerIntegrator::Derivatives(deltaT, 1.0); //1

	EulerIntegrator::Derivatives(deltaT, 0.5); //2

	EulerIntegrator::Derivatives(deltaT, 0.5); //3
	EulerIntegrator::Derivatives(deltaT, 1.0); //4
}
