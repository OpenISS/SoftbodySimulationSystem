
#ifndef Face_H
#define Face_H

#include "global.h"
#include "Particle.h"

// Class Face is an element cell of 3D ball entire surface

class Face /*: public CollectionElement*/
{
public:
	Face(Particle *Ap1, Particle *Ap2, Particle *Ap3): 
	  fp1(Ap1), fp2(Ap2), fp3(Ap3)
	  {
		
   // constructor
//	  field = 0;
	  normal = new Vector(0,0,0);
	  force  = new Vector(0,0,0);	  
	  }

	 ~Face()
	{
	 delete fp1;
	 delete fp2;
	 delete fp3;
	 delete normal;
	 delete force;
	 
	 }

 void CalNormalNField(void);
	
public:	
	Particle	 *fp1;		 // first vertex 
	Particle	 *fp2;       // second vertex
	Particle	 *fp3;       // third vertex

	
//    float    field;		 // normal field
	Vector* normal;	 // triangle normal Vector
	Vector* force;		 // force on the triangle
};

#endif
