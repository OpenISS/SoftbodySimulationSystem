#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

// Class Particle declaration
class Particle
{
public:

	Particle(Vector* R, float Mass) : mass(Mass)
	{		
		r = R;
	  //mass=1;
//		cout<<"Mass. Particle: "<<mass<<endl;
		OneOverMass=1.0/mass;      // constructor	
		norm = new Vector(0,0,0);
		dr = new Vector(0,0,0);
		dv = new Vector(0,0,0);
//		norm = NULL;
//		dr = NULL;
//		dv = NULL;
//		f = NULL;
//		v = NULL;
		f = new Vector(0,0,0);
		v = new Vector(0,0,0);
	}

	Particle()
	{
		r = new Vector(0,0,0);
		norm = new Vector(0,0,0);
		dr = new Vector(0,0,0);
		dv = new Vector(0,0,0);
		f = new Vector(0,0,0);
		v = new Vector(0,0,0);

		/*
		//r = NULL;
		norm = NULL;
		dr = NULL;
		dv = NULL;
		f = NULL;
		v = NULL;
		*/
	}


	~Particle()
	{
		/*
		delete norm;
		delete dr;
		delete dv;
		delete f;
		delete v;
		*/
	}
	
	void ClearForce(void);   // reset forces at a Particle 		
	void AccumuForce(Vector const &);
	friend ostream& operator<<(ostream& os, const Particle& c);


public:

	float mass;         // space Particle with mass 
	float OneOverMass;  // for computation
	
	Vector* r;		    // Particle space position
	Vector* f;		    // Particle space force
	Vector* v;		    // Particle space velocity
    Vector* dr;		    // small change of position in derivatives
	Vector* dv;		    // small change of velocity in derivatives
	
	Vector* norm;	    // normal vector at the Particle on a ball
	
};

#endif
