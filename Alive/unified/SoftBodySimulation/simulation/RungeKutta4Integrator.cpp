#include "RungeKutta4Integrator.h"

RungeKutta4Integrator::RungeKutta4Integrator(Object& object) : MidpointIntegrator(object)
{
}

RungeKutta4Integrator::~RungeKutta4Integrator()
{
}


void RungeKutta4Integrator::k4(int i, float k, float deltaT)
{
	k3(i, k, deltaT);

	memcpy(temp_inner_points4, temp_inner_points3, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points4, temp_outer_points3, sizeof(Particle) * MAX_POINTS_SPRINGS);

	
//	k1(i, 0.5 * k, deltaT);

	temp_inner_points4[i].v->x = temp_inner_points0[i].v->x + k * (temp_inner_points3[i].f->x/temp_inner_points3[i].mass) * deltaT;
	temp_inner_points4[i].v->y = temp_inner_points0[i].v->y + k * (temp_inner_points3[i].f->y/temp_inner_points3[i].mass) * deltaT;
	temp_inner_points4[i].r->x = temp_inner_points0[i].r->x + k * temp_inner_points3[i].v->x * deltaT;
	temp_inner_points4[i].r->y = temp_inner_points0[i].r->y + k * temp_inner_points3[i].v->y * deltaT;

	temp_outer_points4[i].v->x = temp_outer_points0[i].v->x + k * (temp_outer_points3[i].f->x/temp_outer_points3[i].mass) * deltaT;
	temp_outer_points4[i].v->y = temp_outer_points0[i].v->y + k * (temp_outer_points3[i].f->y/temp_outer_points3[i].mass) * deltaT;
	temp_outer_points4[i].r->x = temp_outer_points0[i].r->x + k * temp_outer_points3[i].v->x * deltaT;
	temp_outer_points4[i].r->y = temp_outer_points0[i].r->y + k * temp_outer_points3[i].v->y * deltaT;
}

void RungeKutta4Integrator::k3(int i, float k, float deltaT)
{
	k2(i, k, deltaT);

	memcpy(temp_inner_points3, temp_inner_points2, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points3, temp_outer_points2, sizeof(Particle) * MAX_POINTS_SPRINGS);

	
//	k1(i, 0.5 * k, deltaT);

	temp_inner_points3[i].v->x = temp_inner_points0[i].v->x + k * 0.5 * (temp_inner_points2[i].f->x/temp_inner_points2[i].mass) * deltaT;
	temp_inner_points3[i].v->y = temp_inner_points0[i].v->y + k * 0.5 * (temp_inner_points2[i].f->y/temp_inner_points2[i].mass) * deltaT;
	temp_inner_points3[i].r->x = temp_inner_points0[i].r->x + k * 0.5 * temp_inner_points2[i].v->x * deltaT;
	temp_inner_points3[i].r->y = temp_inner_points0[i].r->y + k * 0.5 * temp_inner_points2[i].v->y * deltaT;

	temp_outer_points3[i].v->x = temp_outer_points0[i].v->x + k * 0.5 * (temp_outer_points2[i].f->x/temp_outer_points2[i].mass) * deltaT;
	temp_outer_points3[i].v->y = temp_outer_points0[i].v->y + k * 0.5 * (temp_outer_points2[i].f->y/temp_outer_points2[i].mass) * deltaT;
	temp_outer_points3[i].r->x = temp_outer_points0[i].r->x + k * 0.5 * temp_outer_points2[i].v->x * deltaT;
	temp_outer_points3[i].r->y = temp_outer_points0[i].r->y + k * 0.5 * temp_outer_points2[i].v->y * deltaT;
}


void RungeKutta4Integrator::k2(int i, float k, float deltaT)
{
	k1(i, k, deltaT);

	memcpy(temp_inner_points2, temp_inner_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);
	memcpy(temp_outer_points2, temp_outer_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);

	
//	k1(i, 0.5 * k, deltaT);

	temp_inner_points2[i].v->x = temp_inner_points0[i].v->x + k * 0.5 * (temp_inner_points1[i].f->x/temp_inner_points1[i].mass) * deltaT;
	temp_inner_points2[i].v->y = temp_inner_points0[i].v->y + k * 0.5 * (temp_inner_points1[i].f->y/temp_inner_points1[i].mass) * deltaT;
	temp_inner_points2[i].r->x = temp_inner_points0[i].r->x + k * 0.5 * temp_inner_points1[i].v->x * deltaT;
	temp_inner_points2[i].r->y = temp_inner_points0[i].r->y + k * 0.5 * temp_inner_points1[i].v->y * deltaT;

	temp_outer_points2[i].v->x = temp_outer_points0[i].v->x + k * 0.5 * (temp_outer_points1[i].f->x/temp_outer_points1[i].mass) * deltaT;
	temp_outer_points2[i].v->y = temp_outer_points0[i].v->y + k * 0.5 * (temp_outer_points1[i].f->y/temp_outer_points1[i].mass) * deltaT;
	temp_outer_points2[i].r->x = temp_outer_points0[i].r->x + k * 0.5 * temp_outer_points1[i].v->x * deltaT;
	temp_outer_points2[i].r->y = temp_outer_points0[i].r->y + k * 0.5 * temp_outer_points1[i].v->y * deltaT;
}

void RungeKutta4Integrator::ynew(int i, float k, float deltaT)
{
	k4(i, k, deltaT);

	object->inner_points[i].v->x = temp_inner_points0[i].v->x + 1/6*temp_inner_points1[i].v->x + 1/3*temp_inner_points2[i].v->x + 1/3*temp_inner_points3[i].v->x + 1/6*temp_inner_points4[i].v->x;				// Change in velocity is added to the velocity.
	object->inner_points[i].v->y = temp_inner_points0[i].v->x + 1/6*temp_inner_points1[i].v->y + 1/3*temp_inner_points2[i].v->y + 1/3*temp_inner_points3[i].v->y + 1/6*temp_inner_points4[i].v->y;				// Change in velocity is added to the velocity.	
	object->inner_points[i].r->x = temp_inner_points0[i].r->x + 1/6*temp_inner_points1[i].r->x + 1/3*temp_inner_points2[i].r->x + 1/3*temp_inner_points3[i].r->x + 1/6*temp_inner_points4[i].r->x;				// Change in velocity is added to the velocity.											// Change in position is velocity times the change in time
	object->inner_points[i].r->y = temp_inner_points0[i].r->y + 1/6*temp_inner_points1[i].r->y + 1/3*temp_inner_points2[i].r->y + 1/3*temp_inner_points3[i].r->y + 1/6*temp_inner_points4[i].r->y;				// Change in velocity is added to the velocity.											// Change in position is velocity times the change in time

	object->outer_points[i].v->x = temp_outer_points0[i].v->x + 1/6*temp_outer_points1[i].v->x + 1/3*temp_outer_points2[i].v->x + 1/3*temp_outer_points3[i].v->x + 1/6*temp_outer_points4[i].v->x;				// Change in velocity is added to the velocity.
	object->outer_points[i].v->y = temp_outer_points0[i].v->x + 1/6*temp_outer_points1[i].v->y + 1/3*temp_outer_points2[i].v->y + 1/3*temp_outer_points3[i].v->y + 1/6*temp_outer_points4[i].v->y;				// Change in velocity is added to the velocity.	
	object->outer_points[i].r->x = temp_outer_points0[i].r->x + 1/6*temp_outer_points1[i].r->x + 1/3*temp_outer_points2[i].r->x + 1/3*temp_outer_points3[i].r->x + 1/6*temp_outer_points4[i].r->x;				// Change in velocity is added to the velocity.											// Change in position is velocity times the change in time
	object->outer_points[i].r->y = temp_outer_points0[i].r->y + 1/6*temp_outer_points1[i].r->y + 1/3*temp_outer_points2[i].r->y + 1/3*temp_outer_points3[i].r->y + 1/6*temp_outer_points4[i].r->y;				// Change in velocity is added to the velocity.											// Change in position is velocity times the change in time

}
