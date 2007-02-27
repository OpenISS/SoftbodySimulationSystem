#include <cmath>
#include<assert.h>
#include "Vector.h"


// Class Vector member functions

Vector operator+ (const Vector &K, const Vector &N)				// #1 fcn - Vector addition for two vectors
{
	cout<<"vecotr +"<<endl;
	return Vector(K.x + N.x, K.y + N.y, K.z + N.z);
}
/*
Vector& Vector::operator+ (Vector const &K)					// #1 fcn - Vector addition with a vector to itself
{

	x+=K.x;
	y+=K.y;
	z+=K.z;
	return *this;
	
}

Vector& Vector::operator+ (float s)							// #1 fcn - Vector addition for a vector and a float
{
	x+=s;
	y+=s;
	z+=s;
	return *this;
}*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector operator- (const Vector &K, const Vector &N)				// #2 fcn - Vector subtraction for two vectors
{
//	cout<<"vecotr -"<<endl;
	return Vector(K.x - N.x, K.y - N.y, K.z - N.z);
}
/*
Vector& Vector::operator- (Vector const &K)					// #2 fcn - Vector subtraction with a vector to itself
{
	x-=K.x;
	y-=K.y;
	z-=K.z;
	return *this;
}

Vector& Vector::operator- (float s)							// #2 fcn - Vector subtraction for a vector and a float
{
	x -= s;
	y -= s;
	z -= s;
	return *this;
}
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector operator* (const Vector &K, const Vector &N)		   		 // #3 fcn - Vector multiplication for two vectors
{
{
//	cout<<"vector *"<<endl;
	return Vector(K.x * N.x, K.y * N.y, K.z * N.z);
}

Vector& Vector::operator* (Vector const &K)				    	// #3 fcn - Vector multiplication with a vector to itself
{
	//cout<<"call this one 2"<<endl;
	
	x*=K.x;
	y*=K.y;
	z*=K.z;
	return *this;
}

Vector& Vector::operator* (float s)							// #3 fcn - Vector multiplication for a vector and a float
{
	//cout<<"call this one 1"<<endl;
	x *= s;
	y *= s;
	z *= s;
	return *this;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector operator/ (const Vector &K, const Vector &N)				// #4 fcn - Vector division for two vectors

{
//	cout<<"vecotr /"<<endl;
	return Vector(K.x / N.x, K.y / N.y, K.z / N.z);
}
/*
Vector& Vector::operator/ (Vector const &K)					// #4 fcn - Vector division with a vector to itself
{
	x/=K.x;
	y/=K.y;
	z/=K.z;
	return *this;
}
Vector& Vector::operator / (float k)						// #4 fcn - Vector division for a vector and a float
{
	x/=k;
	y/=k;
	z/=k;
	return *this;
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Vector operator^ (Vector const &R, Vector const &K)				// #5 fcn - Vector cross product, results in a vector 
{	
	return Vector(R.y*K.z - R.z*K.y, R.z*K.x - R.x*K.z, R.x*K.y - R.y*K.x);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
Vector operator^ (Vector const &R, Vector const &K)				// #6 fcn - Vector dot product, results in a scalar.
{	

	return (R.x*K.x + R.y*K.y + R.z*K.z);
}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vector& Vector::operator=(Vector const &K)					// #7 fcn - Vector assign operator	
{
	x = K.x;
	y = K.y;
	z = K.z;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
bool Vector::operator==(Vector const &K)    					// fcn #7 - Vector equalization operator
{
	if(x == K.x)
		if(y == K.y)
			if(z == K.z)
				return true;
	return false;
}





