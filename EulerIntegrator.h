#ifndef EULERINTEGRATOR_H
#define EULERINTEGRATOR_H

#include "Integrator.h"


class EulerIntegrator : public Integrator
{
public:
    
    EulerIntegrator(Object&);        // constructor
    
    virtual ~EulerIntegrator();      // destructor

    
    virtual void Derivatives(float, float); // integrate all the particles on the object

protected:
    
    void k1(int, float, float);     // get the derivatives of velocity and position
    
    void ynew(int, float, float);   // get the new velocity and position

};

#endif /* EULERINTEGRATOR_H */
