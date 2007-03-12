#ifndef VIEWSPACE_H
#define VIEWSPACE_H

#include "Vector.h"

// A 3D space containing the balls


//##ModelId=45F4D79602F2
class ViewSpace       					// constructor
{
public:
	//##ModelId=45F4D79602F3
	ViewSpace()
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

	//##ModelId=45F4D79602F4
	~ViewSpace()					// destructor
	{
		for(int i = 0; i < 8; i++)
		{
			delete spaceVertex[i];
		}
	}
     
	//##ModelId=45F4D79602F5
	void Draw(void);
	   
public:
	//##ModelId=45F4D7960300
	Vector* spaceVertex[8];
};


#endif
