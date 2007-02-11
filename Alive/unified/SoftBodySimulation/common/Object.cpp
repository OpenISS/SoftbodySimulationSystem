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
	integratorType = EULER;
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
	
	SetParticles();         // create point Object3D

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
		cout << "INTEGRATOR IS ABOUT TO BE INSTATIATED" << endl;

		switch(integratorType)
		{
			case EULER:
				integrator = new EulerIntegrator(*this);
				break;

	/*		case MIDPOINT:
				integrator = new MidpointIntegrator(*this);
				break;

			case RK4:
				integrator = new RungeKutta4Integrator(*this);
				break;
*/
			default:
				assert(false);
				return;
		}
	}

	integrator->integrate(deltaT, drag, xDrag, yDrag);
}
