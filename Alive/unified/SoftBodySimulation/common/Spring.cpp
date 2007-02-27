#include "Spring.h"



Spring::Spring(Particle *P1, Particle *P2,float Ks, float Kd):		// spring constructor with spring head, tail, and Ks, Kd
  sp1(P1), sp2(P2), ks(Ks), kd(Kd)
{												// *P1, *P2 Particles the srping two ends
												// Spring_ks is the Hooke constant
												// Spring_kd is the dampling constant

	if (restLen != 0)									//?????????????????????????????????????????
	{
	 restLen = (*sp1->r - *sp2->r).getLength(); 				// static length	
	}
	changePercent = 10.0;
	maxAllowedDist = (changePercent/1.0f)*restLen;
	type = SPRING_STRUCTURAL;							// default spring type is structural spring which
												// construct the object shape
}


Spring::Spring()										// spring constructor with no initial value
{
	sp1 = new Particle();								// head Particle of a Spring
	sp2 = new Particle();								// tail Particle of a Spring
	restLen = 0;          								// lenth when Fs = 0 (Hooke force)
	changePercent = 0;    								// percentage of spring length change
	maxAllowedDist = 0;   								// maximum distange allowed from the rest length
	ks = 0;										// Spring constant
	kd = 0;										// damping factor	
	type = SPRING_STRUCTURAL;							// default spring type is structural spring which
}												// construct the object shape

Spring::~Spring()										//spring destructor
{
/*	if(sp1 != NULL)
		delete sp1;

	if(sp2 != NULL)
		delete sp2;
*/
}
  
void Spring::setRestLen()
{
	restLen = (*sp1->r - *sp2->r).getLength(); 				// static length
}
