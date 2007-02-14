#include "MidpointIntegrator.h"
#include "Object2D.h"

MidpointIntegrator::MidpointIntegrator(Object& object) : EulerIntegrator(object)
{
}

MidpointIntegrator::~MidpointIntegrator()
{
}

void MidpointIntegrator::k2(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

//	memcpy(temp_inner_points2, temp_inner_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);
//	memcpy(temp_outer_points2, temp_outer_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);
	for(int j=0; j<object->outer_points.size(); j++)
	{

		temp_outer_points1[j]->mass = temp_outer_points0[j]->mass;
		temp_outer_points1[j]->r = temp_outer_points0[j]->r;
		temp_outer_points1[j]->v = temp_outer_points0[j]->v;
		temp_outer_points1[j]->f = temp_outer_points0[j]->f;
		temp_outer_points1[j]->dr = temp_outer_points0[j]->dr;
		temp_outer_points1[j]->dv = temp_outer_points0[j]->dv;
		temp_outer_points1[j]->OneOverMass = temp_outer_points0[j]->OneOverMass;

		temp_inner_points1[j]->mass = temp_inner_points0[j]->mass;
		temp_inner_points1[j]->r = temp_inner_points0[j]->r;
		temp_inner_points1[j]->v = temp_inner_points0[j]->v;
		temp_inner_points1[j]->f = temp_inner_points0[j]->f;
		temp_inner_points1[j]->dr = temp_inner_points0[j]->dr;
		temp_inner_points1[j]->dv = temp_inner_points0[j]->dv;
		temp_inner_points1[j]->OneOverMass = temp_inner_points0[j]->OneOverMass;
	}


	temp_inner_points2[i]->dv->x = temp_inner_points0[i]->dv->x + k * 0.5 * (temp_inner_points1[i]->f->x/temp_inner_points1[i]->mass) * deltaT;
	temp_inner_points2[i]->dv->y = temp_inner_points0[i]->dv->y + k * 0.5 * (temp_inner_points1[i]->f->y/temp_inner_points1[i]->mass) * deltaT;
	temp_inner_points2[i]->dv->z = temp_inner_points0[i]->dv->z + k * 0.5 * (temp_inner_points1[i]->f->z/temp_inner_points1[i]->mass) * deltaT;

	temp_inner_points2[i]->dr->x = temp_inner_points0[i]->dr->x + k * 0.5 * temp_inner_points1[i]->dv->x * deltaT;
	temp_inner_points2[i]->dr->y = temp_inner_points0[i]->dr->y + k * 0.5 * temp_inner_points1[i]->dv->y * deltaT;
	temp_inner_points2[i]->dr->z = temp_inner_points0[i]->dr->z + k * 0.5 * temp_inner_points1[i]->dv->z * deltaT;

	temp_outer_points2[i]->dv->x = temp_outer_points0[i]->dv->x + k * 0.5 * (temp_outer_points1[i]->f->x/temp_outer_points1[i]->mass) * deltaT;
	temp_outer_points2[i]->dv->y = temp_outer_points0[i]->dv->y + k * 0.5 * (temp_outer_points1[i]->f->y/temp_outer_points1[i]->mass) * deltaT;
	temp_outer_points2[i]->dv->z = temp_outer_points0[i]->dv->z + k * 0.5 * (temp_outer_points1[i]->f->z/temp_outer_points1[i]->mass) * deltaT;
	
	temp_outer_points2[i]->dr->x = temp_outer_points0[i]->dr->x + k * 0.5 * temp_outer_points1[i]->dv->x * deltaT;
	temp_outer_points2[i]->dr->y = temp_outer_points0[i]->dr->y + k * 0.5 * temp_outer_points1[i]->dv->y * deltaT;
	temp_outer_points2[i]->dr->z = temp_outer_points0[i]->dr->z + k * 0.5 * temp_outer_points1[i]->dv->z * deltaT;
}

void MidpointIntegrator::ynew(int i, float k, float deltaT)
{
	k2(i, k, deltaT);

	object->inner_points[i]->dv->x = temp_inner_points2[i]->dv->x;
	object->inner_points[i]->dv->y = temp_inner_points2[i]->dv->y;
	object->inner_points[i]->dv->z = temp_inner_points2[i]->dv->z;

	object->inner_points[i]->dr->x = temp_inner_points2[i]->dr->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->dr->y = temp_inner_points2[i]->dr->y;
	object->inner_points[i]->dr->z = temp_inner_points2[i]->dr->z;

	object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + temp_inner_points2[i]->v->x;				// Change in velocity is added to the velocity.
	object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + temp_inner_points2[i]->v->y;		
	object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + temp_inner_points2[i]->v->z;		
	
	object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + temp_inner_points2[i]->r->x; 											// Change in position is velocity times the change in time
	object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + temp_inner_points2[i]->r->y;
	object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + temp_inner_points2[i]->r->z;


	object->outer_points[i]->dv->x = temp_outer_points2[i]->dv->x;
	object->outer_points[i]->dv->y = temp_outer_points2[i]->dv->y;
	object->outer_points[i]->dv->z = temp_outer_points2[i]->dv->z;

	object->outer_points[i]->dr->x = temp_outer_points2[i]->dr->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->dr->y = temp_outer_points2[i]->dr->y;
	object->outer_points[i]->dr->z = temp_outer_points2[i]->dr->z;

	object->outer_points[i]->v->x = temp_outer_points0[i]->v->x + temp_outer_points2[i]->v->x;				// Change in velocity is added to the velocity.
	object->outer_points[i]->v->y = temp_outer_points0[i]->v->y + temp_outer_points2[i]->v->y;		
	object->outer_points[i]->v->z = temp_outer_points0[i]->v->z + temp_outer_points2[i]->v->z;		
	
	object->outer_points[i]->r->x = temp_outer_points0[i]->r->x + temp_outer_points2[i]->r->x; 											// Change in position is velocity times the change in time
	object->outer_points[i]->r->y = temp_outer_points0[i]->r->y + temp_outer_points2[i]->r->y;
	object->outer_points[i]->r->z = temp_outer_points0[i]->r->z + temp_outer_points2[i]->r->z;
}
