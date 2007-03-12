#ifndef SPRING_H
#define SPRING_H


#include "Particle.h"
// Class Spring is an element cell of 2D ball entire surface
// Linear hooke Spring is built between two space Particles

//##ModelId=45F4D79603CA
class Spring 
{
public:
	
	//##ModelId=45F4D79603CB
	Spring(Particle *P1, Particle *P2,float Ks=KS, float Kd=KD);		// constructor with variables
	//##ModelId=45F4D79603DE
	Spring();											// constructor with no variable
	//##ModelId=45F4D79603DF
	~Spring();											// destructor

	//##ModelId=45F4D79603E0
	void setRestLen();

public:
//protected:
	//##ModelId=45F4D79603E2
	Particle *sp1;										// head Particle of a Spring
	//##ModelId=45F4D7970004
	Particle *sp2;										// tail Particle of a Spring
	//##ModelId=45F4D7970008
	float restLen;										// length when spring force = 0 (Hooke force)
	//##ModelId=45F4D7970009
	float changePercent;									// percentage of spring length change
	//##ModelId=45F4D7970011
	float maxAllowedDist;									// maximum distaance allowed from the rest length
	//##ModelId=45F4D7970012
	float ks;											// Spring constant
	//##ModelId=45F4D7970013
	float kd;											// spring damping factor	
	//##ModelId=45F4D7970022
	Vector normal;										// normal vector at the spring of a object  
	//##ModelId=45F4D7970027
	spring_type type;										// different types of springs to construct the object, structural, radium  
};


#endif
