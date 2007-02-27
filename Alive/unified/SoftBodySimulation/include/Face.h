#ifndef FACE_H
#define FACE_H

#include "Particle.h"
#include "Spring.h"

// Class Face is an element cell of 3D ball entire surface
class Face
{
public:

	//face constructor with three particles point to the three points on each face, for 2D
	Face(Particle *Ap1, Particle *Ap2, Particle *Ap3) :
           fp1(Ap1), fp2(Ap2), fp3(Ap3)
	{
		normal = new Vector(0,0,0);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////

	// face constructor with three particles point to the three points on each face, 
	// and store the spring information into the spring vector for 3D
	Face(Particle *Ap1, Particle *Ap2, Particle *Ap3, vector<Spring*> &springs) :   
	    fp1(Ap1), fp2(Ap2), fp3(Ap3)
	{
		normal = new Vector(0,0,0);					// normal vecotr for face
//		force  = new Vector(0,0,0);
		
		fs1 = new Spring(Ap1, Ap2);					// first spring points to particle p1&p2
		fs2 = new Spring(Ap2, Ap3);					// second spring points to particle p2&p3
		fs3 = new Spring(Ap3, Ap1);					// third spring points to particle p3&p1


		bool a = false, b = false, c = false;			// the three new particles have not existed 

		for(int o = 0; o < springs.size(); o++)			// for all the spring in the requested spring vecotr
		{
			if								// if the spring exist with particle p1&p2 
			(
				   springs[o]->sp1 == Ap1
				&& springs[o]->sp2 == Ap2
			)								
			{
				   delete fs1;					// delete the builded spring fs1
				   fs1 = springs[o];				// the new spring will point to the existed spring
				   a = true;					// set the spring's particles have existed
			}

			if								// if the spring exist with particle p2&p3 
			(
				   springs[o]->sp1 == Ap2
				&& springs[o]->sp2 == Ap3
			)
			{
				   delete fs2;					// delete the builded spring fs2
				   fs2 = springs[o];				// the new spring will point to the existed spring
			 	   b = true;					// set the spring's particles have existed
			}

			if								// if the spring exist with particle p3&p1 
			(
				   springs[o]->sp1 == Ap3
				&& springs[o]->sp2 == Ap1
			)
			{
				   delete fs3;					// delete the builded spring fs3
				   fs3 = springs[o];				// the new spring will point to the existed spring
				   c = true;					// set the spring's particles have existed
			}
		}

		// The new points are added to the general collection of points
		if(!a) springs.push_back(fs1);
		if(!b) springs.push_back(fs2);
		if(!c) springs.push_back(fs3);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
	~Face()									// face destructor 
	{
//		delete fp1;
//		delete fp2;
//		delete fp3;
		delete normal;
//		delete force;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////
	void CalNormalNField(void);						// Calculate normal vector to a triangle and its field 	
public:	
	Spring	 *fs1;		 					// first spring on the face 
	Spring	 *fs2;       						// second spring on the face
	Spring	 *fs3;   							// third spring on the face 
//    float    	field;							// normal field
	Vector* 	normal;							// triangle normal Vector
//	Vector* 	force;							// force on the triangle
};

#endif
