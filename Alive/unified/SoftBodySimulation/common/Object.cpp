#include <assert.h>

#include "Object.h"
#include "EulerIntegrator.h"
#include "MidpointIntegrator.h"
#include "RungeKutta4Integrator.h"

Object::Object()
{
	numParticles = 2;
	numSprings = 1;
	integrator = NULL;
	integratorType = RK4;
}

Object::~Object()
{
	delete integrator;
}

//==========================================================================  

void Object::SetParticles() // M*N horizonal springs
{
	assert(false);
}


//##############################################################################

void Object::SetObject()
{
	cout<<"set points"<<endl;
	SetParticles();         // create point Object3D

//SetNormals();
 
// SetTriPlanes();      // set triangle faces on side surfaces
//	SetSprings();   // set springs on horizontal planes, connect points
 //iteration();  
 /*  Object3DParticles=t_Object3DParticles;

  Face=t_Face;*/
}

//#############################################################################

void Object::setIntegratorType(integrator_type type)
{
	this->integratorType = type;
}

void Object::Update(float deltaT, bool drag, float xDrag, float yDrag)
{
	if(integrator == NULL)
	{
		switch(integratorType)
		{
			case EULER:
				integrator = new EulerIntegrator(*this);
				break;

			case MIDPOINT:
				integrator = new MidpointIntegrator(*this);
				break;

			case RK4:
				integrator = new RungeKutta4Integrator(*this);
				break;

			default:
				assert(false);
				return;
		}
	}

	integrator->integrate(deltaT, drag, xDrag, yDrag);
}
