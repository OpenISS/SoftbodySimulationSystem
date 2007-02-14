#ifndef RUNGEKUTTA4INTEGRATOR_H
#define RUNGEKUTTA4INTEGRATOR_H

#include "MidpointIntegrator.h"

class RungeKutta4Integrator : public MidpointIntegrator
{
public:
	RungeKutta4Integrator(Object&);
	~RungeKutta4Integrator();

protected:

	void k4(int, float, float);
	void k3(int, float, float);
//	void k2(int, float, float);
	void ynew(int, float, float);
};

#endif /* RUNGEKUTTA4INTEGRATOR_H */
