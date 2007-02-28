#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Object.h"

class Object;

class Integrator
{
protected:
	Object* object;

	vector<Particle*> temp_inner_points0; // temp inner vector<Particle*> container for integrator computation
	vector<Particle*> temp_inner_points1;
	vector<Particle*> temp_inner_points2;
	vector<Particle*> temp_inner_points3;
	vector<Particle*> temp_inner_points4;

	vector<Particle*> temp_outer_points0; // temp outer vector<Particle*> container for integrator computation
	vector<Particle*> temp_outer_points1;
	vector<Particle*> temp_outer_points2;
	vector<Particle*> temp_outer_points3;
	vector<Particle*> temp_outer_points4;

	dimensionality dim;

public:
	bool dragExists;				  //if there is user interaction
	float mDragX;				  // mouse position x axis
	float mDragY;				  // mouse position y axis

public:
	Integrator(Object&);			  // integrator constructor with the computed object
	virtual ~Integrator();			  // integrator destructor

	// the calculation of the integration with/without external dragging force
	virtual void integrate(float, bool drag = false, float xDrag = 0, float yDrag = 0);

	dimensionality getDimension() {return dim;}   		    // get the object type, 1D, 2D, or 3D
	void setDimension(dimensionality dim) {this->dim = dim;}  // set the object type, 1D, 2D, or 3D

protected:
	virtual void ExternalForces();     				   // accumulate gravity and dragging force
	virtual void SpringForces();       				   // accumulate all type of springs forces 
	virtual void PressureForces();     				   // accumulate pressure  
 
	virtual void AccumulateForces();   				   // accumulate all forces acted on object 
	virtual void Derivatives(float, float) = 0;   		   // Differential computation
	virtual void CollisionDetection(int);			   // calculate the collision detection 

private:
	// general spring calculation function 
	void CalculateSpringForces(vector<Spring *>springs, int i, bool special = false);
};

#endif /* INTEGRATOR_H */
