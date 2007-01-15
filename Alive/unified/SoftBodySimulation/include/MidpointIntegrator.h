#ifndef MIDPOINTINTEGRATOR_H
#define MIDPOINTINTEGRATOR_H

#include "EulerIntegrator.h"

class MidpointIntegrator : public EulerIntegrator
{
public:
	MidpointIntegrator(Object&);
	~MidpointIntegrator();

	virtual void AccumulateForces();
	virtual void Derivatives(float deltaT, float k);

//protected:
//	void PressureForces();     // pressure  
};

#endif /* MIDPOINTINTEGRATOR_H */
