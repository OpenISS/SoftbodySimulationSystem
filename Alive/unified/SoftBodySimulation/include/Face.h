#ifndef FACE_H
#define FACE_H

#include "Particle.h"
#include "Spring.h"

// Class Face is an element cell of 3D ball entire surface
class Face
{
public:
/*	Face(Spring *Ap1, Spring *Ap2, Spring *Ap3): 
	  fp1(Ap1), fp2(Ap2), fp3(Ap3)*/
	Face(Particle *Ap1, Particle *Ap2, Particle *Ap3) :
	  fp1(Ap1), fp2(Ap2), fp3(Ap3)
	{
		normal = new Vector(0,0,0);
	}

	Face(Particle *Ap1, Particle *Ap2, Particle *Ap3, vector<Spring*> &springs) :
	  fp1(Ap1), fp2(Ap2), fp3(Ap3)
	{
		// constructor
		//	  field = 0;
		normal = new Vector(0,0,0);
//		force  = new Vector(0,0,0);
		
		//fp1

		fs1 = new Spring(Ap1, Ap2);
		fs2 = new Spring(Ap2, Ap3);
		fs3 = new Spring(Ap3, Ap1);

		springs.push_back(fs1);
		springs.push_back(fs2);
		springs.push_back(fs3);

	
	}

	~Face()
	{
//		delete fp1;
//		delete fp2;
//		delete fp3;
		delete normal;
	//	delete force;
	}

	void CalNormalNField(void);
	
public:	
///*
	Particle	 *fp1;		 // first vertex 
	Particle	 *fp2;       // second vertex
	Particle	 *fp3;       // third vertex*/
///*
	Spring	 *fs1;		 // first vertex 
	Spring	 *fs2;       // second vertex
	Spring	 *fs3;       // third vertex
//*/
	
//    float    field;		 // normal field
	Vector* normal;	 // triangle normal Vector
//	Vector* force;		 // force on the triangle
};

#endif
