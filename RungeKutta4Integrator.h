#ifndef RUNGEKUTTA4INTEGRATOR_H
#define RUNGEKUTTA4INTEGRATOR_H

#include "MidpointIntegrator.h"


class RungeKutta4Integrator : public MidpointIntegrator
{
public:
    
    RungeKutta4Integrator(Object&);// constructor
    
    ~RungeKutta4Integrator();// destructor


protected:

    void k3(int, float, float);// 3rd integrate to get the derivatives of velocity and position

    void k4(int, float, float);// 4th integrate to get the derivatives of velocity and position
    
    void ynew(int, float, float);// get the new velocity and position
};

#endif /* RUNGEKUTTA4INTEGRATOR_H */
