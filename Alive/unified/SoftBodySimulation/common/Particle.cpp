#include "Particle.h"


// class Particle number functions

//##ModelId=45F4D7970080
void Particle::ClearForce(void)					// reset forces at a Particle 	
{
	
	if(f == NULL)
	{
		f = new Vector(0,0,0);					// A force vector with all coordinates equal zero
	}
	else
	{
		f->x = 0;
		f->y = 0;
		f->z = 0;
	}
} 


ostream& operator<<(ostream& os, const Particle& c)		// output operator
{
 
  //os<<c.mass;
  
	os<<c.f->x;
	os<<c.f->y;
	os<<c.f->z;

	os<<c.mass;
	os<<c.OneOverMass;  						// for computation
	
	os<<c.r->x;		    						// Particle space position
	os<<c.r->y;
	os<<c.r->z;
	
	os<<c.v->x;								// Particle space velocity
	os<<c.v->y;
	os<<c.v->z;  			

    	os<<c.dr->x;							// small change of position in derivatives
	os<<c.dr->y;
	os<<c.dr->z; 			
	
	os<<c.dv->x;							// small change of velocity in derivatives
	os<<c.dv->y;  			
	os<<c.dv->z;

	return os; 								// Always return stream object.
}
