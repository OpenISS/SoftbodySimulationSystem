#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Object1D.h"

class Object2D : public Object1D
{
protected:
	float    pressure;			  // pressure at each Particles on Object3D alone its normal

public:

	Spring radium_springs[NUMSPRINGS];	   // for radium springs between two circles 
	Spring shear_springs_left[NUMSPRINGS];  // for shear spring toward left
	Spring shear_springs_right[NUMSPRINGS]; // for right spring toward right

public:

	Object2D();
	virtual ~Object2D();

	virtual void Draw();


	inline void setPressure(float pre){pressure = pre;} // Set Pressure                                                                     
	inline float getPressure() {return(pressure);}      // Get Pressure   


private:
	void Add_Structural_Spring(int index, int h, int t);

	void Add_Radium_Spring(int index);
	void Add_Shear_Spring(int index, int h, int t );


	virtual void SetObject(void);
};

#endif /* OBJECT2D_H */
