#include "EulerIntegrator.h"

//##ModelId=45F4D79800AE
EulerIntegrator::EulerIntegrator(Object& object) : Integrator(object)// constructor
{
}

//##ModelId=45F4D79800B0
EulerIntegrator::~EulerIntegrator() // destructor
{
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/***********************
 * Euler Integrator integrate all the particles on the object *
 ***********************/
//void EulerIntegrator::Derivatives(Particle[] points, int NUMP, float DT)
//void EulerIntegrator::integrate(Object object, int NUMP)

//##ModelId=45F4D79800B2
void EulerIntegrator::Derivatives(float deltaT, float k)
{

	int NUMP = object->GetNumberOfParticles();

//	cout<<"derivative,,,,,,,,,,,,,,,,,,object->GetNumberOfParticles======"<<object->GetNumberOfParticles()<<endl;
	for(int i=0; i<NUMP; i++)	
	{
		ynew(i, k, deltaT);
		CollisionDetection(i);
	}
}


//##ModelId=45F4D79800BE
void EulerIntegrator::k1(int i, float k, float deltaT)
{

	for(int j=0; j<object->outer_points.size(); j++)
	{

		temp_outer_points0[j]->mass = object->outer_points[j]->mass;
		temp_outer_points0[j]->r = object->outer_points[j]->r;
		temp_outer_points0[j]->v = object->outer_points[j]->v;
		temp_outer_points0[j]->f = object->outer_points[j]->f;
		temp_outer_points0[j]->dr = object->outer_points[j]->dr;
		temp_outer_points0[j]->dv = object->outer_points[j]->dv;
		temp_outer_points0[j]->OneOverMass = object->outer_points[j]->OneOverMass;

		temp_inner_points0[j]->mass = object->inner_points[j]->mass;
		temp_inner_points0[j]->r = object->inner_points[j]->r;
		temp_inner_points0[j]->v = object->inner_points[j]->v;
		temp_inner_points0[j]->f = object->inner_points[j]->f;
		temp_inner_points0[j]->dr = object->inner_points[j]->dr;
		temp_inner_points0[j]->dv = object->inner_points[j]->dv;
		temp_inner_points0[j]->OneOverMass = object->inner_points[j]->OneOverMass;
	}
		
		
	temp_outer_points1[i]->dv->x = k * (temp_outer_points0[i]->f->x/temp_outer_points0[i]->mass) * deltaT;
	temp_outer_points1[i]->dv->y = k * (temp_outer_points0[i]->f->y/temp_outer_points0[i]->mass) * deltaT;
	temp_outer_points1[i]->dv->z = k * (temp_outer_points0[i]->f->z/temp_outer_points0[i]->mass) * deltaT;
	
	temp_outer_points1[i]->dr->x = k * temp_outer_points0[i]->v->x * deltaT;
	temp_outer_points1[i]->dr->y = k * temp_outer_points0[i]->v->y * deltaT;
	temp_outer_points1[i]->dr->z = k * temp_outer_points0[i]->v->z * deltaT;


	temp_inner_points1[i]->dv->x = k * (temp_inner_points0[i]->f->x/temp_inner_points0[i]->mass) * deltaT;
	temp_inner_points1[i]->dv->y = k * (temp_inner_points0[i]->f->y/temp_inner_points0[i]->mass) * deltaT;
	temp_inner_points1[i]->dv->z = k * (temp_inner_points0[i]->f->z/temp_inner_points0[i]->mass) * deltaT;
	
	temp_inner_points1[i]->dr->x = k * temp_inner_points0[i]->v->x * deltaT;
	temp_inner_points1[i]->dr->y = k * temp_inner_points0[i]->v->y * deltaT;
	temp_inner_points1[i]->dr->z = k * temp_inner_points0[i]->v->z * deltaT;




}

//##ModelId=45F4D79800C2
void EulerIntegrator::ynew(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

	/*if(object->dim==1){
		if (i==0){
	object->outer_points[i]->dv->x = 0;//temp_outer_points1[i]->dv->x;
	object->outer_points[i]->dv->y = 0;//temp_outer_points1[i]->dv->y;
	object->outer_points[i]->dv->z = 0;//temp_outer_points1[i]->dv->z;

	object->outer_points[i]->dr->x = 0;//temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dr->y = 0;//temp_outer_points1[i]->dr->y;
	object->outer_points[i]->dr->z = 0;//temp_outer_points1[i]->dr->z;

	object->outer_points[i]->v->x = 0;//temp_outer_points0[i]->v->x + temp_outer_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->outer_points[i]->v->y = 0;//temp_outer_points0[i]->v->y + temp_outer_points1[i]->dv->y;		
	object->outer_points[i]->v->z = 0;//temp_outer_points0[i]->v->z + temp_outer_points1[i]->dv->z;		

	object->outer_points[i]->r->x = 0;//temp_outer_points0[i]->r->x + temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->r->y = 0;//temp_outer_points0[i]->r->y + temp_outer_points1[i]->dr->y;
	object->outer_points[i]->r->z = 0;//temp_outer_points0[i]->r->z + temp_outer_points1[i]->dr->z;

	

	object->inner_points[i]->dv->x = 0;//temp_inner_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dv->y = 0;//temp_inner_points1[i]->dv->y;
	object->inner_points[i]->dv->z = 0;//temp_inner_points1[i]->dv->z;

	object->inner_points[i]->dr->x = 0;//temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = 0;//temp_inner_points1[i]->dr->y;
	object->inner_points[i]->dr->z = 0;//temp_inner_points1[i]->dr->z;


	
	object->inner_points[i]->v->x = 0;//temp_inner_points0[i]->v->x + temp_inner_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->inner_points[i]->v->y = 0;//temp_inner_points0[i]->v->y + temp_inner_points1[i]->dv->y;		
	object->inner_points[i]->v->z = 0;//temp_inner_points0[i]->v->z + temp_inner_points1[i]->dv->z;		

	object->inner_points[i]->r->x = 0;//temp_inner_points0[i]->r->x + temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = 0;//temp_inner_points0[i]->r->y + temp_inner_points1[i]->dr->y;
	object->inner_points[i]->r->z = 0;//temp_inner_points0[i]->r->z + temp_inner_points1[i]->dr->z;
	}
		else{
		object->outer_points[i]->dv->x = temp_outer_points1[i]->dv->x;
	object->outer_points[i]->dv->y = temp_outer_points1[i]->dv->y;
	object->outer_points[i]->dv->z = temp_outer_points1[i]->dv->z;

	object->outer_points[i]->dr->x = temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dr->y = temp_outer_points1[i]->dr->y;
	object->outer_points[i]->dr->z = temp_outer_points1[i]->dr->z;

	object->outer_points[i]->v->x = temp_outer_points0[i]->v->x + temp_outer_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->outer_points[i]->v->y = temp_outer_points0[i]->v->y + temp_outer_points1[i]->dv->y;		
	object->outer_points[i]->v->z = temp_outer_points0[i]->v->z + temp_outer_points1[i]->dv->z;		

	object->outer_points[i]->r->x = temp_outer_points0[i]->r->x + temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->r->y = temp_outer_points0[i]->r->y + temp_outer_points1[i]->dr->y;
	object->outer_points[i]->r->z = temp_outer_points0[i]->r->z + temp_outer_points1[i]->dr->z;

	

	object->inner_points[i]->dv->x = temp_inner_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dv->y = temp_inner_points1[i]->dv->y;
	object->inner_points[i]->dv->z = temp_inner_points1[i]->dv->z;

	object->inner_points[i]->dr->x = temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = temp_inner_points1[i]->dr->y;
	object->inner_points[i]->dr->z = temp_inner_points1[i]->dr->z;


	
	object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + temp_inner_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + temp_inner_points1[i]->dv->y;		
	object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + temp_inner_points1[i]->dv->z;		

	object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + temp_inner_points1[i]->dr->y;
	object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + temp_inner_points1[i]->dr->z;
		}
	}

	else{*/
	object->outer_points[i]->dv->x = temp_outer_points1[i]->dv->x;
	object->outer_points[i]->dv->y = temp_outer_points1[i]->dv->y;
	object->outer_points[i]->dv->z = temp_outer_points1[i]->dv->z;

	object->outer_points[i]->dr->x = temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dr->y = temp_outer_points1[i]->dr->y;
	object->outer_points[i]->dr->z = temp_outer_points1[i]->dr->z;

	object->outer_points[i]->v->x = temp_outer_points0[i]->v->x + temp_outer_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->outer_points[i]->v->y = temp_outer_points0[i]->v->y + temp_outer_points1[i]->dv->y;		
	object->outer_points[i]->v->z = temp_outer_points0[i]->v->z + temp_outer_points1[i]->dv->z;		

	object->outer_points[i]->r->x = temp_outer_points0[i]->r->x + temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->r->y = temp_outer_points0[i]->r->y + temp_outer_points1[i]->dr->y;
	object->outer_points[i]->r->z = temp_outer_points0[i]->r->z + temp_outer_points1[i]->dr->z;

	

	object->inner_points[i]->dv->x = temp_inner_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dv->y = temp_inner_points1[i]->dv->y;
	object->inner_points[i]->dv->z = temp_inner_points1[i]->dv->z;

	object->inner_points[i]->dr->x = temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = temp_inner_points1[i]->dr->y;
	object->inner_points[i]->dr->z = temp_inner_points1[i]->dr->z;


	
	object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + temp_inner_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + temp_inner_points1[i]->dv->y;		
	object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + temp_inner_points1[i]->dv->z;		

	object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + temp_inner_points1[i]->dr->y;
	object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + temp_inner_points1[i]->dr->z;
//	}
}

