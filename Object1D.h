#ifndef OBJECT1D_H
#define OBJECT1D_H

#include "Object.h"

//##ModelId=45F4D79701B7
class Object1D : public Object
{
public:
    //##ModelId=45F4D79701B9
    Object1D();                    // object1D constructor
    //##ModelId=45F4D79701BA
    virtual ~Object1D();            // object1D destructor
    //##ModelId=45F4D79701C7
    virtual void Draw(int shaderID, glm::mat4 worldMatrix);            // display object1D
//    virtual void FindClosestPoint(void);

private:
    void createVertexArray();
    void updateVertexArray();
    glm::vec3 vertexArrayData[4];    // object 1D only needs 4 data points
    //model the object1D with structural spring
    //##ModelId=45F4D79701C9
    void Add_Structural_Spring(int index, int head, int tail);
    GLuint VAO;
    GLuint VBO;
protected:
    //##ModelId=45F4D79701CD
    virtual void SetObject();        // construct the object1D
    
};

#endif /* OBJECT1D_H */
