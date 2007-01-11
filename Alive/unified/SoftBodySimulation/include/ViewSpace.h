
#ifndef VIEWSPACE_H
#define VIEWSPACE_H

#include "Vector.h"




// A 3D space containing the balls


class ViewSpace       // constructor
{
public:
/*	ViewSpace()
		 {
          spaceVertex[0]= new Vector( LIMIT, -LIMIT,  LIMIT);
          spaceVertex[1]= new Vector( LIMIT, -LIMIT, -LIMIT);
          spaceVertex[2]= new Vector(-LIMIT, -LIMIT, -LIMIT);
          spaceVertex[3]= new Vector(-LIMIT, -LIMIT,  LIMIT);

          spaceVertex[4]= new Vector( LIMIT,  LIMIT,  LIMIT);
          spaceVertex[5]= new Vector( LIMIT,  LIMIT, -LIMIT);
          spaceVertex[6]= new Vector(-LIMIT,  LIMIT, -LIMIT);
          spaceVertex[7]= new Vector(-LIMIT,  LIMIT,  LIMIT);           
		 }

	~ViewSpace()
	{
		for(int i = 0; i < 8; i++)
		{
			delete spaceVertex[i];
		}
	}
     */
	  void Rotate(void);
      void Draw(void);
	   
public:
//	Vector* spaceVertex[8];
};


#endif