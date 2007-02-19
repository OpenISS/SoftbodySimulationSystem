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


	int numParticles;							//number of particles of the object
	int numSprings;								//number of springs of the object

	Integrator* integrator;						//integrator object
	integrator_type integratorType;				//different type of integrator, Euler, Midpoint, RK4

	dimensionality dim;							//dimension type to specify the object is 1D, 2D, or 3D

public:
/*	Spring inner_springs[MAX_POINTS_SPRINGS];	//springs for inner layer object
	Particle inner_points[MAX_POINTS_SPRINGS];	//particles for inner layer object

	Spring outer_springs[MAX_POINTS_SPRINGS];   //springs for outer layer object
	Particle outer_points[MAX_POINTS_SPRINGS];  //particles for outer layer object
*/

	vector<Spring*>  inner_springs;
	vector<Spring*>  outer_springs;
	vector<Particle*>  inner_points;
	vector<Particle*>  outer_points;
	vector<Face*> inner_faces;
	vector<Face*> outer_faces;

	int   closest_i ;  		    // the point which is closest to mouse position


public:
	Object();									//object constructor
	virtual ~Object();							//object diconstructor


	int GetNumberOfParticles() { return numParticles; }					//get the number of particles of the object
	int GetNumberOfSprings() { return numSprings; }						//get the number of springs of the object

	
	void setIntegratorType(integrator_type type);						//choose the integrator
	Integrator* getIntegrator() {return integrator;}					//get the integrator type
	
	virtual void Update(float, bool = false, float = 0, float = 0);		//update the object about forces, velocity, position
	
	virtual void Draw() = 0;											//display the object
	virtual void FindClosestPoint(void) ;

protected:
	virtual void SetParticles();										//model the particles on the object
	virtual void SetObject();											//model the object
	virtual void Add_Structural_Spring(int, int, int);

};

#endif /* OBJECT_H */
