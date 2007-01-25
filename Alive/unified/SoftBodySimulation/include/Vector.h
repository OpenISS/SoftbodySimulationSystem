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
		cout << "vector's getting born: x=" << x << ",y=" << y << ",z=" << z << endl;
  }

/*
	Vector()	 
  { x=1;
	y=1;
	z=1;  
		cout << "vector's getting born: x=" << x << ",y=" << y << ",z=" << z << endl;
  }
*/

	~Vector()
	{
		cout << "vector's dying: x=" << x << ",y=" << y << ",z=" << z << endl;
	}            // destructor
	
		 // Computation operators.
		 
	Vector& operator+ (Vector const &);   // #1 fcn - Vector addition
//    Vector& operator+ (Vector &);   // #1 fcn - Vector addition
//	Vector& operator- (Vector const &);   // #2 fcn - Vector subtraction
//	Vector operator- (Vector const &, Vector const &);   // #2 fcn - Vector subtraction
	friend Vector operator- (const Vector & p, const Vector & q);   // #2 fcn - Vector subtraction
	Vector& operator* (float);		     // #3 fcn - Vector by a scalar
//	Vector& operator% (Vector const &);	 // #4 fcn - Vector cross multiply 
	float  operator* (Vector const &); // #6 fcn - Vector dot multiply
	void   operator= (Vector const &); // #7 fcn - Vector assign	
	
//	Vector operator=(Vector const &K)   // fcn #6 - Vector assign operator

	bool     operator==(Vector const &); // #8 fcn - Vector equal
	Vector& operator/ (int);		     // #3 fcn - Vector by a scalar



//	Vector& operator*(float s, Vector &v); // 2 parameters, Vector + scalar  

	
		 // Vector length.
	inline float getLength() { 
	/*	cout<<"this.x="<<this->x<<endl;
		cout<<"this.y="<<this->y<<endl;
		cout<<"this.z="<<this->z<<endl;
		cout<<"sqrt="<<sqrt((this->x)*(this->x)+(this->y) * (this->y)+(this->z)*(this->z))<<endl;
	*/	return sqrt((this->x)*(this->x)+(this->y) * (this->y)+(this->z)*(this->z)); }
		
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


	 