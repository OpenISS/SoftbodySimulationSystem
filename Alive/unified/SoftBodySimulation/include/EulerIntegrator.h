#ifndef EULERINTEGRATOR_H
#define EULERINTEGRATOR_H

#include "Integrator.h"

//##ModelId=45F4D798009E
class EulerIntegrator : public Integrator
{
public:
	//##ModelId=45F4D79800AE
	EulerIntegrator(Object&);
	//##ModelId=45F4D79800B0
	virtual ~EulerIntegrator();

	//##ModelId=45F4D79800B2
	virtual void Derivatives(float, float);

protected:
	//##ModelId=45F4D79800BE
	void k1(int, float, float);
	//##ModelId=45F4D79800C2
	void ynew(int, float, float);

};

#endif /* EULERINTEGRATOR_H */
