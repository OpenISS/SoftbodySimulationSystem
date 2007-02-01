#include <cmath>
#include "Vector.h"



// Class Vector number functions

Vector operator+ (const Vector &K, const Vector &N)    // fcn #2 - Vectors subtraction
{
	return Vector(K.x + N.x, K.y + N.y, K.z + N.z);
}
/*
Vector& Vector::operator+ (Vector const &K)    // fcn #1 - Vectors addition
{

	x+=K.x;
	y+=K.y;
	z+=K.z;
	return *this;
	
}

Vector& Vector::operator+ (float s)    // fcn #2 - Vectors subtraction
{
	x+=s;
	y+=s;
	z+=s;
	return *this;
}*/
//////////////////////////////////////////////////////////////////////

Vector operator- (const Vector &K, const Vector &N)    // fcn #2 - Vectors subtraction
{
	return Vector(K.x - N.x, K.y - N.y, K.z - N.z);
}
/*
Vector& Vector::operator- (Vector const &K)    // fcn #2 - Vectors subtraction
{
	x-=K.x;
	y-=K.y;
	z-=K.z;
	return *this;
}

Vector& Vector::operator- (float s)    // fcn #2 - Vectors subtraction
{
	x -= s;
	y -= s;
	z -= s;
	return *this;
}
*/

//////////////////////////////////////////////////////////////////////////
Vector operator* (const Vector &K, const Vector &N)    // fcn #2 - Vectors subtraction
{
	return Vector(K.x * N.x, K.y * N.y, K.z * N.z);
}
/*
Vector& Vector::operator* (Vector const &K)    // // fcn #4 - Vectors dot product (R * K)
{
	x*=K.x;
	y*=K.y;
	z*=K.z;
	return *this;
}

Vector& Vector::operator* (float s)    // fcn #3 - multiply by a scalar (R * s) 
{
	x *= s;
	y *= s;
	z *= s;
	return *this;

}
*/
////////////////////////////////////////////////////////////////
Vector operator/ (const Vector &K, const Vector &N)    // fcn #2 - Vectors subtraction
{
	return Vector(K.x / N.x, K.y / N.y, K.z / N.z);
}
/*
Vector& Vector::operator/ (Vector const &K)    // fcn #2 - Vectors subtraction
{
	x/=K.x;
	y/=K.y;
	z/=K.z;
	return *this;
}
Vector& Vector::operator / (float k)
{
	x/=k;
	y/=k;
	z/=k;
	return *this;
}
*/
////////////////////////////////////////////////////////


Vector operator% (Vector const &R, Vector const &K)   // fcn #5 - Vectors cross product (R % K)
{	
	return Vector(R.y*K.z - R.z*K.y, R.z*K.x - R.x*K.z, R.x*K.y - R.y*K.x);
}


//////////////////////////////////////////////////////////////

Vector& Vector::operator=(Vector const &K)   // fcn #6 - Vector assign operator
{
	x=K.x;
	y=K.y;
	z=K.z;
	return *this;
}



////////////////////////////////////////////////////////////  
bool Vector::operator==(Vector const &K)    // fcn #7 - Vector equalization operator
{
	if(x == K.x)
		if(y == K.y)
			if(z == K.z)
				return true;

	return false;
}





