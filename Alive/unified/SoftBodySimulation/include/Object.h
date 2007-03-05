#ifndef OBJECT_H
#define OBJECT_H

#include "Face.h"
#include "Spring.h"
#include "Integrator.h"
#include <vector>
using namespace std;

class Integrator;

class Object
{
protected:
	int numParticles;							// number of particles of the object
	int numSprings;							// number of springs of the object
	Integrator* integrator;						// integrator object
	integrator_type integratorType;				// different type of integrator, Euler, Midpoint, RK4

public:
	vector<Spring*>  inner_springs;				// the springs on the inner layer of the object
	vector<Spring*>  outer_springs;				// the springs on the outer layer of the object
	vector<Particle*>  inner_points;				// the particles on the inner layer of the object
	vector<Particle*>  outer_points;				// the particles on the outer layer of the object
	vector<Face*> inner_faces;					// the surfaces on the inner layer of the object
	vector<Face*> outer_faces;					// the surfaces on the outer layer of the object
	dimensionality dim;						// dimension type to specify the object is 1D, 2D, or 3D

	int   closest_i ;  		    				// the closest point on the outer layer to mouse position

public:
	Object();								// object constructor
	virtual ~Object();						// object destructor 

	int GetNumberOfParticles() { return numParticles; }	// get the number of particles of the object
	int GetNumberOfSprings() { return numSprings; }		// get the number of springs of the object
	
	void setIntegratorType(integrator_type type);		// choose the integrator
	Integrator* getIntegrator() {return integrator;}	// get the integrator type
	
	virtual void Update(float, bool = false, float = 0, float = 0);			//update the object about forces, velocity, position
	
	virtual void Draw() = 0;					// display the object
	virtual void FindClosestPoint(void) ;			// find the closet particle on th outer layer to mouse position

protected:
	virtual void SetParticles();					// model the particles on the object
	virtual void SetObject();					// model the object
	virtual void Add_Structural_Spring(int, int, int);	// construct the springs to model the object
};

#endif /* OBJECT_H */
