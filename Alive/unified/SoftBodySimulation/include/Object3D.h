#ifndef OBJECT3D_H
#define OBJECT3D_H


#include "Particle.h"
#include "Spring.h"

#include "Object2D.h"


class Object3D : public Object2D
{
public:

	Object3D();
//	Object3D(float Mass, float Ks, float Kd, float Press);
//	Object3D (float Mass, float Ks, float Kd);
	virtual ~Object3D();
             	         
			  


/*	
 void SetSprings();   // set springs on horizontal planes, connect Particles
 void SetTriPlanes();      // set triangle faces on side surfaces
 void SetObject();           // Then, make the Object3D object
*/
						   
	

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

//	void GetClosestParticle();   // the Particle on the Object3D, which is cloest to the mouse pos

//void GetParticles ();
//void GetFace();

private:
  //  float ks, kd;

 //   int Bmass;
	virtual void SetObject(void);	
	void Add_Structural_Spring(int index, int h, int t);	//model the inner or outer cirle with structural springs
	Particle *pa, *pb, *pc;

   // vector<Spring*>  spring; 
//	vector<Particle*> Object3DParticles;

	//int static npoints=6;
	int iterations;
};

#endif
