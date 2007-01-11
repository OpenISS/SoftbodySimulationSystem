#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Object.h"

enum dimensionality {DIM1D, DIM2D, DIM3D};

class Object;

class Integrator
{
protected:
	Object* object;

	bool dragExists;
	float mDragX;
	float mDragY;

public:
	Integrator(Object&);
	virtual ~Integrator();

//	virtual void integrate(float);
	virtual void integrate(float, bool drag = false, float xDrag = 0, float yDrag = 0);

protected:
	virtual void ExternalForces();     // gravity force
	virtual void SpringForces();       // spring forces 
 
	virtual void AccumulateForces();   // accumulate forces acted on 
	virtual void Derivatives(float) = 0;   // Differential computation

	virtual void GravityForce();
	virtual void DragForce();
};

#endif /* INTEGRATOR_H */
