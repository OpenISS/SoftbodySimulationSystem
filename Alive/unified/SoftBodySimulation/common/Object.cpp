#include <assert.h>

#include "Object.h"
#include "EulerIntegrator.h"
#include "MidpointIntegrator.h"
#include "RungeKutta4Integrator.h"

Object::Object()
{
	numParticles = 2;					//default particle number on the object
	numSprings = 1;						//default spring number on the object
	integrator = NULL;					//default integrator 
	integratorType = MIDPOINT;				//default integrator tpye is Euler
	dim = DIM1D;						//default object is 1D
	closest_i=0;			  		    // the point which is closest to mouse position
}

Object::~Object()
{

	delete integrator;
}

//==========================================================================  

void Object::SetParticles()				//model the particles on the object
{

	assert(false);
}

void Object::Add_Structural_Spring(int index, int head, int tail)
{
	assert(false);

}

//##############################################################################

void Object::SetObject()				//model the object
{
	
	SetParticles();						//model the particles on the object

}

//#############################################################################

void Object::setIntegratorType(integrator_type type)		//set the integrator tpye as user selects from the GUI
{
	
	this->integratorType = type;
}

//#############################################################################
//update the forces, velocity, and position of the particle on the object

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

		integrator->setDimension(dim);
	}

	integrator->integrate(deltaT, drag, xDrag, yDrag);
}
