#ifndef OBJECT1D_H
#define OBJECT1D_H

#include "Object.h"

class Object1D : public Object
{
public:
	Object1D();					// object1D constructor
	virtual ~Object1D();			// object1D destructor
	virtual void Draw();			// display object1D
//	virtual void FindClosestPoint(void);

private:	
	//model the object1D with structural spring
	void Add_Structural_Spring(int index, int head, int tail);
protected:
	virtual void SetObject();		// construct the object1D
};

#endif /* OBJECT1D_H */
