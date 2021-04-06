#ifndef OBJECT3D_H
#define OBJECT3D_H


#include "Particle.h"
#include "Spring.h"

#include "Object2D.h"


//##ModelId=45F4D79700EC
class Object3D : public Object2D
{
public:

	//##ModelId=45F4D79700EE
	Object3D();				// object3D constructor
//	Object3D(float Mass, float Ks, float Kd, float Press);
//	Object3D (float Mass, float Ks, float Kd);
	//##ModelId=45F4D79700FB
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

	//##ModelId=45F4D79700FD
	virtual void Draw();
	//##ModelId=45F4D79700FF
	void Iteration();
	//##ModelId=45F4D7970100
	void nonunitsphere();
	//void GetClosestParticle();   // the Particle on the Object3D, which is cloest to the mouse pos

	//void GetParticles ();
	//void GetFace();

private:
	//##ModelId=45F4D7970101
	virtual void SetObject(void);					// model the object3D
	//##ModelId=45F4D797010B
	void Add_Structural_Spring(int index, int h, int t);	// model the inner or outer cirle with structural springs
	//##ModelId=45F4D797010F
	void Add_Radium_Spring(int index);				// add the radium springs with inner point i and outer point i 
	//##ModelId=45F4D797011B
	void Add_Shear_Spring(int index);		// add the left&right shear springs with inner point i and outer point i+1

	//##ModelId=45F4D797011D
	void Tetrahedron();				// draw the single shape
	//##ModelId=45F4D797011E
	void Pyramid3();
	//##ModelId=45F4D797011F
	void Pyramid4();

	Particle *pa, *pb, *pc;				// the three points subdivide each edge on the triangle face
	//##ModelId=45F4D797012A
	int iterations;					// the number of iteration for subdivision
};

#endif
