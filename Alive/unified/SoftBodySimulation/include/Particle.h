#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector.h"

// Class Particle declaration
class Particle
{
public:

	Particle(Vector* R, float Mass) : mass(Mass)		 // particle constructor with variables position and mass
	{		
		cout<<"call me now--------------"<<endl;
		r = R;
	
	
	//	OneOverMass=1.0/mass;						
		dr = new Vector(0,0,0);
		dv = new Vector(0,0,0);
		f  = new Vector(0,0,0);
		v  = new Vector(0,0,0);
	}

	Particle()											// particle constructor with variables position and mass
	{
		r  = new Vector(0,0,0);
		dr = new Vector(0,0,0);
		dv = new Vector(0,0,0);
		f  = new Vector(0,0,0);
		v  = new Vector(0,0,0);
	}

	Particle(const Particle& p)											// particle constructor with variables position and mass
	{
		mass = p.mass;

		r  = new Vector(0,0,0);
		r->x = p.r->x;
		r->y = p.r->y;
		r->z = p.r->z;
		
		dr = new Vector(0,0,0);
		dr->x = p.dr->x;
		dr->y = p.dr->y;
		dr->z = p.dr->z;



		dv = new Vector(0,0,0);
		dv->x = p.dv->x;
		dv->y = p.dv->y;
		dv->z = p.dv->z;

		f  = new Vector(0,0,0);
		f->x = p.f->x;
		f->y = p.f->y;
		f->z = p.f->z;

		v  = new Vector(0,0,0);
		v->x = p.v->x;
		v->y = p.v->y;
		v->z = p.v->z;
	}


	~Particle()											// particle destructor			
	{
		/*
		delete norm;
		delete dr;
		delete dv;
		delete f;
		delete v;
		*/
	}
	
	void ClearForce(void);								// reset forces at a Particle 		
//	void AccumuForce(Vector const &);
	friend ostream& operator<<(ostream& os, const Particle& c);


public:

	float mass;					// space Particle with mass 
	float OneOverMass;			// for computation
	
	Vector* r;					// Particle space position
	Vector* f;					// Particle space force
	Vector* v;					// Particle space velocity
    Vector* dr;					// small change of position in derivatives
	Vector* dv;					// small change of velocity in derivatives	
};

#endif
