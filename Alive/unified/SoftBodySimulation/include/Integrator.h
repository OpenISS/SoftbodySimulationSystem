#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Object.h"

class Object;

//##ModelId=45F4D79702FF
class Integrator
{
protected:
	//##ModelId=45F4D7970301
	Object* object;

	//##ModelId=45F4D7970310
	vector<Particle*> temp_inner_points0; // temp inner vector<Particle*> container for integrator computation
	//##ModelId=45F4D797031F
	vector<Particle*> temp_inner_points1;
	//##ModelId=45F4D7970324
	vector<Particle*> temp_inner_points2;
	//##ModelId=45F4D797032F
	vector<Particle*> temp_inner_points3;
	//##ModelId=45F4D797033F
	vector<Particle*> temp_inner_points4;

	//##ModelId=45F4D7970344
	vector<Particle*> temp_outer_points0; // temp outer vector<Particle*> container for integrator computation
	//##ModelId=45F4D797034E
	vector<Particle*> temp_outer_points1;
	//##ModelId=45F4D797035E
	vector<Particle*> temp_outer_points2;
	//##ModelId=45F4D797036D
	vector<Particle*> temp_outer_points3;
	//##ModelId=45F4D797037D
	vector<Particle*> temp_outer_points4;

	//##ModelId=45F4D7970382
	dimensionality dim;

public:
	//##ModelId=45F4D797038C
	bool dragExists;				  //if there is user interaction
	//##ModelId=45F4D797038D
	float mDragX;				  // mouse position x axis
	//##ModelId=45F4D797039B
	float mDragY;				  // mouse position y axis

public:
	//##ModelId=45F4D797039C
	Integrator(Object&);			  // integrator constructor with the computed object
	//##ModelId=45F4D79703AB
	virtual ~Integrator();			  // integrator destructor

	// the calculation of the integration with/without external dragging force
	//##ModelId=45F4D79703AD
	virtual void integrate(float, bool drag = false, float xDrag = 0, float yDrag = 0);

	//##ModelId=45F4D79703BC
	dimensionality getDimension() {return dim;}   		    // get the object type, 1D, 2D, or 3D
	//##ModelId=45F4D79703BD
	void setDimension(dimensionality dim) {this->dim = dim;}  // set the object type, 1D, 2D, or 3D

protected:
	//##ModelId=45F4D79703CA
	virtual void ExternalForces();     				   // accumulate gravity and dragging force
	//##ModelId=45F4D79703CC
	virtual void SpringForces();       				   // accumulate all type of springs forces 
	//##ModelId=45F4D79703CE
	virtual void PressureForces();     				   // accumulate pressure  
 
	//##ModelId=45F4D79703DA
	virtual void AccumulateForces();   				   // accumulate all forces acted on object 
	//##ModelId=45F4D79703DC
	virtual void Derivatives(float, float) = 0;   		   // Differential computation
	//##ModelId=45F4D7980001
	virtual void CollisionDetection(int);			   // calculate the collision detection 

private:
	// general spring calculation function 
	//##ModelId=45F4D7980004
	void CalculateSpringForces(vector<Spring *>springs, int i, bool special = false);
};

#endif /* INTEGRATOR_H */
