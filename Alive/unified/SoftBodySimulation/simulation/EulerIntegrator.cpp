#include "EulerIntegrator.h"

EulerIntegrator::EulerIntegrator(Object& object) : Integrator(object)
{
}

EulerIntegrator::~EulerIntegrator()
{
}


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/***********************
 * Euler Integrator *
 ***********************/
//void EulerIntegrator::Derivatives(Particle[] points, int NUMP, float DT)
//void EulerIntegrator::integrate(Object object, int NUMP)

void EulerIntegrator::Derivatives(float deltaT, float k)
{

	int NUMP = object->GetNumberOfParticles();

	for(int i=0; i<NUMP; i++)	
	{
		ynew(i, k, deltaT);
		CollisionDetection(i);
	}
}


void EulerIntegrator::k1(int i, float k, float deltaT)
{
/*	memcpy(temp_inner_points0, object->inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(&temp_outer_points0, &object->outer_points, object->outer_points.size());
*/

	/*
	destructor:
	temp_outer_points0.clear();
	temp_outer_points1.clear();

	temp_inner_points0.clear();
	temp_inner_points1.clear();
	*/

	for(int j=0; j<object->outer_points.size(); j++)
	{

	//	cout<<"bubu loop !!!!!!!!!!!!!!!!!!!!!!!!!!"<<j<<endl;
/*
	consructor
		temp_outer_points0.push_back(new Particle (*object->outer_points[j]));
		temp_outer_points1.push_back(new Particle (*object->outer_points[j]));

		temp_inner_points0.push_back(new Particle (*object->inner_points[j]));
		temp_inner_points1.push_back(new Particle (*object->inner_points[j]));
*/
/*		temp_outer_points0[j](new Particle (*object->outer_points[j]));
		temp_outer_points1.push_back(new Particle (*object->outer_points[j]));

		temp_inner_points0.push_back(new Particle (*object->inner_points[j]));
		temp_inner_points1.push_back(new Particle (*object->inner_points[j]));
*/
		
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
		
		
//	temp_inner_points0 = object->inner_points;
//	temp_outer_points0 = object->outer_points;

/*	temp_inner_points1[i]->dv->x = k * (temp_inner_points0[i]->f->x/temp_inner_points0[i]->mass) * deltaT;
	temp_inner_points1[i]->dv->y = k * (temp_inner_points0[i]->f->y/temp_inner_points0[i]->mass) * deltaT;
	temp_inner_points1[i]->dv->z = k * (temp_inner_points0[i]->f->z/temp_inner_points0[i]->mass) * deltaT;
	
	temp_inner_points1[i]->dr->x = k * temp_inner_points0[i]->v->x * deltaT;
	temp_inner_points1[i]->dr->y = k * temp_inner_points0[i]->v->y * deltaT;
	temp_inner_points1[i]->dr->z = k * temp_inner_points0[i]->v->z * deltaT;
*/
//	cout<<"temp_outer_points0[i]->fy::::"<<temp_outer_points0[i]->f->y<<endl;
//	cout<<"temp_outer_points1[i]->vy:::"<<temp_outer_points1[i]->v->y<<endl;
//	cout<<"temp_outer_points0[i]->mass::::"<<temp_outer_points0[i]->mass<<endl;
	
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

/*	cout<<"temp_outer_points1[i]->dvy::::"<<temp_outer_points1[i]->dv->y<<endl<<endl;
cout<<"object->outer_points[i]->fy::::"<<object->outer_points[i]->f->y<<endl;
	cout<<"temp_outer_points0[i]->fy::::"<<temp_outer_points0[i]->f->y<<endl<<endl;
		
	cout<<"object->outer_points[i]->dvy::::"<<object->outer_points[i]->dv->y<<endl;
	cout<<"temp_outer_points1[i]->dvy::::"<<temp_outer_points1[i]->dv->y<<endl;
		cout<<"temp_outer_points1[i]->dvx::::"<<temp_outer_points1[i]->dv->x<<endl;
*/



}

void EulerIntegrator::ynew(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

/*	object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + temp_inner_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + temp_inner_points1[i]->dv->y;		
	object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + temp_inner_points1[i]->dv->z;		

	object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + temp_inner_points1[i]->dr->y;
	object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + temp_inner_points1[i]->dr->z;

	object->inner_points[i]->dv->x = temp_inner_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dv->y = temp_inner_points1[i]->dv->y;
	object->inner_points[i]->dv->z = temp_inner_points1[i]->dv->z; 						

	object->inner_points[i]->dr->x = temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = temp_inner_points1[i]->dr->y;
	object->inner_points[i]->dr->z = temp_inner_points1[i]->dr->z;

*/

	object->outer_points[i]->v->x = temp_outer_points0[i]->v->x + temp_outer_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->outer_points[i]->v->y = temp_outer_points0[i]->v->y + temp_outer_points1[i]->dv->y;		
	object->outer_points[i]->v->z = temp_outer_points0[i]->v->z + temp_outer_points1[i]->dv->z;		

	object->outer_points[i]->r->x = temp_outer_points0[i]->r->x + temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->r->y = temp_outer_points0[i]->r->y + temp_outer_points1[i]->dr->y;
	object->outer_points[i]->r->z = temp_outer_points0[i]->r->z + temp_outer_points1[i]->dr->z;

	object->outer_points[i]->dv->x = temp_outer_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dv->y = temp_outer_points1[i]->dv->y;
	object->outer_points[i]->dv->z = temp_outer_points1[i]->dv->z;

	object->outer_points[i]->dr->x = temp_outer_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dr->y = temp_outer_points1[i]->dr->y;
	object->outer_points[i]->dr->z = temp_outer_points1[i]->dr->z;


	
	object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + temp_inner_points1[i]->dv->x;				// Change in velocity is added to the velocity->
	object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + temp_inner_points1[i]->dv->y;		
	object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + temp_inner_points1[i]->dv->z;		

	object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + temp_inner_points1[i]->dr->y;
	object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + temp_inner_points1[i]->dr->z;

	object->inner_points[i]->dv->x = temp_inner_points1[i]->dv->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dv->y = temp_inner_points1[i]->dv->y;
	object->inner_points[i]->dv->z = temp_inner_points1[i]->dv->z;

	object->inner_points[i]->dr->x = temp_inner_points1[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = temp_inner_points1[i]->dr->y;
	object->inner_points[i]->dr->z = temp_inner_points1[i]->dr->z;


}
