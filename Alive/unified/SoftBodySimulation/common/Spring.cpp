#include "Spring.h"


// constructor
Spring::Spring(Particle *P1, Particle *P2,float Ks, float Kd):
  sp1(P1), sp2(P2), ks(Ks), kd(Kd)
{
	// *P1, *P2 Particles the srping two ends
	// Spring_ks is the Hooke constant
	// Spring_kd is the dampling constant

	/*	 if (restLen != 0)
	{
	//			cout<<"restLen!=0"<<endl; 
	 restLen = (*sp1->r - *sp2->r).getLength(); // static length	
	}
	changePercent = 10.0;
	maxAllowedDist = (changePercent/1.0f)*restLen;
	*/
	type = SPRING_STRUCTURAL;
}


Spring::Spring()
{
	//		 sp1 = new Particle(0,0);				// head Particle of a Spring
	//		 sp2 = new Particle(0,0);				// tail Particle of a Spring


	sp1=sp2=NULL;

	restLen=0;          // lenth when Fs = 0 (Hooke force)
	changePercent=0;    // percentage of spring length change
	maxAllowedDist=0;   // maximum distange allowed from the rest length
	ks=0;			// Spring constant
	kd=0;		// damping factor	

	type = SPRING_STRUCTURAL;
}

Spring::~Spring()
{
	if(sp1!=NULL)
		delete sp1;

	if(sp2!=NULL)
		delete sp2;
}
  
void Spring::setRestLen()
{
//			cout<<"restLen!=0"<<endl; 
	restLen = (*sp1->r - *sp2->r).getLength(); // static length
//	restLen = (*sp2->r - *sp1->r).getLength(); // static length
//	 return restLen;
}

// operator "==" for STL  

bool Spring::operator== (Spring const &s2)
{
	if(sp1->r == s2.sp1->r)
	if(sp2->r == s2.sp2->r)
		return true;

	if(sp1->r == s2.sp2->r)
	if(sp2->r == s2.sp1->r)
		return true;

	return false;
}

void Spring::InverseConstraints(void)  
{

/*	Vector*	r12 = new Vector();			// distance Vector between 2 Points
	float	r12d;			// value of the distance Vector length			
	float	deltaLen;   	// actual vector length - rest length
	
// calculate distance of Spring start and end Points

	r12		 = (sp1->r - sp2->r);			// distance Vector
	r12d	 = r12.getLength();			// Vector length, defined in "Vector.h"
    deltaLen = (r12d - restLen);

	if(deltaLen > maxAllowedDist)  // if the shift is beyound the allowed length
	{		
	  deltaLen -= maxAllowedDist;  // shirk it by a maxAllowed distance
	  r12.Normalize();             // Normalize this vector
	  r12 = r12 * (deltaLen/2.0f); // delta vector to be added to the original vector

	  *sp1->r = *sp1->r + r12;       // Apply the constraint tp sp1
	  *sp2->r = *sp2->r - r12;       // Apply the constraint to sp2
	}
*/
}


/*
 void Spring::CalculateSpringForceM(void) // for tangent springs
{
	Vector	r12;			// distance Vector between 2 Points
	float	r12d;			// distance Vector length
	Vector	v12;			// velocity Vector between 3 velocities		
	float	f;				// acting forces
	Vector	F;				// final force Vector
	
// calculate distance of Spring start and end Points

	r12		=	(sp1->r - sp2->r);			// distance Vector
	r12d	=	 r12.getLength();			// Vector length, defined in "Vector.h"


	if(r12d != 0)  // not in same Point position
	{		
	  v12 = (sp1->v - sp2->v);                         // velocity Vector difference 	  				
		f = (r12d - restLen) * KS + (v12 * r12) * KD / r12d;	        // scalar	
		F = (r12 * (1.0f/r12d)) * f;                   // and finally Vector force
	}
	
	sp1.AccumuForce(-1.0 * F);  	// Accumulate force on Point p1
	sp2.AccumuForce(1.0 * F);      // Accumulate force on Point p2
}
*/
 void Spring::CalculateSpringForceT(void) // for top end springs
{
/*	Vector	r12;			// distance Vector between 2 Points
	float	r12d;			// distance Vector length
	Vector	v12;			// velocity Vector between 3 velocities		
	float	f;				// acting forces
	Vector	F;				// final force Vector
	
// calculate distance of Spring start and end Points

	r12		=	(sp1->r - sp2->r);			// distance Vector
	r12d	=	 r12.getLength();			// Vector length, defined in "Vector.h"


	if(r12d != 0)  // not in same Point position
	{		
	  v12 = (sp1->v - sp2->v);                         // velocity Vector difference 	  				
		f = (r12d - restLen) * ks + (v12 * r12) * kd / r12d;	        // scalar	
		F = (r12 * (1.0f/r12d)) *2*f;          //  Vector force / N
	}
	
	sp1->AccumuForce(-1.0 * F);  	// Accumulate force on Point p1
	sp2->AccumuForce(1.0 * F);      // Accumulate force on Point p2*/
}



/* void Spring::CalculateSpringForceH(void) // for horizonal springs
{
	Vector	r12;			// distance Vector between 2 Points
	float	r12d;			// distance Vector length
	Vector	v12;			// velocity Vector between 3 velocities		
	float	f;				// acting forces
	Vector	F;				// final force Vector
	
// calculate distance of Spring start and end Points

	r12		=	(sp1->r - sp2->r);			// distance Vector
	r12d	=	 r12.getLength();			// Vector length, defined in "Vector.h"


	if(r12d != 0)  // not in same Point position
	{		
	  v12 = (sp1->v - sp2->v);                         // velocity Vector difference 	  				
		f = (r12d - restLen) * KS + (v12 * r12) * KD / r12d;	        // scalar	
		F = (r12 * (1.0f/r12d)) * (f/10.0);          //  Vector force / N
	}
	
	sp1->AccumuForce(-1.0 * F);  	// Accumulate force on Point p1
	sp2->AccumuForce(1.0 * F);      // Accumulate force on Point p2
}

*/