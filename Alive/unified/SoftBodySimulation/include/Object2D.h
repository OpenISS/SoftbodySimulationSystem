#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Object1D.h"

class Object2D : public Object1D
{
protected:
	float    pressure;			  // pressure at each Particles on Object3D alone its normal
	float    radius;              // radius of the 2D/3D Object


public:

	Object2D();
	virtual ~Object2D();

	virtual void Draw();


	inline void setPressure(float pre){pressure = pre;} // Set Pressure                                                                     
	inline float getPressure() {return(pressure);}      // Get Pressure   

};

#endif /* OBJECT2D_H */
