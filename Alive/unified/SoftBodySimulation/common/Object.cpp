#include <assert.h>

#include "Object.h"
#include "EulerIntegrator.h"
#include "MidpointIntegrator.h"
#include "RungeKutta4Integrator.h"

Object::Object()
{
	NUMP = 2;
	NUMS = 1;
	integrator = NULL;
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

void Object::SetSprings() // M*N horizonal springs
{   
/*	      int i;

   for (i=0; i<face.size(); i++) // On each horizonal plane, N tangent springs
		{
	     
		    spring.push_back(Spring(face[i].fp1, face[i].fp2,ks,kd));     // row i with offset j
			spring.push_back(Spring(face[i].fp2, face[i].fp3,ks,kd));
			spring.push_back(Spring(face[i].fp3, face[i].fp1,ks,kd));
		
		}*/
 
//cout<<"spring size is : "<<spring.size()<<endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Object::SetTriPlanes()    // set triangle faces on side surfaces
{ 
 /*  face.push_back(Face(Object3DParticles[0], Object3DParticles[3], Object3DParticles[4]));
   face.push_back(Face(Object3DParticles[0], Object3DParticles[4], Object3DParticles[5]));
   face.push_back(Face(Object3DParticles[0], Object3DParticles[5], Object3DParticles[2]));
   face.push_back(Face(Object3DParticles[0], Object3DParticles[2], Object3DParticles[3]));
   face.push_back(Face(Object3DParticles[1], Object3DParticles[4], Object3DParticles[3]));
   face.push_back(Face(Object3DParticles[1], Object3DParticles[5], Object3DParticles[4]));
   face.push_back(Face(Object3DParticles[1], Object3DParticles[2], Object3DParticles[5]));
   face.push_back(Face(Object3DParticles[1], Object3DParticles[3], Object3DParticles[2]));*/
/*for (int i=0; i< t_face.size();i++)
{


}
*/

}
//=======================================================================



//##############################################################################

void Object::SetObject()
{
	cout<<"set points"<<endl;
//	integrator = new EulerIntegrator(*this);
	SetParticles();         // create point Object3D
 

//SetNormals();
 
// SetTriPlanes();      // set triangle faces on side surfaces
//	SetSprings();   // set springs on horizontal planes, connect points
 //iteration();  
 /*  Object3DParticles=t_Object3DParticles;

  Face=t_Face;*/
}

//#############################################################################


void Object::Update(float deltaT, bool drag, float xDrag, float yDrag)
{
	if(integrator == NULL)
//		integrator = new EulerIntegrator(*this);
//		integrator = new MidpointIntegrator(*this);
		integrator = new RungeKutta4Integrator(*this);

	integrator->integrate(deltaT, drag, xDrag, yDrag);
}
