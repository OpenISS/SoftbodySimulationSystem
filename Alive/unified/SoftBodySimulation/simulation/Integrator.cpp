#include "Integrator.h"
#include "Object2D.h"
#include <assert.h>
#include <vector>

Integrator::Integrator(Object& objectToIntegrate) : dragExists(false)
{

	this->object = &objectToIntegrate;
//	memcpy(temp_inner_points0, object.inner_points, sizeof(Particle) * MAX_POINTS_SPRINGS);
//	memcpy(temp_outer_points0, object.outer_points, sizeof(Particle) * MAX_POINTS_SPRINGS);

//	temp_outer_points0 = object.outer_points;
	for(int j=0; j<objectToIntegrate.outer_points.size(); j++)
	{
		temp_outer_points0.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points1.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points2.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points3.push_back(new Particle (*this->object->outer_points[j]));
		temp_outer_points4.push_back(new Particle (*this->object->outer_points[j]));

		temp_inner_points0.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points1.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points2.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points3.push_back(new Particle (*this->object->inner_points[j]));
		temp_inner_points4.push_back(new Particle (*this->object->inner_points[j]));
	}

	dim = DIM1D;
}

Integrator::~Integrator()
{
//	delete this->initObject;
	temp_outer_points0.clear();
	temp_outer_points1.clear();
	temp_outer_points2.clear();
	temp_outer_points3.clear();
	temp_outer_points4.clear();

	temp_inner_points0.clear();
	temp_inner_points1.clear();
	temp_inner_points2.clear();
	temp_inner_points3.clear();
	temp_inner_points4.clear();
}

void Integrator::integrate(float deltaT, bool drag, float xDrag, float yDrag)
{
	dragExists = drag;
	mDragX = xDrag;
	mDragY = yDrag;

//	this->object->FindClosestPoint();

	//cout<<"mDragX=="<<mDragX<<"==mDragY=="<<mDragY<<endl;
	// accumulate forces acted on
	AccumulateForces();    
	Derivatives(deltaT, 1.0);

/*
	cout<<"derived fx sp1 = "<<object->outer_points[0]->f->x << ",fy sp1=" <<object->outer_points[0]->f->y<<endl;
	cout<<"derived vx sp1 = "<<object->outer_points[0]->v->x << ",vy sp1=" <<object->outer_points[0]->v->y<<endl;
	cout<<"==================================="<<endl<<endl;
*/
}


void Integrator::AccumulateForces()   // accumulate forces acted on 
{
	ExternalForces();
	SpringForces();	

	switch(dim)
	{
		case DIM1D:
			break;

		// Pressure forces are not applicable in 1D
		case DIM2D:
		case DIM3D:
	//		PressureForces();
			break;
	}
}


void Integrator::ExternalForces()
{
	int i;    // runing index


	float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2;	// points outer_p1, outer_p2 on the outer circle
  
    float outer_rd12;			            	// length of outer_p1, outer_p2

    float outer_Fx,outer_Fy,outer_Fz;		            // force vector

	float f;				        // external force 


	// Gravity
	for(i = 0; i < object->GetNumberOfParticles(); i++)
	{
		object->inner_points[i]->f->x = 0;//40*sin(25*i);
		object->inner_points[i]->f->y = MASS * GY;     
		object->inner_points[i]->f->z = 0;//(object->inner_points[i]->mass)*GY;     

		object->outer_points[i]->f->x = 0;//40*sin(25*i);
		object->outer_points[i]->f->y = MASS * GY;//10;//(object->outer_points[i]->mass)*GY;	
		object->outer_points[i]->f->z = 0;//40*sin(25*i);
		
		if(i == object->closest_i)
		{
			if(dragExists)			// if user clicked
			{
				outer_x1 = object->outer_points[ i ]->r->x;		// get points X-coord
				outer_y1 = object->outer_points[ i ]->r->y;        // get points Y-coord
				outer_z1 = object->outer_points[ i ]->r->z;        // get points Y-coord

				outer_x2 = mDragX;                      // get Mouse  X-coord
				outer_y2 = mDragY;                      // get Mouse  Y-coord
				outer_z2 = 0;                      // get Mouse  Y-coord

				outer_rd12 =
					sqrt((outer_x1-outer_x2) * (outer_x1-outer_x2)
						+(outer_y1-outer_y2) * (outer_y1-outer_y2)
						+(outer_z1-outer_z2) * (outer_z1-outer_z2)
						); // distance

				f = (outer_rd12 - MOUSE_REST) * MOUSE_KS
				  + (
						  object->outer_points[i]->v->x * (outer_x1-outer_x2)
						+ object->outer_points[i]->v->y * (outer_y1-outer_y2)
						+ object->outer_points[i]->v->z * (outer_z1-outer_z2)
					) * MOUSE_KD / outer_rd12;

				// calculate spring force
				outer_Fx = ((outer_x1 - outer_x2) / outer_rd12) * f;
				outer_Fy = ((outer_y1 - outer_y2) / outer_rd12) * f;
				outer_Fz = ((outer_z1 - outer_z2) / outer_rd12) * f;

				// accumulate gravity + hooke forces
				object->outer_points[i]->f->x -= outer_Fx; // from the closet point to the Mouse point
				object->outer_points[i]->f->y -= outer_Fy;
				object->outer_points[i]->f->z -= outer_Fz;
			}
		}
	}
}


void Integrator::SpringForces()
{
	int i;    // runing index


	// Three parts for computing the spring forces on all the points
	for(i = 0; i<object->GetNumberOfSprings(); i++)  // Part #1, tangent spring force constribution 
	{
		CalculateSpringForces(object->outer_springs, i);


		switch(dim)
		{
			case DIM1D:
				// intentionally empty
				break;

			case DIM2D:
			{
		
				CalculateSpringForces
				(
				
					((Object2D*)object)->inner_springs,
					i
				);
			
				CalculateSpringForces
				(
					((Object2D*)object)->radium_springs,
					i
				);

				//  Part #3 shear spring constribution
				CalculateSpringForces
				(
					((Object2D*)object)->shear_springs_left,
					i
				);

				CalculateSpringForces
				(
					((Object2D*)object)->shear_springs_right,
					i
				);

				break;
			}

			case DIM3D:
			{
			}
		
		}
	}
}

void Integrator::CalculateSpringForces(vector<Spring *>springs, int i)
{
	float vx12, vy12, vz12;
	float Fx, Fy, Fz;
	float /*fx, fy,*/ f;

	float x1 = springs[i]->sp1->r->x;
	float y1 = springs[i]->sp1->r->y;
	float z1 = springs[i]->sp1->r->z;

	float x2 = springs[i]->sp2->r->x;
	float y2 = springs[i]->sp2->r->y;
	float z2 = springs[i]->sp2->r->z;


	float rd12 = (*springs[i]->sp1->r - *springs[i]->sp2->r).getLength();

	if(rd12 == 0)
	{
		cerr << "WARNING: rd12 is zero, ignoring the rest of the spring forces calculations... " << endl;
		return;
	}

	/* Calculate normal vectors to springs */

	switch(dim)
	{
		case DIM1D:
		case DIM2D:
			springs[i]->normal.x = -(y1 - y2) / rd12;  // Normal Y-vector
			springs[i]->normal.y = +(x1 - x2) / rd12;  // Normal X-vector 
			springs[i]->normal.z = 0;  // Normal Z-vector 
			break;

		case DIM3D:
			cout << "computing 3D normal" << endl;
			springs[i]->normal.x = -(x1 - x2) / rd12;  // Normal Y-vector
			springs[i]->normal.y = +(z1 - z2) / rd12;  // Normal X-vector 
			springs[i]->normal.z = +(y1 - y2) / rd12;  // Normal Z-vector 
			break;
	}


	vx12 = springs[i]->sp1->v->x - springs[i]->sp2->v->x;
	vy12 = springs[i]->sp1->v->y - springs[i]->sp2->v->y;
	vz12 = springs[i]->sp1->v->z - springs[i]->sp2->v->z;

	f = (rd12 - springs[i]->restLen) * KS
	  + (vx12 * (x1 - x2)
	  +  vy12 * (y1 - y2)
	  +  vz12 * (z1 - z2)) * KD / rd12;

	Fx = ((x1 - x2) / rd12) * f;
	Fy = ((y1 - y2) / rd12) * f;
	Fz = ((z1 - z2) / rd12) * f;

//	cout<<"Fx-------------"<<Fx<<endl;
//	cout<<"Fy-------------"<<Fy<<endl;

	springs[i]->sp1->f->x -= Fx;
	springs[i]->sp1->f->y -= Fy;
	springs[i]->sp1->f->z -= Fz;

	springs[i]->sp2->f->x += Fx;
	springs[i]->sp2->f->y += Fy;
	springs[i]->sp2->f->z += Fz;
}

///*

void Integrator::PressureForces()
{
	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2,inner_z1,inner_z2;	// points inner_p1, inner_p2 on the inner circle
    float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2;	// points outer_p1, outer_p2 on the outer circle

// 	float radium_rd12;                          // length of inner_p1, outer_p1 

	float inner_rd12;			            	// length of inner_p1, inner_p2
	float outer_rd12;			            	// length of outer_p1, outer_p2    

	float inner_volume=0.0;           // inner circle inner_volume
	float outer_volume=0.0;		    // outer circle outer_volume 

	float inner_p_accu;             // pressure force accumulation 
	float outer_p_accu;         	// pressure force accumulation


	// pressure force for the inner and outer circles
	
	for(i=0; i<object->GetNumberOfSprings(); i++) // calculation of inner circle volume
	{
        inner_x1 = object->inner_springs[i]->sp1->r->x;	
		inner_y1 = object->inner_springs[i]->sp1->r->y;
		inner_z1 = object->inner_springs[i]->sp1->r->z;

		inner_x2 = object->inner_springs[i]->sp2->r->x;	
		inner_y2 = object->inner_springs[i]->sp2->r->y;
		inner_z2 = object->inner_springs[i]->sp2->r->z;

		inner_rd12 =
			sqrt(
				(inner_x1-inner_x2)*(inner_x1-inner_x2)
			   +(inner_y1-inner_y2)*(inner_y1-inner_y2)
			   +(inner_z1-inner_z2)*(inner_z1-inner_z2)
			   );

		// XXX
		inner_volume += 10.5 *
			fabs(inner_x1 - inner_x2) *
			fabs(object->inner_springs[i]->normal.x) * 
			(inner_rd12);

//	
		outer_x1 = object->outer_springs[i]->sp1->r->x;	
		outer_y1 = object->outer_springs[i]->sp1->r->y;
		outer_z1 = object->outer_springs[i]->sp1->r->z;

		outer_x2 = object->outer_springs[i]->sp2->r->x;	
		outer_y2 = object->outer_springs[i]->sp2->r->y;
		outer_z2 = object->outer_springs[i]->sp2->r->z;

		outer_rd12 = 
			sqrt(
				(outer_x1-outer_x2)*(outer_x1-outer_x2)
			   +(outer_y1-outer_y2)*(outer_y1-outer_y2)
			   +(outer_z1-outer_z2)*(outer_z1-outer_z2)
			   );	

//		outer_volume += 5.5 * 
//		outer_volume += 1.05 * 
		outer_volume +=	40.5 * 
			fabs(outer_x1 - outer_x2) * 
//			fabs(outer_y1 - outer_y2) * 
//			fabs(outer_z1 - outer_z2) * 
			(
			fabs(object->outer_springs[i]->normal.x)
			+fabs(object->outer_springs[i]->normal.y)
			+fabs(object->outer_springs[i]->normal.z)
			) * 
			(outer_rd12);
//	
	} 

	



	for(i=0; i<object->GetNumberOfSprings(); i++)  // calculation inner pressure force 
	{
        inner_x1 = object->inner_springs[i]->sp1->r->x;
		inner_y1 = object->inner_springs[i]->sp1->r->y;
		inner_z1 = object->inner_springs[i]->sp1->r->z;

		inner_x2 = object->inner_springs[i]->sp2->r->x;	
		inner_y2 = object->inner_springs[i]->sp2->r->y;
		inner_z2 = object->inner_springs[i]->sp2->r->z;

		inner_rd12=sqrt((inner_x1-inner_x2)*(inner_x1-inner_x2) 
		+  (inner_y1-inner_y2)*(inner_y1-inner_y2)
		+  (inner_z1-inner_z2)*(inner_z1-inner_z2)
		);	

		inner_p_accu = inner_rd12 * ((Object2D*)object)->getPressure() * (1.0f / inner_volume);
	
		object->inner_springs[i]->sp1->f->x += object->inner_springs[i]->normal.x*inner_p_accu;
		object->inner_springs[i]->sp1->f->y += object->inner_springs[i]->normal.y*inner_p_accu;
		object->inner_springs[i]->sp1->f->z += object->inner_springs[i]->normal.z*inner_p_accu;

		object->inner_springs[i]->sp2->f->x += object->inner_springs[i]->normal.x*inner_p_accu;
		object->inner_springs[i]->sp2->f->y += object->inner_springs[i]->normal.y*inner_p_accu;
		object->inner_springs[i]->sp2->f->z += object->inner_springs[i]->normal.z*inner_p_accu;

		////////////////////////////////////////////
		outer_x1 = object->outer_springs[i]->sp1->r->x;
		outer_y1 = object->outer_springs[i]->sp1->r->y;
		outer_z1 = object->outer_springs[i]->sp1->r->z;

		outer_x2 = object->outer_springs[i]->sp2->r->x;	
		outer_y2 = object->outer_springs[i]->sp2->r->y;
		outer_z2 = object->outer_springs[i]->sp2->r->z;

		outer_rd12=sqrt((outer_x1-outer_x2)*(outer_x1-outer_x2) 
		+  (outer_y1-outer_y2)*(outer_y1-outer_y2)
		+  (outer_z1-outer_z2)*(outer_z1-outer_z2)
		);	
													

		outer_p_accu = outer_rd12 * ((Object2D*)object)->getPressure() * (1.0f / outer_volume);
	
		object->outer_springs[i]->sp1->f->x += object->outer_springs[i]->normal.x * outer_p_accu;
		object->outer_springs[i]->sp1->f->y += object->outer_springs[i]->normal.y * outer_p_accu;
		object->outer_springs[i]->sp1->f->z += object->outer_springs[i]->normal.z * outer_p_accu;

		object->outer_springs[i]->sp2->f->x += object->outer_springs[i]->normal.x * outer_p_accu;
		object->outer_springs[i]->sp2->f->y += object->outer_springs[i]->normal.y * outer_p_accu;
		object->outer_springs[i]->sp2->f->z += object->outer_springs[i]->normal.z * outer_p_accu;
	}
}
//*/

/*
/////////////////////////////////////////////////////////////////////
void Integrator::PressureForces()
{
	int i;    // runing index

   	float inner_x1,inner_x2,inner_y1,inner_y2,inner_z1,inner_z2;	// points inner_p1, inner_p2 on the inner circle
    float outer_x1,outer_x2,outer_y1,outer_y2,outer_z1,outer_z2;	// points outer_p1, outer_p2 on the outer circle

// 	float radium_rd12;                          // length of inner_p1, outer_p1 

	float inner_rd12;			            	// length of inner_p1, inner_p2
	float outer_rd12;			            	// length of outer_p1, outer_p2    

	float inner_volume=0.0;           // inner circle inner_volume
	float outer_volume=0.0;		    // outer circle outer_volume 

	float inner_p_accu=0;;             // pressure force accumulation 
	float outer_p_accu=0;;         	// pressure force accumulation

	for(i=0;i<object->inner_faces.size();i++)
	{
		object->inner_faces[i]->CalNormalNField();
		object->outer_faces[i]->CalNormalNField();
		//		cout<<"outer_faces[i]->normal->x==="<<outer_faces[i]->normal->x<<"=== outer_faces[i]->normal->y==="<<outer_faces[i]->normal->y<<"===outer_faces[i]->normal->z===="<<outer_faces[i]->normal->z<<endl;
	}

	// pressure force for the inner circle 
	
	for(i=0; i<object->outer_faces.size(); i++) // calculation of inner circle volume
	{
		inner_volume += 0.5 * (object->inner_faces[i]->fp1->r->x +
							   object->inner_faces[i]->fp2->r->x +
							   object->inner_faces[i]->fp3->r->x)*
						(object->inner_faces[i]->normal->x) * 
						(object->inner_faces[i]->normal->getLength());

		outer_volume += 0.5 * (object->outer_faces[i]->fp1->r->x +
							   object->outer_faces[i]->fp2->r->x +
							   object->outer_faces[i]->fp3->r->x)*
						(object->outer_faces[i]->normal->x) * 
						(object->outer_faces[i]->normal->getLength());
	}

	
	for(i = 0; i < object->outer_faces.size(); i++)  // calculation inner pressure force 
	{
		inner_p_accu=(object->inner_faces[i]->normal->x) * 
					 (object->inner_faces[i]->normal->getLength())*
					 ((Object2D*)object)->getPressure()*(1.0f/inner_volume);

		object->inner_faces[i]->fp1->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp1->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp1->f->z += 0.5 * inner_p_accu;

		object->inner_faces[i]->fp2->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp2->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp2->f->z += 0.5 * inner_p_accu;

		object->inner_faces[i]->fp3->f->x += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp3->f->y += 0.5 * inner_p_accu;
		object->inner_faces[i]->fp3->f->z += 0.5 * inner_p_accu;

				////////////////////////////////////////////
	
		outer_p_accu=(object->outer_faces[i]->normal->x) *
				 (object->outer_faces[i]->normal->getLength()) *
				 ((Object2D*)object)->getPressure() * (1.0f/outer_volume);

		object->outer_faces[i]->fp1->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp1->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp1->f->z += 0.5 * outer_p_accu;

		object->outer_faces[i]->fp2->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp2->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp2->f->z += 0.5 * outer_p_accu;

		object->outer_faces[i]->fp3->f->x += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp3->f->y += 0.5 * outer_p_accu;
		object->outer_faces[i]->fp3->f->z += 0.5 * outer_p_accu;
	}

}


//*/




//////////////////////////////////////////////////////////////////////
void Integrator::CollisionDetection(int i)
{
	bool changed = false;
	float decay = 0.5;

	// Check #1 - X boundaries
	if((object->outer_points[i]->r->x + object->outer_points[i]->dr->x) < -LIMIT)
	{
		object->outer_points[i]->dr->x = -LIMIT - object->outer_points[i]->r->x;
		changed = true;
	}
	else if((object->outer_points[i]->r->x + object->outer_points[i]->dr->x) > LIMIT)
	{
		object->outer_points[i]->dr->x = LIMIT - object->outer_points[i]->r->x;
		changed = true;
	} 

	if(changed)
	{
		object->outer_points[i]->v->x = -decay * object->outer_points[i]->v->x;
		object->outer_points[i]->v->y =  0.5 * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z =  0.5 * object->outer_points[i]->v->z;


		object->outer_points[i]->r->x = object->outer_points[i]->r->x + object->outer_points[i]->dr->x;
		changed = false;

	}

	
	// Check #2 - Y boundaries	
	if((object->outer_points[i]->r->y + object->outer_points[i]->dr->y) < -LIMIT)
	{
		object->outer_points[i]->dr->y = -LIMIT - object->outer_points[i]->r->y;
		changed = true;
	}
	else if((object->outer_points[i]->r->y + object->outer_points[i]->dr->y) > LIMIT)
	{
		object->outer_points[i]->dr->y = LIMIT - object->outer_points[i]->r->y;
		changed = true;
	}

	if(changed)
	{
		object->outer_points[i]->v->x =    0.5 * object->outer_points[i]->v->x;   
		object->outer_points[i]->v->y =  - decay * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z =    0.5 * object->outer_points[i]->v->z;   
		
		object->outer_points[i]->r->y  = object->outer_points[i]->r->y + object->outer_points[i]->dr->y;
		changed = false;
	}
	

	// Check #3 - Z boundary
		
    if((object->outer_points[i]->r->z + object->outer_points[i]->dr->z) < -LIMIT )
	{
		object->outer_points[i]->dr->z = -LIMIT - object->outer_points[i]->r->z;
		changed = true;
	}
	else if((object->outer_points[i]->r->z + object->outer_points[i]->dr->z) > LIMIT )
	{
		object->outer_points[i]->dr->z = LIMIT - object->outer_points[i]->r->z;
		changed = true;
	}
 

	if(changed)
	{
		object->outer_points[i]->v->x =    0.5 * object->outer_points[i]->v->x;   
		object->outer_points[i]->v->y =    0.5 * object->outer_points[i]->v->y;
		object->outer_points[i]->v->z = - decay * object->outer_points[i]->v->z;   
		
	    object->outer_points[i]->r->z  = object->outer_points[i]->r->z + object->outer_points[i]->dr->z;
		changed = false;
	}



	// Check #4 - Boundary limitations


	if (object->outer_points[i]->r->x < -LIMIT) object->outer_points[i]->r->x = -LIMIT;
	if (object->outer_points[i]->r->y < -LIMIT) object->outer_points[i]->r->y = -LIMIT;
	if (object->outer_points[i]->r->z < -LIMIT) object->outer_points[i]->r->z = -LIMIT;

	if (object->outer_points[i]->r->x > LIMIT) object->outer_points[i]->r->x = LIMIT;
	if (object->outer_points[i]->r->y > LIMIT) object->outer_points[i]->r->y = LIMIT;
	if (object->outer_points[i]->r->z > LIMIT) object->outer_points[i]->r->z = LIMIT;



/////////////////////////////////////////////////////////////////////////////////////////////////////////


	
	// Check #1 - X boundaries
	if((object->inner_points[i]->r->x + object->inner_points[i]->dr->x) < -LIMIT)
	{
		object->inner_points[i]->dr->x = -LIMIT - object->inner_points[i]->r->x;
		changed = true;
	}
	else if((object->inner_points[i]->r->x + object->inner_points[i]->dr->x) > LIMIT)
	{
		object->inner_points[i]->dr->x = LIMIT - object->inner_points[i]->r->x;
		changed = true;
	} 

	if(changed)
	{
		object->inner_points[i]->v->x = -decay * object->inner_points[i]->v->x;
		object->inner_points[i]->v->y =  0.5 * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z =  0.5 * object->inner_points[i]->v->z;


		object->inner_points[i]->r->x = object->inner_points[i]->r->x + object->inner_points[i]->dr->x;
		changed = false;

	}

	
	// Check #2 - Y boundaries	
	if((object->inner_points[i]->r->y + object->inner_points[i]->dr->y) < -LIMIT)
	{
		object->inner_points[i]->dr->y = -LIMIT - object->inner_points[i]->r->y;
		changed = true;
	}
	else if((object->inner_points[i]->r->y + object->inner_points[i]->dr->y) > LIMIT)
	{
		object->inner_points[i]->dr->y = LIMIT - object->inner_points[i]->r->y;
		changed = true;
	}

	if(changed)
	{
		object->inner_points[i]->v->x =    0.5 * object->inner_points[i]->v->x;   
		object->inner_points[i]->v->y =  - decay * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z =    0.5 * object->inner_points[i]->v->z;   
		
		object->inner_points[i]->r->y  = object->inner_points[i]->r->y + object->inner_points[i]->dr->y;
		changed = false;
	}
	

	// Check #3 - Z boundary
		
    if((object->inner_points[i]->r->z + object->inner_points[i]->dr->z) < -LIMIT )
	{
		object->inner_points[i]->dr->z = -LIMIT - object->inner_points[i]->r->z;
		changed = true;
	}
	else if((object->inner_points[i]->r->z + object->inner_points[i]->dr->z) > LIMIT )
	{
		object->inner_points[i]->dr->z = LIMIT - object->inner_points[i]->r->z;
		changed = true;
	}


	if(changed)
	{
		object->inner_points[i]->v->x =    0.5 * object->inner_points[i]->v->x;   
		object->inner_points[i]->v->y =    0.5 * object->inner_points[i]->v->y;
		object->inner_points[i]->v->z = - decay * object->inner_points[i]->v->z;   
		
	    object->inner_points[i]->r->z  = object->inner_points[i]->r->z + object->inner_points[i]->dr->z;
		changed = false;
	}



	// Check #4 - Boundary limitations


	if (object->inner_points[i]->r->x < -LIMIT) object->inner_points[i]->r->x = -LIMIT;
	if (object->inner_points[i]->r->y < -LIMIT) object->inner_points[i]->r->y = -LIMIT;
	if (object->inner_points[i]->r->z < -LIMIT) object->inner_points[i]->r->z = -LIMIT;

	if (object->inner_points[i]->r->x > LIMIT) object->inner_points[i]->r->x = LIMIT;
	if (object->inner_points[i]->r->y > LIMIT) object->inner_points[i]->r->y = LIMIT;
	if (object->inner_points[i]->r->z > LIMIT) object->inner_points[i]->r->z = LIMIT;

	
}

