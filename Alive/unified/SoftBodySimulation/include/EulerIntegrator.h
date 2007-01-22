#ifndef EULERINTEGRATOR_H
#define EULERINTEGRATOR_H

#include "Integrator.h"

class EulerIntegrator : public Integrator
{
public:
	EulerIntegrator(Object&);
	virtual ~EulerIntegrator();

	virtual void AccumulateForces();   // accumulate forces acted on 
	virtual void Derivatives(float, float);


protected:
	void k1(int, float, float);
	void ynew(int, float, float);

};

#endif /* EULERINTEGRATOR_H */
