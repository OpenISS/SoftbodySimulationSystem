#ifndef OBJECT_H
#define OBJECT_H

#include "Face.h"
#include "Spring.h"
#include "Integrator.h"
#include <vector>
using namespace std;

class Integrator;

//##ModelId=45F4D79701E6
class Object
{
protected:
    //##ModelId=45F4D79701E7
    int numParticles;                            // number of particles of the object
    //##ModelId=45F4D79701F5
    int numSprings;                            // number of springs of the object
    //##ModelId=45F4D79701F7
    Integrator* integrator;                        // integrator object
    //##ModelId=45F4D7970206
    integrator_type integratorType;                // different type of integrator, Euler, Midpoint, RK4

public:
    //##ModelId=45F4D797020B
    vector<Spring*>  inner_springs;                // the springs on the inner layer of the object
    //##ModelId=45F4D7970216
    vector<Spring*>  outer_springs;                // the springs on the outer layer of the object
    //##ModelId=45F4D7970227
    vector<Particle*>  inner_points;                // the particles on the inner layer of the object
    //##ModelId=45F4D7970235
    vector<Particle*>  outer_points;                // the particles on the outer layer of the object
    //##ModelId=45F4D7970246
    vector<Face*> inner_faces;                    // the surfaces on the inner layer of the object
    //##ModelId=45F4D797024B
    vector<Face*> outer_faces;                    // the surfaces on the outer layer of the object
    //##ModelId=45F4D7970254
    dimensionality dim;                        // dimension type to specify the object is 1D, 2D, or 3D

    //##ModelId=45F4D7970258
    int   closest_i ;                              // the closest point on the outer layer to mouse position

public:
    //##ModelId=45F4D7970263
    Object();                                // object constructor
    //##ModelId=45F4D7970264
    virtual ~Object();                        // object destructor

    //##ModelId=45F4D7970266
    int GetNumberOfParticles() { return numParticles; }    // get the number of particles of the object
    //##ModelId=45F4D7970267
    int GetNumberOfSprings() { return numSprings; }        // get the number of springs of the object
    
    //##ModelId=45F4D7970268
    void setIntegratorType(integrator_type type);        // choose the integrator
    //##ModelId=45F4D7970273
    Integrator* getIntegrator() {return integrator;}    // get the integrator type
    
    //##ModelId=45F4D7970274
    virtual void Update(float, bool = false, float = 0, float = 0);            //update the object about forces, velocity, position
    
    //##ModelId=45F4D7970284
    virtual void Draw(int, glm::mat4) = 0;                    // display the object
    //##ModelId=45F4D7970286
    virtual void FindClosestPoint(void) ;            // find the closet particle on th outer layer to mouse position

protected:
    //##ModelId=45F4D7970293
    virtual void SetParticles();                    // model the particles on the object
    //##ModelId=45F4D7970295
    virtual void SetObject();                    // model the object
    //##ModelId=45F4D7970297
    virtual void Add_Structural_Spring(int, int, int);    // construct the springs to model the object
};

#endif /* OBJECT_H */
