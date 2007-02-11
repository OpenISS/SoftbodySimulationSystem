#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Object.h"

class Object;

class Integrator
{
protected:
	Object* object;

	Particle temp_inner_points0[MAX_POINTS_SPRINGS];		//temp inner particle container for integrator computation
	Particle temp_inner_points1[MAX_POINTS_SPRINGS];
	Particle temp_inner_points2[MAX_POINTS_SPRINGS];
	Particle temp_inner_points3[MAX_POINTS_SPRINGS];
	Particle temp_inner_points4[MAX_POINTS_SPRINGS];

	Particle temp_outer_points0[MAX_POINTS_SPRINGS];		//temp outer particle container for integrator computation
	Particle temp_outer_points1[MAX_POINTS_SPRINGS];
	Particle temp_outer_points2[MAX_POINTS_SPRINGS];
	Particle temp_outer_points3[MAX_POINTS_SPRINGS];
	Particle temp_outer_points4[MAX_POINTS_SPRINGS];

	dimensionality dim;

public:
	bool dragExists;										//if there is user interaction
	float mDragX;											//mouse position
	float mDragY;

public:
	Integrator(Object&);									//integrator constructor
	virtual ~Integrator();

	virtual void integrate(float, bool drag = false, float xDrag = 0, float yDrag = 0);


	dimensionality getDimension() {return dim;}
	void setDimension(dimensionality dim) {this->dim = dim;}

protected:
	virtual void ExternalForces();     // gravity force
	virtual void SpringForces();       // spring forces 
	virtual void PressureForces();     // pressure  
 
	virtual void AccumulateForces();   // accumulate forces acted on 
	virtual void Derivatives(float, float) = 0;   // Differential computation
	virtual void CollisionDetection(int);

private:
	void CalculateSpringForces(Spring springs[], int i/*, float rd12\, float x1, float y1, float x2, float y2*/);
};

#endif /* INTEGRATOR_H */
