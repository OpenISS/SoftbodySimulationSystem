


#include "Spring.h"
#include "Vector.h"



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