#include "Face.h"


// Class triface function definition
// Calculate normal vector to a triangle and its field 
	 
void Face::CalNormalNField(void)
{
	// the normal can be calculated by vector cross multiply

	Vector N = (fp1->r - fp2->r) % (fp1->r - fp3->r);

	//field = N.getLength();  	// triangle field, normal vector scalar 

	N.Normalize();              // normalize the vector
	*normal = N;                 // as the triangle face normal vector
}
