#ifndef MIDPOINTINTEGRATOR_H
#define MIDPOINTINTEGRATOR_H

#include "EulerIntegrator.h"

//##ModelId=45F4D79702B1
class MidpointIntegrator : public EulerIntegrator
{
public:
	//##ModelId=45F4D79702B3
	MidpointIntegrator(Object&);
	//##ModelId=45F4D79702B5
	~MidpointIntegrator();

protected:

	//##ModelId=45F4D79702B6
	void k2(int, float, float);
	//##ModelId=45F4D79702C4
	void ynew(int, float, float);
};

#endif /* MIDPOINTINTEGRATOR_H */
