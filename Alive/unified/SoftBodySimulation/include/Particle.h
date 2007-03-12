#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

// Class Particle declaration
//##ModelId=45F4D797006F
class Particle
{
  public:

	//##ModelId=45F4D7970070
	Particle(Vector* R, float Mass) : mass(Mass)		 		// particle constructor with variables position and mass
	{		
		r = R;									// initialize Particle space position
	//	OneOverMass=1.0/mass;						
		dr = new Vector(0,0,0);							// initialize position in derivatives	
		dv = new Vector(0,0,0);							// initialize velocity in derivatives	
		f  = new Vector(0,0,0);							// initialize Particle space force
		v  = new Vector(0,0,0);							// initialize Particle space velocity
	}

	//##ModelId=45F4D7970073
	Particle()										// particle constructor with no variables
	{
		r  = new Vector(0,0,0);							// initialize Particle space position
		dr = new Vector(0,0,0);							// initialize position in derivatives	
		dv = new Vector(0,0,0);							// initialize velocity in derivatives	
		f  = new Vector(0,0,0);							// initialize Particle space force
		v  = new Vector(0,0,0);							// initialize Particle space velocity
		mass = MASS;
	}

	//##ModelId=45F4D7970074
	Particle(const Particle& p)							// particle constructor with variables position
	{
		mass = p.mass;

		r  = new Vector(0,0,0);							// initialize Particle space position
		r->x = p.r->x;
		r->y = p.r->y;
		r->z = p.r->z;
		
		dr = new Vector(0,0,0);							// initialize position in derivatives	
		dr->x = p.dr->x;
		dr->y = p.dr->y;
		dr->z = p.dr->z;

		dv = new Vector(0,0,0);							// initialize velocity in derivatives	
		dv->x = p.dv->x;
		dv->y = p.dv->y;
		dv->z = p.dv->z;

		f  = new Vector(0,0,0);							// initialize Particle space force
		f->x = p.f->x;
		f->y = p.f->y;
		f->z = p.f->z;

		v  = new Vector(0,0,0);							// initialize Particle space velocity
		v->x = p.v->x;
		v->y = p.v->y;
		v->z = p.v->z;
	}


	//##ModelId=45F4D797007F
	~Particle()										// particle destructor			
	{
		/*
		delete norm;
		delete dr;
		delete dv;
		delete f;
		delete v;
		*/
	}
	
	//##ModelId=45F4D7970080
	void ClearForce(void);								// reset forces at a Particle 		
//	void AccumuForce(Vector const &);
	//##ModelId=45F4D79700B2
	friend ostream& operator<<(ostream& os, const Particle& c);		//output operator


public:

	//##ModelId=45F4D7970082
	float mass;										// space Particle with mass 
	//##ModelId=45F4D797008E
	float OneOverMass;								// for computation
	//##ModelId=45F4D7970090
	Vector* r;										// Particle space position
	//##ModelId=45F4D7970095
	Vector* f;										// Particle space force
	//##ModelId=45F4D797009F
	Vector* v;										// Particle space velocity
	//##ModelId=45F4D79700A4
      Vector* dr;										// small change of position in derivatives
	//##ModelId=45F4D79700AE
	Vector* dv;										// small change of velocity in derivatives	
};

#endif
