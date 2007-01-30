#ifndef OBJECT_H
#define OBJECT_H

#include "Face.h"
#include "Spring.h"
#include "Particle.h"

#define MAX_POINTS_SPRINGS 40


#include "Integrator.h"

#include "global.h"

using namespace std;

class Integrator;

enum integrator_type {EULER, MIDPOINT, RK4};

class Object
{
protected:
	vector<Face*> face; 

	int NUMP;
	int NUMS;

	//tmp
	int PosX;
	int PosY;
	float Mass1, Mass2;
	float Ks1, Ks2;
	float Kd1, Kd2;

	Integrator* integrator;
	integrator_type integratorType;


public:
	Spring inner_springs[MAX_POINTS_SPRINGS];
	Particle inner_points[MAX_POINTS_SPRINGS];

	Spring outer_springs[MAX_POINTS_SPRINGS];     // for point springs on outer circle
	Particle outer_points[MAX_POINTS_SPRINGS];  // for outer circle Particles + 1 mouse Particle


public:
	Object();
//	Object(Object&);
	virtual ~Object();


	int GetNumberOfParticles() { return NUMP; }
	int GetNumberOfSprings() { return NUMS; }

	virtual void Draw() = 0; 
	virtual void Update(float, bool = false, float = 0, float = 0);

	//virtual void Clone(); 

	virtual void SetObject();           // Then, make the Object3D object

	Integrator* getIntegrator() {return integrator;}

	void setIntegratorType(integrator_type type);

protected:
	virtual void SetParticles();         // create Particle Object3D
	virtual void SetSprings();   // set springs on horizontal planes, connect Particles
	virtual void SetTriPlanes();      // set triangle faces on side surfaces
};

#endif /* OBJECT_H */
