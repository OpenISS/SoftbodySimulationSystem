#ifndef MIDPOINTINTEGRATOR_H
#define MIDPOINTINTEGRATOR_H

#include "EulerIntegrator.h"


class MidpointIntegrator : public EulerIntegrator
{
public:
	
	MidpointIntegrator(Object&);	// constructor
	
	~MidpointIntegrator();		// destructor

protected:

	
	void k2(int, float, float);// 2nd integrate to get the derivatives of velocity and position
	
	void ynew(int, float, float);// get the new velocity and position
};

#endif /* MIDPOINTINTEGRATOR_H */
