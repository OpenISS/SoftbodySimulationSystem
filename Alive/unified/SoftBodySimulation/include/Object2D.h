#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Object1D.h"
#include "global.h"

//##ModelId=45F4D797013A
class Object2D : public Object1D
{
protected:
	//##ModelId=45F4D797014A
	float    pressure;					// pressure at each Particles on Object2D along its normal
public:
	//##ModelId=45F4D797015B
	vector<Spring*>  radium_springs;				// for radium springs between two circles 
	//##ModelId=45F4D7970160
	vector<Spring*>  shear_springs_left;			// for shear spring toward left
	//##ModelId=45F4D797016A
	vector<Spring*>  shear_springs_right;			// for right spring toward right

public:

	//##ModelId=45F4D797016E
	Object2D();								// constructor object2D
	//##ModelId=45F4D7970178
	virtual ~Object2D();						// destructor object2D

	//##ModelId=45F4D797017A
	virtual void Draw();						// display the object 2D
	//##ModelId=45F4D797017C
	inline void setPressure(float pre){pressure = pre;}	// Set Pressure                                                                     
	//##ModelId=45F4D797017E
	inline float getPressure() {return(pressure);}		// Get Pressure   

private:
	//##ModelId=45F4D797017F
	virtual void SetObject(void);					// model the object2D
	//##ModelId=45F4D797018A
	void Add_Structural_Spring(int index, int h, int t);	// model the inner or outer cirle with structural springs
	//##ModelId=45F4D7970198
	void Add_Radium_Spring(int index);				// add the radium springs with inner point i and outer point i 
	//##ModelId=45F4D797019A
	void Add_Shear_Spring(int index, int h, int t );	// add the left shear springs with inner point i and outer point i+1										//add the right shear springs with inner point i+1 and outer point i
	//##ModelId=45F4D79701A7
	virtual void Add_Faces(int i, int i1, int imid);	// add the triangle surface to object2D
	
};

#endif /* OBJECT2D_H */
