#ifndef OBJECT1D_H
#define OBJECT1D_H

#include "Object.h"

class Object1D : public Object
{
public:
	Object1D();
	virtual ~Object1D();

	virtual void Draw();


private:	
	void Add_Tangent_Spring(int index, int head, int tail);
	void CreateOneD();
};

#endif /* OBJECT1D_H */
