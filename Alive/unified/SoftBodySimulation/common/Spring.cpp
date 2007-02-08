#include "Spring.h"



Spring::Spring(Particle *P1, Particle *P2,float Ks, float Kd):		// constructor
  sp1(P1), sp2(P2), ks(Ks), kd(Kd)
{
	  cout<<"spring construcotr1"<<endl;
	// *P1, *P2 Particles the srping two ends
	// Spring_ks is the Hooke constant
	// Spring_kd is the dampling constant

		 if (restLen != 0)
	{
	//			cout<<"restLen!=0"<<endl; 
	 restLen = (*sp1->r - *sp2->r).getLength(); // static length	
	}
	changePercent = 10.0;
	maxAllowedDist = (changePercent/1.0f)*restLen;
	
	type = SPRING_STRUCTURAL;
}


Spring::Spring()
{

			 sp1 = new Particle(0,0);				// head Particle of a Spring
			 sp2 = new Particle(0,0);				// tail Particle of a Spring


	restLen = 0;          // lenth when Fs = 0 (Hooke force)
	changePercent = 0;    // percentage of spring length change
	maxAllowedDist = 0;   // maximum distange allowed from the rest length
	ks = 0;			// Spring constant
	kd = 0;		// damping factor	

	type = SPRING_STRUCTURAL;
}

Spring::~Spring()
{
/*	if(sp1 != NULL)
		delete sp1;

	if(sp2 != NULL)
		delete sp2;
*/
}
  
void Spring::setRestLen()
{
	cout<<"spring setrestlen"<<endl;
//			cout<<"restLen!=0"<<endl; 
	restLen = (*sp1->r - *sp2->r).getLength(); // static length
//	restLen = (*sp2->r - *sp1->r).getLength(); // static length
//	 return restLen;
}
