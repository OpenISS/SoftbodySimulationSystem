

#include <cmath>
#include "Vector.h"



// Class Vector number functions

Vector& Vector::operator+ (Vector const &K)    // fcn #1 - Vectors addition
{

	x+=K.x;
	y+=K.y;
	z+=K.z;
	return *this;
	
}




Vector& Vector::operator- (Vector const &K)    // fcn #2 - Vectors subtraction
{
	x-=K.x;
	y-=K.y;
	z-=K.z;
	
	return *this;
}



Vector& Vector::operator* (float s)    // fcn #3 - multiply by a scalar (R * s) 
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
	//return new Vector(x*s, y*s, z*s));
}

Vector& Vector::operator / (int k)
{
	x/=k;
	y/=k;
	z/=k;
	return *this;


}

float Vector::operator* (Vector const &K)      // fcn #4 - Vectors dot product (R * K)
{
	return (x*K.x, y*K.y, z*K.z);
}

/*
Vector& Vector::operator% (Vector const &K)   // fcn #5 - Vectors cross product (R % K)
{	
	return Vector(y*K.z - z*K.y, z*K.x - x*K.z, x*K.y - y*K.x);
}
*/

void Vector::operator=(Vector const &K)   // fcn #6 - Vector assign operator
{
	x = K.x;
	y = K.y;
	z = K.z;
}

/*
Vector Vector::operator=(Vector const &K)   // fcn #6 - Vector assign operator
{
	return Vector(K.x, K.y, K.z);
}
*/
  
bool Vector::operator==(Vector const &K)    // fcn #7 - Vector equalization operator
	  {
			if(x == K.x)
			if(y == K.y)
			if(z == K.z)
				return true;

			return false;
	  }
/*
 Vector& Vector operator* (float s, Vector const &v)  // fcn #8 - 2 parameters (s * R)
{
	 x=v.x*s;
	 y=v.y*s;
	 z=v.z*s;
	return *this;
}
*/





