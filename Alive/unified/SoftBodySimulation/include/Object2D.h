#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Object1D.h"
#include "global.h"

class Object2D : public Object1D
{
protected:
	float    pressure;							// pressure at each Particles on Object2D along its normal

public:

/*	Spring radium_springs[NUMSPRINGS];			// for radium springs between two circles 
	Spring shear_springs_left[NUMSPRINGS];		// for shear spring toward left
	Spring shear_springs_right[NUMSPRINGS];		// for right spring toward right
*/



	vector<Spring*>  radium_springs;
	vector<Spring*>  shear_springs_left;
	vector<Spring*>	 shear_springs_right;

public:

	Object2D();
	virtual ~Object2D();

	virtual void Draw();						//display the object 2D


	inline void setPressure(float pre){pressure = pre;}		// Set Pressure                                                                     
	inline float getPressure() {return(pressure);}			// Get Pressure   


private:
	virtual void SetObject(void);							//model the object

	void Add_Structural_Spring(int index, int h, int t);	//model the inner or outer cirle with structural springs

	void Add_Radium_Spring(int index);						//add the radium springs with inner point i and outer point i 
	void Add_Shear_Spring(int index, int h, int t );		//add the left shear springs with inner point i and outer point i+1
															//add the right shear springs with inner point i+1 and outer point i

	virtual void Add_Faces(int i, int i1, int imid);
	
};

#endif /* OBJECT2D_H */
