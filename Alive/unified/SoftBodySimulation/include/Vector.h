#ifndef VECTOR_H
#define VECTOR_H

#include "global.h"

//Vector class is employed to store and operate on x, y, z coordinates, 
//for particle position, particel velocity, or force information in their repective spaces 



class Vector
{

public:

	Vector(float Ax=0,float Ay=0,float Az=0):	 // constructor with variables, Ax, Ay, Az
	       x(Ax),y(Ay),z(Az)					 // default Vector(0,0,0)  
		                   
  {
	//	cout << "vector's getting born: x=" << x << ",y=" << y << ",z=" << z << endl;
  }


	~Vector()									 // destructor
	{
	//	cout << "vector's dying: x=" << x << ",y=" << y << ",z=" << z << endl;
	}            
	

	// Computation operators.
		 
//	Vector& operator+ (Vector const &);								// #1 fcn - Vector addition
//  Vector& operator+ (float);										// #1 fcn - Vector addition
	friend Vector operator+ (const Vector & p, const Vector & q);	// #1 fcn - Vector addition


	//Vector& operator- (Vector const &);							// #2 fcn - Vector subtraction
	//Vector& operator- (float);									// #2 fcn - Vector subtraction
	friend Vector operator- (const Vector & p, const Vector & q);   // #2 fcn - Vector subtraction

//	Vector& operator* (Vector const &);								// #3 fcn - Vector multiplication
//	Vector& operator* (float);										// #3 fcn - Vector multiplication
	friend Vector operator* (const Vector & p, const Vector & q);   // #3 fcn - Vector multiplication

//	Vector& operator/ (Vector const &);								// #4 fcn - Vector division
//	Vector& operator/ (float);										// #4 fcn - Vector division
	friend Vector operator/ (const Vector & p, const Vector & q);   // #4 fcn - Vector division


	friend Vector operator% (Vector const &, Vector const &);		// #5 fcn - Vector cross product, results in a vector 

	friend double operator^ (Vector const &, Vector const &);		// #6 fcn - Vector dot product, results in a scalar


	Vector&  operator= (Vector const &);							// #7 fcn - Vector assign	

	bool     operator==(Vector const &);							// #8 fcn - Vector equal

		
	inline float getLength()										// Vector length.
	{ 
		return sqrt((this->x)*(this->x)+(this->y) * (this->y)+(this->z)*(this->z)); 
	}
		
		 
	inline void Normalize()											//  Normalize Vector.	
	{
		float d = getLength();										// its length

		cout<<"d="<<d<<endl;

		if(d !=0)	*this = (*this) * (1.0f/d);
	}

	

public:

	float x;														// x-coordinate
	float y;														// y-coordinate
	float z;														// z-coordinate

};


#endif


	 