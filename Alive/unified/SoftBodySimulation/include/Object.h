#ifndef OBJECT_H
#define OBJECT_H

#include "Face.h"
#include "Spring.h"
#include "Particle.h"

#include "Integrator.h"

#include "global.h"

using namespace std;

class Integrator;

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

public:
	Spring OneDSpring[1];
	Particle OneDPoint[2];


public:
	Object();
	virtual ~Object();


	int GetNumberOfParticles() { return NUMP; }
	int GetNumberOfSprings() { return NUMS; }

	virtual void Draw() = 0; 
	virtual void Update(float, bool = false, float = 0, float = 0);

	virtual void SetObject();           // Then, make the Object3D object

	Integrator* getIntegrator() {return integrator;}

protected:
	virtual void SetParticles();         // create Particle Object3D
	virtual void SetSprings();   // set springs on horizontal planes, connect Particles
	virtual void SetTriPlanes();      // set triangle faces on side surfaces
};

#endif /* OBJECT_H */
