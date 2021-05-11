#include "Object1D.h"
#include <vector>
//##ModelId=45F4D79701B9
Object1D::Object1D()
{
    SetObject();
    dim = DIM1D;
    // added
    createVertexArray();
}


//##ModelId=45F4D79701BA
Object1D::~Object1D()
{
}

void Object1D::createVertexArray(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArrayData), vertexArrayData, GL_DYNAMIC_DRAW);
    
    // set attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Object1D::updateVertexArray(){
    // update the vertex array and upload the data to buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // the actual object
    vertexArrayData[0] = glm::vec3(outer_springs[0]->sp1->r->x,outer_springs[0]->sp1->r->y, 0.0f);
    vertexArrayData[1] = glm::vec3(outer_springs[0]->sp2->r->x,outer_springs[0]->sp2->r->y, 0.0f);
    
    // integrator point
    if(integrator != nullptr){
        vertexArrayData[2] = glm::vec3(integrator->mDragX, integrator->mDragY, 0.0f);
        vertexArrayData[3] = glm::vec3(outer_points[closest_i]->r->x,outer_points[closest_i]->r->y, 0.0f);
    }
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexArrayData), vertexArrayData);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArrayData), (void*)vertexArrayData, GL_DYNAMIC_DRAW);

}

//##ModelId=45F4D79701C7
void Object1D::Draw(int shaderID, glm::mat4 worldMatrix)
{
    static bool findOnce = false;
    
    
    // draw object1D itself (one line and two points)
    
    // update the buffer data
    updateVertexArray();
    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set world matrix
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "worldMatrix"), 1, GL_FALSE, &worldMatrix[0][0]);
    // get color location
    GLuint ColorLocation = glGetUniformLocation(shaderID, "colorChoice");
    glDisable(GL_CULL_FACE);
    // set color and draw
    // draw line
    glEnableClientState(GL_VERTEX_ARRAY);
    glUniform4f(ColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
    glDrawArrays(GL_LINES, 0, 2);
    // draw points
    glPointSize(10.0f);
    glDrawArrays(GL_POINTS, 0, 2);
    
    
        if(integrator != nullptr)
        {
            if(integrator->dragExists)
            {
                if(findOnce == true)
                {
                    FindClosestPoint();
                    findOnce = false;
                }
                glUniform4f(ColorLocation, 1.0f, 1.0f, 0.0f, 1.0f);
                glDrawArrays(GL_LINES, 2, 2);
            }
            else
            {
                FindClosestPoint();
                findOnce = true;
            }

        }
 


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glEnable(GL_CULL_FACE);
  
}

//====================================================================

//##ModelId=45F4D79701C9
void Object1D::Add_Structural_Spring(int index, int head, int tail)
{

    outer_springs.push_back( new Spring(outer_points[head],outer_points[tail]));
    inner_springs.push_back( new Spring());

 /*      outer_springs[index].sp1 = &outer_points[head];
    outer_springs[index].sp2 = &outer_points[tail];

      inner_springs[index].sp1 = new Particle();
    inner_springs[index].sp2 = new Particle();

    outer_springs[index].setRestLen();
    */
    inner_springs[index]->setRestLen();
    outer_springs[index]->setRestLen();
}


//================================================================
//##ModelId=45F4D79701CD
void Object1D::SetObject()
{


    int PosX = 0;
    int PosY = 0;
    int i;
//    cout<<"numParticles---1D------"<<numParticles<<endl;
    for(i=0; i<numParticles; i++)        // create NUMP points into 2D circle
    {
/*        if (i==0)
    outer_points.push_back( new Particle(new Vector(0,0,0), MASS));
        else
*/
    outer_points.push_back( new Particle(new Vector(PosX,PosY,0), MASS));
    inner_points.push_back( new Particle());
    /*    outer_points[i].r->x += PosX ;   // outer X coordiation
        outer_points[i].r->y += PosY;   // outer Y coordiation
        outer_points[i].mass =  MASS;
    */
        PosY += 2;
    }


    for(i=0; i<1 ;i++)           // NUMP-1 springs from 1st to the NUMP for outer & inner
    {
        Add_Structural_Spring(i, i, (i+1) % numParticles);
    }
}


//=======================================================
/*
void Object1D::FindClosestPoint(void)
{
    float dmin = 0;
    float mousepointd = 0;
    int i;

    // find closest point
    dmin = sqrt(pow(outer_points[closest_i]->r->x - integrator->mDragX,2) + pow(outer_points[closest_i]->r->y - integrator->mDragY,2));

    for(i=0; i<numParticles; i++)
    {
        mousepointd = sqrt(    pow(outer_points[i]->r->x - integrator->mDragX,2) +
                            pow(outer_points[i]->r->y - integrator->mDragY,2));
        if(mousepointd < dmin)
        {
            dmin = mousepointd;
            closest_i = i;
        }
    }

    cout<<"    closest_i=="<<    closest_i<<endl;
}*/
