#ifndef VECTOR_H
#define VECTOR_H

#include "global.h"

//Vector class is employed to store and operate on x, y, z coordinates,
//for particle position, particel velocity, or force information in their repective spaces



//##ModelId=45F4D796031E
class Vector
{

public:

    //##ModelId=45F4D796031F
    Vector(float Ax=0,float Ay=0,float Az=0):                 // constructor with variables, Ax, Ay, Az
                x(Ax),y(Ay),z(Az)                    // default Vector(0,0,0)
      {
    //    cout << "vector's getting born: x=" << x << ",y=" << y << ",z=" << z << endl;
    }


    //##ModelId=45F4D7960331
    ~Vector()                                     // destructor
    {
    //    cout << "vector's dying: x=" << x << ",y=" << y << ",z=" << z << endl;
    }
    

    // Computation operators.
         
    //Vector& operator+ (Vector const &);                                // #1 fcn - Vector addition with a vector to itself
    //Vector& operator+ (float);                                        // #1 fcn - Vector addition for a vector and a float
    //##ModelId=45F4D796039D
    friend Vector operator+ (const Vector & p, const Vector & q);                // #1 fcn - Vector addition for two vectors


    //Vector& operator- (Vector const &);                                // #2 fcn - Vector subtraction with a vector to itself
    //Vector& operator- (float);                                        // #2 fcn - Vector subtraction for a vector and a float
    //##ModelId=45F4D79603AE
    friend Vector operator- (const Vector & p, const Vector & q);                   // #2 fcn - Vector subtraction for two vectors

    //##ModelId=45F4D7960332
    Vector& operator* (Vector const &);                                    // #3 fcn - Vector multiplication
    //##ModelId=45F4D7960334
    Vector& operator* (float);                                        // #3 fcn - Vector multiplication for a vector and a float
    //##ModelId=45F4D79603B2
    friend Vector operator* (const Vector & p, const Vector & q);                   // #3 fcn - Vector multiplication for two vectors


//    Vector& operator/ (Vector const &);                                    // #4 fcn - Vector division with a vector to itself
//    Vector& operator/ (float);                                        // #4 fcn - Vector division for a vector and a float

    //##ModelId=45F4D79603BC
    friend Vector operator/ (const Vector & p, const Vector & q);                   // #4 fcn - Vector division for two vectors


    //##ModelId=45F4D79603C0
    friend Vector operator^ (Vector const &, Vector const &);                    // #5 fcn - Vector cross product, results in a vector

//    friend Vector operator^ (Vector const &, Vector const &);                    // #6 fcn - Vector dot product, results in a scalar


    //##ModelId=45F4D796033E
    Vector&  operator= (Vector const &);                                // #7 fcn - Vector assign operator

    //##ModelId=45F4D7960340
    bool     operator==(Vector const &);                                // #8 fcn - Vector equal operator

        
    //##ModelId=45F4D7960342
    inline float getLength()                                        // get vector length
    {
        return sqrt((this->x)*(this->x)+(this->y) * (this->y)+(this->z)*(this->z));
    }
        
         
    //##ModelId=45F4D7960343
    inline void Normalize()                                            //  Normalize the Vector
    {
        float d = getLength();                                        // its length

//        cout<<"d="<<d<<endl;

        if(d !=0)    *this = (*this) * (1.0f/d);
        //cout<<"this.x--"<<this
    }

    

public:

    //##ModelId=45F4D796034D
    float x;                                                    // x-coordinate
    //##ModelId=45F4D796039B
    float y;                                                    // y-coordinate
    //##ModelId=45F4D796039C
    float z;                                                    // z-coordinate

};


#endif


     
