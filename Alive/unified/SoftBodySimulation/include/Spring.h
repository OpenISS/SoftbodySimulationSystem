
#ifndef SPRING_H
#define SPRING_H


#include "global.h"
#include "Particle.h"

// Linear hooke Spring is built between two space Particles

enum spring_type { SPRING_RADIUM, SPRING_STRUCTURAL, SPRING_SHEAR };


class Spring 
{
public:

	// constructor
	Spring(Particle *P1, Particle *P2,float Ks=KS, float Kd=KD);
	Spring();
	~Spring();

	void InverseConstraints(void);     // for Inverse Dynamics Constraints
	//  void CalculateSpringForceM(void);  
	void CalculateSpringForceT(void);
	//void CalculateSpringForceH(void);

	void setRestLen();

	bool operator== (Spring const &s2);


public:
//protected:
	Particle *sp1;				// head Particle of a Spring
	Particle *sp2;				// tail Particle of a Spring
	
	float restLen;          // lenth when Fs = 0 (Hooke force)
	float changePercent;    // percentage of spring length change
	float maxAllowedDist;   // maximum distange allowed from the rest length
	float ks;				// Spring constant
	float kd;				// damping factor	

	//float nx,ny;            	// normal vector at the spring area   
	Vector normal;

   	int n;			        	// radium spring index

	spring_type type;
};


#endif