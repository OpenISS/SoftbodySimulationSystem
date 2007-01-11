
#ifndef SPRING_H
#define SPRING_H


#include "global.h"
#include "Particle.h"
//#include "CollectionElement.h"

// Linear hooke Spring is built between two space Particles


class Spring //: public CollectionElement
// constructor
{
public:
	Spring(Particle *P1, Particle *P2,float Ks=KS, float Kd=KD):
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
		 }



		  Spring()
		  {
//		 sp1 = new Particle(0,0);				// head Particle of a Spring
//		 sp2 = new Particle(0,0);				// tail Particle of a Spring

			  
			  sp1=sp2=NULL;

	restLen=0;          // lenth when Fs = 0 (Hooke force)
	changePercent=0;    // percentage of spring length change
	maxAllowedDist=0;   // maximum distange allowed from the rest length
	ks=0;			// Spring constant
	kd=0;		// damping factor	
		  
		  }
	~Spring()
	{
		if(sp1!=NULL)
			delete sp1;

		if(sp2!=NULL)
			delete sp2;
	}
		  
      void InverseConstraints(void);     // for Inverse Dynamics Constraints
	//  void CalculateSpringForceM(void);  
	  void CalculateSpringForceT(void);
      //void CalculateSpringForceH(void);
	   
	    void setRestLen ()
		 {
//			cout<<"restLen!=0"<<endl; 
			 restLen = (*sp1->r - *sp2->r).getLength(); // static length
		//	 return restLen;
		 }
  
// operator "==" for STL  
	  
	  bool operator== (Spring const &s2)
	  {
			if(sp1->r == s2.sp1->r)
			if(sp2->r == s2.sp2->r)
				return true;

			if(sp1->r == s2.sp2->r)
			if(sp2->r == s2.sp1->r)
				return true;
			return false;
	  }


public:
	Particle *sp1;				// head Particle of a Spring
	Particle *sp2;				// tail Particle of a Spring
	
	float restLen;          // lenth when Fs = 0 (Hooke force)
	float changePercent;    // percentage of spring length change
	float maxAllowedDist;   // maximum distange allowed from the rest length
	float ks;				// Spring constant
	float kd;				// damping factor	
};


#endif