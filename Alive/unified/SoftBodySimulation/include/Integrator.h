#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Object.h"

enum dimensionality {DIM1D, DIM2D, DIM3D};

class Object;

class Integrator
{
protected:
	Object* object;
///	Object* initObject;

	Particle temp_inner_points0[MAX_POINTS_SPRINGS];
	Particle temp_inner_points1[MAX_POINTS_SPRINGS];
	Particle temp_inner_points2[MAX_POINTS_SPRINGS];
	Particle temp_inner_points3[MAX_POINTS_SPRINGS];
	Particle temp_inner_points4[MAX_POINTS_SPRINGS];

	Particle temp_outer_points0[MAX_POINTS_SPRINGS];
	Particle temp_outer_points1[MAX_POINTS_SPRINGS];
	Particle temp_outer_points2[MAX_POINTS_SPRINGS];
	Particle temp_outer_points3[MAX_POINTS_SPRINGS];
	Particle temp_outer_points4[MAX_POINTS_SPRINGS];

	bool dragExists;
	float mDragX;
	float mDragY;

	dimensionality dim;

public:
	Integrator(Object&);
	virtual ~Integrator();

//	virtual void integrate(float);
	virtual void integrate(float, bool drag = false, float xDrag = 0, float yDrag = 0);

protected:
	virtual void ExternalForces();     // gravity force
	virtual void SpringForces();       // spring forces 
	virtual void PressureForces();     // pressure  
 
	virtual void AccumulateForces();   // accumulate forces acted on 
	virtual void Derivatives(float, float) = 0;   // Differential computation

	virtual void GravityForce();
	virtual void DragForce();
};

#endif /* INTEGRATOR_H */
