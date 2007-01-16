#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Object1D.h"

#define NUMPOINTS   12
#define NUMSPRINGS  NUMPOINTS
#define DEFAULTPRESSURE 25.0
#define MASS 1.0f           // point mass on the rings = 5.0
#define RING_RADIUS 0.5f	// default radius of the ball

class Object2D : public Object1D
{
protected:
	float    pressure;			  // pressure at each Particles on Object3D alone its normal
	float    radius;              // radius of the 2D/3D Object


	//Particle inner_points[NUMPOINTS];    // for inner circle Particles 
	Particle inner_K0[NUMPOINTS];        // K0
	Particle inner_K1[NUMPOINTS];        // K1
	Particle inner_K2[NUMPOINTS];        // K2
	Particle inner_K3[NUMPOINTS];        // K3
	Particle inner_K4[NUMPOINTS];        // K4

//	Particle outer_points[NUMPOINTS];  // for outer circle Particles + 1 mouse Particle
	Particle outer_K0[NUMPOINTS];  // K0
	Particle outer_K1[NUMPOINTS];  // K1
	Particle outer_K2[NUMPOINTS];  // K2
	Particle outer_K3[NUMPOINTS];  // K3
	Particle outer_K4[NUMPOINTS];  // K4

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Spring inner_springs[NUMSPRINGS];       // for point springs on inner circle
//	Spring outer_springs[NUMSPRINGS];     // for point springs on outer circle



public:
	Spring radium_springs[NUMSPRINGS];	   // for radium springs between two circles 

	Spring shear_springs_left[NUMSPRINGS];  // for shear spring toward left
	Spring shear_springs_right[NUMSPRINGS]; // for right spring toward right
	Object2D();
	virtual ~Object2D();

	virtual void Draw();


	inline void setPressure(float pre){pressure = pre;} // Set Pressure                                                                     
	inline float getPressure() {return(pressure);}      // Get Pressure   


private:
	void Add_Tangent_Spring(int index, int h, int t);
//	void Add_Tangent_Spring(int index, Particle* h, Particle* t);
	void Add_Radium_Spring(int index);
	void Add_Shear_Spring(int index, int h, int t );
//	void Add_Shear_Spring(int index, Particle* h, Particle* t);

	void CreateRing(void);
};

#endif /* OBJECT2D_H */
