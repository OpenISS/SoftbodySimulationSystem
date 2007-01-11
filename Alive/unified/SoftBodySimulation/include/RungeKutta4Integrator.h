#ifndef RUNGEKUTTA4INTEGRATOR_H
#define RUNGEKUTTA4INTEGRATOR_H

#include "MidpointIntegrator.h"

class RungeKutta4Integrator : public MidpointIntegrator
{
public:
	RungeKutta4Integrator(Object&);
	~RungeKutta4Integrator();

//	virtual void integrate();

	virtual void Derivatives(float deltaT, float k);

};

#endif /* RUNGEKUTTA4INTEGRATOR_H */
