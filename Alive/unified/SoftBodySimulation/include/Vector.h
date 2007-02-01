#ifndef VECTOR_H
#define VECTOR_H

#include "global.h"

//  Vector class is employed to store and operate on 3d coordinates, for point 
//  position, velocity, or force information in their repective spaces 

class Vector
{

public:

	Vector(float Ax=0,float Ay=0,float Az=0):
	  x(Ax),y(Ay),z(Az)  // constructor with variables, Ax, Ay, Az
		                   // default Vector(0,0,0)  
  {
	//	cout << "vector's getting born: x=" << x << ",y=" << y << ",z=" << z << endl;
  }


	~Vector()
	{
	//	cout << "vector's dying: x=" << x << ",y=" << y << ",z=" << z << endl;
	}            // destructor
	
		 // Computation operators.
		 
//	Vector& operator+ (Vector const &);   // #1 fcn - Vector addition
//  Vector& operator+ (float);   // #1 fcn - Vector addition
	friend Vector operator+ (const Vector & p, const Vector & q); 

	//Vector& operator- (Vector const &);   // #2 fcn - Vector subtraction
	//Vector& operator- (float); 
	friend Vector operator- (const Vector & p, const Vector & q);   // #2 fcn - Vector subtraction

//	Vector& operator* (Vector const &);   // #2 fcn - Vector subtraction
//	Vector& operator* (float); 
	friend Vector operator* (const Vector & p, const Vector & q);   // #2 fcn - Vector subtraction

//	Vector& operator/ (Vector const &);   // #2 fcn - Vector subtraction
//	Vector& operator/ (float); 
	friend Vector operator/ (const Vector & p, const Vector & q);   // #2 fcn - Vector subtraction

	friend Vector operator% (Vector const &, Vector const &);

	Vector&  operator= (Vector const &); // #7 fcn - Vector assign	
	

	bool     operator==(Vector const &); // #8 fcn - Vector equal



	
		 // Vector length.
	inline float getLength() { 
	return sqrt((this->x)*(this->x)+(this->y) * (this->y)+(this->z)*(this->z)); }
		
		//  Normalize Vector.		 
	inline void Normalize()
	{
		float d = getLength(); // its length

		cout<<"d="<<d<<endl;

		if(d !=0)
			*this = (*this) * (1.0f/d);
	}

public:

	float x;				// x-coordinate
	float y;				// y-coordinate
	float z;				// z-coordinate

};


#endif


	 