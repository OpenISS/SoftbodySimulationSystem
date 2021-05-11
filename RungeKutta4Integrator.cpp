#include "RungeKutta4Integrator.h"

//##ModelId=45F4D7970041
RungeKutta4Integrator::RungeKutta4Integrator(Object& object) : MidpointIntegrator(object)
{
}

//##ModelId=45F4D7970043
RungeKutta4Integrator::~RungeKutta4Integrator()
{
}


//##ModelId=45F4D7970044
void RungeKutta4Integrator::k4(int i, float k, float deltaT)
{
    k3(i, k, deltaT);

//    memcpy(temp_inner_points4, temp_inner_points3, sizeof(Particle) * MAX_POINTS_SPRINGS);
//    memcpy(temp_outer_points4, temp_outer_points3, sizeof(Particle) * MAX_POINTS_SPRINGS);


    for(int j=1; j<object->outer_points.size(); j++)
    {

        temp_outer_points4[j]->mass = temp_outer_points3[j]->mass;
        temp_outer_points4[j]->r = temp_outer_points3[j]->r;
        temp_outer_points4[j]->v = temp_outer_points3[j]->v;
        temp_outer_points4[j]->f = temp_outer_points3[j]->f;
        temp_outer_points4[j]->dr = temp_outer_points3[j]->dr;
        temp_outer_points4[j]->dv = temp_outer_points3[j]->dv;
        temp_outer_points4[j]->OneOverMass = temp_outer_points3[j]->OneOverMass;

        temp_inner_points4[j]->mass = temp_inner_points3[j]->mass;
        temp_inner_points4[j]->r = temp_inner_points3[j]->r;
        temp_inner_points4[j]->v = temp_inner_points3[j]->v;
        temp_inner_points4[j]->f = temp_inner_points3[j]->f;
        temp_inner_points4[j]->dr = temp_inner_points3[j]->dr;
        temp_inner_points4[j]->dv = temp_inner_points3[j]->dv;
        temp_inner_points4[j]->OneOverMass = temp_inner_points3[j]->OneOverMass;
    }
    
//    k1(i, 0.5 * k, deltaT);

    temp_inner_points4[i]->dv->x = temp_inner_points0[i]->dv->x + k * (temp_inner_points3[i]->f->x/temp_inner_points3[i]->mass) * deltaT;
    temp_inner_points4[i]->dv->y = temp_inner_points0[i]->dv->y + k * (temp_inner_points3[i]->f->y/temp_inner_points3[i]->mass) * deltaT;
    temp_inner_points4[i]->dv->z = temp_inner_points0[i]->dv->z + k * (temp_inner_points3[i]->f->z/temp_inner_points3[i]->mass) * deltaT;

    temp_inner_points4[i]->dr->x = temp_inner_points0[i]->dr->x + k * temp_inner_points3[i]->dv->x * deltaT;
    temp_inner_points4[i]->dr->y = temp_inner_points0[i]->dr->y + k * temp_inner_points3[i]->dv->y * deltaT;
    temp_inner_points4[i]->dr->z = temp_inner_points0[i]->dr->z + k * temp_inner_points3[i]->dv->z * deltaT;

    temp_outer_points4[i]->dv->x = temp_outer_points0[i]->dv->x + k * (temp_outer_points3[i]->f->x/temp_outer_points3[i]->mass) * deltaT;
    temp_outer_points4[i]->dv->y = temp_outer_points0[i]->dv->y + k * (temp_outer_points3[i]->f->y/temp_outer_points3[i]->mass) * deltaT;
    temp_outer_points4[i]->dv->z = temp_outer_points0[i]->dv->z + k * (temp_outer_points3[i]->f->z/temp_outer_points3[i]->mass) * deltaT;

    temp_outer_points4[i]->dr->x = temp_outer_points0[i]->dr->x + k * temp_outer_points3[i]->dv->x * deltaT;
    temp_outer_points4[i]->dr->y = temp_outer_points0[i]->dr->y + k * temp_outer_points3[i]->dv->y * deltaT;
    temp_outer_points4[i]->dr->z = temp_outer_points0[i]->dr->z + k * temp_outer_points3[i]->dv->z * deltaT;

}

//##ModelId=45F4D7970050
void RungeKutta4Integrator::k3(int i, float k, float deltaT)
{
    k2(i, k, deltaT);

//    memcpy(temp_inner_points3, temp_inner_points2, sizeof(Particle) * MAX_POINTS_SPRINGS);
//    memcpy(temp_outer_points3, temp_outer_points2, sizeof(Particle) * MAX_POINTS_SPRINGS);


        for(int j=1; j<object->outer_points.size(); j++)
    {

        temp_outer_points3[j]->mass = temp_outer_points2[j]->mass;
        temp_outer_points3[j]->r = temp_outer_points2[j]->r;
        temp_outer_points3[j]->v = temp_outer_points2[j]->v;
        temp_outer_points3[j]->f = temp_outer_points2[j]->f;
        temp_outer_points3[j]->dr = temp_outer_points2[j]->dr;
        temp_outer_points3[j]->dv = temp_outer_points2[j]->dv;
        temp_outer_points3[j]->OneOverMass = temp_outer_points2[j]->OneOverMass;

        temp_inner_points3[j]->mass = temp_inner_points2[j]->mass;
        temp_inner_points3[j]->r = temp_inner_points2[j]->r;
        temp_inner_points3[j]->v = temp_inner_points2[j]->v;
        temp_inner_points3[j]->f = temp_inner_points2[j]->f;
        temp_inner_points3[j]->dr = temp_inner_points2[j]->dr;
        temp_inner_points3[j]->dv = temp_inner_points2[j]->dv;
        temp_inner_points3[j]->OneOverMass = temp_inner_points2[j]->OneOverMass;
    }
    
//    k1(i, 0.5 * k, deltaT);

    temp_inner_points3[i]->dv->x = temp_inner_points0[i]->dv->x + k * 0.5 * (temp_inner_points2[i]->f->x/temp_inner_points2[i]->mass) * deltaT;
    temp_inner_points3[i]->dv->y = temp_inner_points0[i]->dv->y + k * 0.5 * (temp_inner_points2[i]->f->y/temp_inner_points2[i]->mass) * deltaT;
    temp_inner_points3[i]->dr->x = temp_inner_points0[i]->dr->x + k * 0.5 * temp_inner_points2[i]->dv->x * deltaT;
    temp_inner_points3[i]->dr->y = temp_inner_points0[i]->dr->y + k * 0.5 * temp_inner_points2[i]->dv->y * deltaT;

    temp_outer_points3[i]->dv->x = temp_outer_points0[i]->dv->x + k * 0.5 * (temp_outer_points2[i]->f->x/temp_outer_points2[i]->mass) * deltaT;
    temp_outer_points3[i]->dv->y = temp_outer_points0[i]->dv->y + k * 0.5 * (temp_outer_points2[i]->f->y/temp_outer_points2[i]->mass) * deltaT;
    temp_outer_points3[i]->dr->x = temp_outer_points0[i]->dr->x + k * 0.5 * temp_outer_points2[i]->dv->x * deltaT;
    temp_outer_points3[i]->dr->y = temp_outer_points0[i]->dr->y + k * 0.5 * temp_outer_points2[i]->dv->y * deltaT;
}

/*
void RungeKutta4Integrator::k2(int i, float k, float deltaT)
{
    k1(i, k, deltaT);

    memcpy(temp_inner_points2, temp_inner_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);
    memcpy(temp_outer_points2, temp_outer_points1, sizeof(Particle) * MAX_POINTS_SPRINGS);

    
//    k1(i, 0.5 * k, deltaT);

    temp_inner_points2[i].v->x = temp_inner_points0[i].v->x + k * 0.5 * (temp_inner_points1[i].f->x/temp_inner_points1[i].mass) * deltaT;
    temp_inner_points2[i].v->y = temp_inner_points0[i].v->y + k * 0.5 * (temp_inner_points1[i].f->y/temp_inner_points1[i].mass) * deltaT;
    temp_inner_points2[i].r->x = temp_inner_points0[i].r->x + k * 0.5 * temp_inner_points1[i].v->x * deltaT;
    temp_inner_points2[i].r->y = temp_inner_points0[i].r->y + k * 0.5 * temp_inner_points1[i].v->y * deltaT;

    temp_outer_points2[i].v->x = temp_outer_points0[i].v->x + k * 0.5 * (temp_outer_points1[i].f->x/temp_outer_points1[i].mass) * deltaT;
    temp_outer_points2[i].v->y = temp_outer_points0[i].v->y + k * 0.5 * (temp_outer_points1[i].f->y/temp_outer_points1[i].mass) * deltaT;
    temp_outer_points2[i].r->x = temp_outer_points0[i].r->x + k * 0.5 * temp_outer_points1[i].v->x * deltaT;
    temp_outer_points2[i].r->y = temp_outer_points0[i].r->y + k * 0.5 * temp_outer_points1[i].v->y * deltaT;
}
*/

//##ModelId=45F4D7970054
void RungeKutta4Integrator::ynew(int i, float k, float deltaT)
{
    k4(i, k, deltaT);

    object->inner_points[i]->dv->x = temp_inner_points4[i]->dv->x;
    object->inner_points[i]->dv->y = temp_inner_points4[i]->dv->y;
    object->inner_points[i]->dv->z = temp_inner_points4[i]->dv->z;

    object->inner_points[i]->dr->x = temp_inner_points4[i]->dr->x;                                             // Change in position is velocity times the change in time
    object->inner_points[i]->dr->y = temp_inner_points4[i]->dr->y;
    object->inner_points[i]->dr->z = temp_inner_points4[i]->dr->z;


    object->inner_points[i]->v->x = temp_inner_points0[i]->v->x + 1/6*temp_inner_points1[i]->v->x + 1/3*temp_inner_points2[i]->v->x + 1/3*temp_inner_points3[i]->v->x + 1/6*temp_inner_points4[i]->v->x;                // Change in velocity is added to the velocity.
    object->inner_points[i]->v->y = temp_inner_points0[i]->v->y + 1/6*temp_inner_points1[i]->v->y + 1/3*temp_inner_points2[i]->v->y + 1/3*temp_inner_points3[i]->v->y + 1/6*temp_inner_points4[i]->v->y;                // Change in velocity is added to the velocity.
    object->inner_points[i]->v->z = temp_inner_points0[i]->v->z + 1/6*temp_inner_points1[i]->v->z + 1/3*temp_inner_points2[i]->v->z + 1/3*temp_inner_points3[i]->v->z + 1/6*temp_inner_points4[i]->v->z;                // Change in velocity is added to the velocity.

    object->inner_points[i]->r->x = temp_inner_points0[i]->r->x + 1/6*temp_inner_points1[i]->r->x + 1/3*temp_inner_points2[i]->r->x + 1/3*temp_inner_points3[i]->r->x + 1/6*temp_inner_points4[i]->r->x;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time
    object->inner_points[i]->r->y = temp_inner_points0[i]->r->y + 1/6*temp_inner_points1[i]->r->y + 1/3*temp_inner_points2[i]->r->y + 1/3*temp_inner_points3[i]->r->y + 1/6*temp_inner_points4[i]->r->y;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time
    object->inner_points[i]->r->z = temp_inner_points0[i]->r->z + 1/6*temp_inner_points1[i]->r->z + 1/3*temp_inner_points2[i]->r->z + 1/3*temp_inner_points3[i]->r->z + 1/6*temp_inner_points4[i]->r->z;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time

    
    object->outer_points[i]->dv->x = temp_outer_points4[i]->dv->x;
    object->outer_points[i]->dv->y = temp_outer_points4[i]->dv->y;
    object->outer_points[i]->dv->z = temp_outer_points4[i]->dv->z;

    object->outer_points[i]->dr->x = temp_outer_points4[i]->dr->x;                                             // Change in position is velocity times the change in time
    object->outer_points[i]->dr->y = temp_outer_points4[i]->dr->y;
    object->outer_points[i]->dr->z = temp_outer_points4[i]->dr->z;

    object->outer_points[i]->v->x = temp_outer_points0[i]->v->x + 1/6*temp_outer_points1[i]->v->x + 1/3*temp_outer_points2[i]->v->x + 1/3*temp_outer_points3[i]->v->x + 1/6*temp_outer_points4[i]->v->x;                // Change in velocity is added to the velocity.
    object->outer_points[i]->v->y = temp_outer_points0[i]->v->y + 1/6*temp_outer_points1[i]->v->y + 1/3*temp_outer_points2[i]->v->y + 1/3*temp_outer_points3[i]->v->y + 1/6*temp_outer_points4[i]->v->y;                // Change in velocity is added to the velocity.
    object->outer_points[i]->v->z = temp_outer_points0[i]->v->z + 1/6*temp_outer_points1[i]->v->z + 1/3*temp_outer_points2[i]->v->z + 1/3*temp_outer_points3[i]->v->z + 1/6*temp_outer_points4[i]->v->z;                // Change in velocity is added to the velocity.

    object->outer_points[i]->r->x = temp_outer_points0[i]->r->x + 1/6*temp_outer_points1[i]->r->x + 1/3*temp_outer_points2[i]->r->x + 1/3*temp_outer_points3[i]->r->x + 1/6*temp_outer_points4[i]->r->x;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time
    object->outer_points[i]->r->y = temp_outer_points0[i]->r->y + 1/6*temp_outer_points1[i]->r->y + 1/3*temp_outer_points2[i]->r->y + 1/3*temp_outer_points3[i]->r->y + 1/6*temp_outer_points4[i]->r->y;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time
    object->outer_points[i]->r->z = temp_outer_points0[i]->r->z + 1/6*temp_outer_points1[i]->r->z + 1/3*temp_outer_points2[i]->r->z + 1/3*temp_outer_points3[i]->r->z + 1/6*temp_outer_points4[i]->r->z;                // Change in velocity is added to the velocity.                                            // Change in position is velocity times the change in time

}
