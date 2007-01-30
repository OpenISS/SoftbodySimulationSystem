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

	memcpy(temp_inner_points2, temp_inner_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points2, temp_outer_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);

	temp_inner_points2[i].v->x = temp_inner_points0[i].v->x + k * 0.5 * (temp_inner_points1[i].f->x/temp_inner_points1[i].mass) * deltaT;
	temp_inner_points2[i].v->y = temp_inner_points0[i].v->y + k * 0.5 * (temp_inner_points1[i].f->y/temp_inner_points1[i].mass) * deltaT;
	temp_inner_points2[i].r->x = temp_inner_points0[i].r->x + k * 0.5 * temp_inner_points1[i].v->x * deltaT;
	temp_inner_points2[i].r->y = temp_inner_points0[i].r->y + k * 0.5 * temp_inner_points1[i].v->y * deltaT;

	temp_outer_points2[i].v->x = temp_outer_points0[i].v->x + k * 0.5 * (temp_outer_points1[i].f->x/temp_outer_points1[i].mass) * deltaT;
	temp_outer_points2[i].v->y = temp_outer_points0[i].v->y + k * 0.5 * (temp_outer_points1[i].f->y/temp_outer_points1[i].mass) * deltaT;
	temp_outer_points2[i].r->x = temp_outer_points0[i].r->x + k * 0.5 * temp_outer_points1[i].v->x * deltaT;
	temp_outer_points2[i].r->y = temp_outer_points0[i].r->y + k * 0.5 * temp_outer_points1[i].v->y * deltaT;
}

void MidpointIntegrator::ynew(int i, float k, float deltaT)
{
	k2(i, k, deltaT);

	object->inner_points[i].v->x = temp_inner_points0[i].v->x + temp_inner_points2[i].v->x;				// Change in velocity is added to the velocity.
	object->inner_points[i].v->y = temp_inner_points0[i].v->y + temp_inner_points2[i].v->y;		
	object->inner_points[i].r->x = temp_inner_points0[i].r->x + temp_inner_points2[i].r->x; 											// Change in position is velocity times the change in time
	object->inner_points[i].r->y = temp_inner_points0[i].r->y + temp_inner_points2[i].r->y;

	object->outer_points[i].v->x = temp_outer_points0[i].v->x + temp_outer_points2[i].v->x;				// Change in velocity is added to the velocity.
	object->outer_points[i].v->y = temp_outer_points0[i].v->y + temp_outer_points2[i].v->y;		
	object->outer_points[i].r->x = temp_outer_points0[i].r->x + temp_outer_points2[i].r->x; 											// Change in position is velocity times the change in time
	object->outer_points[i].r->y = temp_outer_points0[i].r->y + temp_outer_points2[i].r->y;
}
