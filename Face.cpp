#include "Face.h"
#include<assert.h>

// Class triface function definition
// Calculate normal vector to a triangle and its field
//##ModelId=45F4D7980066
void Face::CalNormalNField(void)
{
    // the normal can be calculated by vector cross multiply

/*    cout<<"fp1->r->x=="<<fp1->r->x<<"==fp1->r->y=="<<fp1->r->y<<"==fp1->r->z=="<<fp1->r->z<<endl;
    cout<<"fp2->r->x=="<<fp2->r->x<<"==fp2->r->y=="<<fp2->r->y<<"==fp2->r->z=="<<fp2->r->z<<endl;
    cout<<"fp3->r->x=="<<fp3->r->x<<"==fp3->r->y=="<<fp3->r->y<<"==fp3->r->z=="<<fp3->r->z<<endl;
*/


    Vector N = (*fp1->r - *fp2->r) ^ (*fp1->r - *fp3->r);
//    Vector N = (*fs1->sp1->r - *fs2->sp1->r) ^ (*fs1->sp1->r - *fs3->sp1->r);


//    cout<<"N.x=="<<N.x<<"==N.y=="<<N.y<<"==N.z=="<<N.z<<endl;
    //field = N.getLength();      // triangle field, normal vector scalar
    //assert(false);

    N.Normalize();                                   // normalize the vector

//    cout<<"after normalize==="<<"N.x=="<<N.x<<"==N.y=="<<N.y<<"==N.z=="<<N.z<<endl;
    *normal = N;                                     // as the triangle face normal vector
}
