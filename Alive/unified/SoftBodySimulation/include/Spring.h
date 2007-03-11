#ifndef SPRING_H
#define SPRING_H


#include "Particle.h"
// Class Spring is an element cell of 2D ball entire surface
// Linear hooke Spring is built between two space Particles

class Spring 
{
public:
	
	Spring(Particle *P1, Particle *P2,float Ks=KS, float Kd=KD);		// constructor with variables
	Spring();											// constructor with no variable
	~Spring();											// destructor

	void setRestLen();

public:
//protected:
	Particle *sp1;										// head Particle of a Spring
	Particle *sp2;										// tail Particle of a Spring
	float restLen;										// length when spring force = 0 (Hooke force)
	float changePercent;									// percentage of spring length change
	float maxAllowedDist;									// maximum distaance allowed from the rest length
	float ks;											// Spring constant
	float kd;											// spring damping factor	
	Vector normal;										// normal vector at the spring of a object  
	spring_type type;										// different types of springs to construct the object, structural, radium  
};


#endif