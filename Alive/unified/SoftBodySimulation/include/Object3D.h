#ifndef OBJECT3D_H
#define OBJECT3D_H


#include "Particle.h"
#include "Spring.h"

//#define M 8    // # of tangent circles along Y-axis
//#define N 6   // # of Particles on each of tangent plane


#include "Object2D.h"


class Object3D : public Object2D
{
public:

	Object3D (float Mass, float Ks, float Kd, float Press)
	{
		pressure=Press;
		ks=Ks;
		kd=Kd;
		Bmass=Mass;

		pa=new Particle(new Vector(0,0,0), Bmass);
		pb=new Particle(new Vector(0,0,0), Bmass);
		pc=new Particle(new Vector(0,0,0), Bmass);

	/*	pa=new Particle();
		pb=new Particle();
		pc=new Particle();*/

		//Collection* someone.getInstance() -> getCurrentCollectionAdapter();
	     
	}

	Object3D (float Mass, float Ks, float Kd)
	{
		pressure=0;
		ks=Ks;
		kd=Kd;
		Bmass=Mass;

	/*	pa=new Particle(new Vector(0,0,0), Bmass);
		pb=new Particle(new Vector(0,0,0), Bmass);
		pc=new Particle(new Vector(0,0,0), Bmass);
*/
	/*	pa=new Particle();
		pb=new Particle();
		pc=new Particle();*/

		//Collection* someone.getInstance() -> getCurrentCollectionAdapter();
	     
	}

	~Object3D()
	{
/*	delete pa;
	delete pb;
	delete pc;
*/	}
             	         

			  
	
	void SetParticles();         // create Particle Object3D
/*	
 void SetSprings();   // set springs on horizontal planes, connect Particles
 void SetTriPlanes();      // set triangle faces on side surfaces
 void SetObject();           // Then, make the Object3D object
*/
						   
	void GetClosestParticle();   // the Particle on the Object3D, which is cloest to the mouse pos
 
	void Mouse(int, int, int, int);
	void Motion(int, int); 
	void Keyboard(unsigned char, int, int); 
	void SpecialKeys(int, int, int);
	void Rotated();

/*
	void ExternalForces();     // gravity force
	void PressureForces();     // pressure  
	void SpringForces();       // spring forces 
 
	void AccumulateForces();   // accumulate forces acted on 
	void Derivatives(float);   // Differential computation
*/

	void Draw();


//void GetParticles ();
//void GetFace();

private:
    float ks, kd;

    int Bmass;

	Particle   *pa,*pb,*pc;

    vector<Spring*>  spring; 
	vector<Particle*> Object3DParticles;

	//Collection* Object3DParticles;
};

#endif
