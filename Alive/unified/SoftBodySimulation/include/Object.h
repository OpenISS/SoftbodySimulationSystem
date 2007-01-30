#ifndef OBJECT_H
#define OBJECT_H

#include "Face.h"
#include "Spring.h"
#include "Integrator.h"

using namespace std;

class Integrator;

class Object
{
protected:
	vector<Face*> face; 

	int numParticles;
	int numSprings;

	Integrator* integrator;
	integrator_type integratorType;


public:
	Spring inner_springs[MAX_POINTS_SPRINGS];
	Particle inner_points[MAX_POINTS_SPRINGS];

	Spring outer_springs[MAX_POINTS_SPRINGS];     // for point springs on outer circle
	Particle outer_points[MAX_POINTS_SPRINGS];  // for outer circle Particles + 1 mouse Particle


public:
	Object();
	virtual ~Object();


	int GetNumberOfParticles() { return numParticles; }
	int GetNumberOfSprings() { return numSprings; }

	virtual void Draw() = 0; 
	virtual void Update(float, bool = false, float = 0, float = 0);

	virtual void SetObject();           // Then, make the Object3D object

	Integrator* getIntegrator() {return integrator;}

	void setIntegratorType(integrator_type type);

protected:
	virtual void SetParticles();         // create Particle Object3D
};

#endif /* OBJECT_H */
