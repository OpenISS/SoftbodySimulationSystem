
#include "Particle.h"


// class Particle number functions

void Particle::ClearForce(void)   // reset forces at a Particle 	
{
	f = new Vector(0,0,0);    // A force vector with all coordinates equal zero
} 

void Particle::AccumuForce(Vector const &force) // Adding a force vector
{
	*f = *f + force;
}


ostream& operator<<(ostream& os, const Particle& c)
{
 
  //os<<c.mass;
  
	os<<c.f->x;
	os<<c.f->y;
	os<<c.f->z;

	os<<c.mass;
	os<<c.OneOverMass;  // for computation
	
	os<<c.r->x;		    // Particle space position
	os<<c.r->y;
	os<<c.r->z;
	
	os<<c.v->x;
	os<<c.v->y;
	os<<c.v->z;  // Particle space velocity

    os<<c.dr->x;
	os<<c.dr->y;
	os<<c.dr->z; // small change of position in derivatives
	
	os<<c.dv->x;	
	os<<c.dv->y;  // small change of velocity in derivatives
	os<<c.dv->z;

	os<<c.norm->x;
	os<<c.norm->y;
	os<<c.norm->z;	    // normal vector at the Particle on a ball
	
	return os; //Always return stream object.
}
