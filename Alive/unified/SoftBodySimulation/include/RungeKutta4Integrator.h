#ifndef RUNGEKUTTA4INTEGRATOR_H
#define RUNGEKUTTA4INTEGRATOR_H

#include "MidpointIntegrator.h"

//##ModelId=45F4D7970030
class RungeKutta4Integrator : public MidpointIntegrator
{
public:
	//##ModelId=45F4D7970041
	RungeKutta4Integrator(Object&);
	//##ModelId=45F4D7970043
	~RungeKutta4Integrator();

protected:

	//##ModelId=45F4D7970044
	void k4(int, float, float);
	//##ModelId=45F4D7970050
	void k3(int, float, float);
//	void k2(int, float, float);
	//##ModelId=45F4D7970054
	void ynew(int, float, float);
};

#endif /* RUNGEKUTTA4INTEGRATOR_H */
