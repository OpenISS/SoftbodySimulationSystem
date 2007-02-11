#ifndef OBJECT1D_H
#define OBJECT1D_H

#include "Object.h"

class Object1D : public Object
{
public:
	Object1D();
	virtual ~Object1D();

	virtual void Draw();

	void FindClosestPoint(void);
private:	
	void Add_Structural_Spring(int index, int head, int tail);
	virtual void SetObject();


};

#endif /* OBJECT1D_H */
