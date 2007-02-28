#ifndef OBJECT3D_H
#define OBJECT3D_H


#include "Particle.h"
#include "Spring.h"

#include "Object2D.h"


class Object3D : public Object2D
{
public:

	Object3D();				// object3D constructor
//	Object3D(float Mass, float Ks, float Kd, float Press);
//	Object3D (float Mass, float Ks, float Kd);
	virtual ~Object3D();		// object3D destructor

	/*
	void Mouse(int, int, int, int);
	void Keyboard(unsigned char, int, int); 
	void SpecialKeys(int, int, int);
	void Rotated();
	*/

/*
	void ExternalForces();     // gravity force
	void PressureForces();     // pressure  
	void SpringForces();       // spring forces 
	void AccumulateForces();   // accumulate forces acted on 
	void Derivatives(float);   // Differential computation
*/

public:

	virtual void Draw();
	void Iteration();
	void nonunitsphere();
	//void GetClosestParticle();   // the Particle on the Object3D, which is cloest to the mouse pos

	//void GetParticles ();
	//void GetFace();

private:
	virtual void SetObject(void);					// model the object3D
	void Add_Structural_Spring(int index, int h, int t);	// model the inner or outer cirle with structural springs
	void Add_Radium_Spring(int index);				// add the radium springs with inner point i and outer point i 
	void Add_Shear_Spring(int index);		// add the left&right shear springs with inner point i and outer point i+1

	void Tetrahedron();				// draw the single shape
	void Pyramid3();
	void Pyramid4();

	Particle *pa, *pb, *pc;				// the three points subdivide each edge on the triangle face
	int iterations;					// the number of iteration for subdivision
};

#endif
