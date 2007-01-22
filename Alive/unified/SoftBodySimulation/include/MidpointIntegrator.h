#ifndef MIDPOINTINTEGRATOR_H
#define MIDPOINTINTEGRATOR_H

#include "EulerIntegrator.h"

class MidpointIntegrator : public EulerIntegrator
{
public:
	MidpointIntegrator(Object&);
	~MidpointIntegrator();

	virtual void AccumulateForces();
//	virtual void Derivatives(float deltaT, float k);

protected:
//	void PressureForces();     // pressure 

	void k2(int, float, float);
	void ynew(int, float, float);
};

#endif /* MIDPOINTINTEGRATOR_H */
