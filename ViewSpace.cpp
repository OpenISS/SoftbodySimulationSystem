#include "ViewSpace.h"
#include "global.h"
using namespace glm;

void ViewSpace::createVertexArrayObject()
{
    // put all the data into vertex array
    int f = 0, c = 4, b = 1, r = 0, l = 2;
    vec3 vertexArray[] = {
        // floor
        // [color = glColor4f(1, 0.5, 0.1, 0.5)] [normal = (0, 1, 0)]
        vec3(spaceVertex[f]->x, spaceVertex[f]->y, spaceVertex[f]->z),
        vec3(spaceVertex[f+1]->x, spaceVertex[f+1]->y, spaceVertex[f+1]->z),
        vec3(spaceVertex[f+2]->x, spaceVertex[f+2]->y, spaceVertex[f+2]->z),
        vec3(spaceVertex[f+3]->x, spaceVertex[f+3]->y, spaceVertex[f+3]->z),
        
        // ceiling
        // [color = glColor4f(1, 0.5, 0.1, 0.5)] [normal = (0, -1, 0)]
        vec3(spaceVertex[c]->x, spaceVertex[c]->y, spaceVertex[c]->z),
        vec3(spaceVertex[c+1]->x, spaceVertex[c+1]->y, spaceVertex[c+1]->z),
        vec3(spaceVertex[c+2]->x, spaceVertex[c+2]->y, spaceVertex[c+2]->z),
        vec3(spaceVertex[c+3]->x, spaceVertex[c+3]->y, spaceVertex[c+3]->z),
        
        // back wall
        // [color = glColor4f(0, 0, 1, 0.5)] [normal = (0,0,1)]
        vec3(spaceVertex[b]->x, spaceVertex[b]->y, spaceVertex[b]->z),
        vec3(spaceVertex[b+1]->x, spaceVertex[b+1]->y, spaceVertex[b+1]->z),
        vec3(spaceVertex[b+5]->x, spaceVertex[b+5]->y, spaceVertex[b+5]->z),
        vec3(spaceVertex[b+4]->x, spaceVertex[b+4]->y, spaceVertex[b+4]->z),
        
        // right wall
        // [color = glColor4f(0.5, 0.9, 0.1, 0.5)] [normal = (-1, 0, 0)]
        vec3(spaceVertex[r]->x, spaceVertex[r]->y, spaceVertex[r]->z),
        vec3(spaceVertex[r+1]->x, spaceVertex[r+1]->y, spaceVertex[r+1]->z),
        vec3(spaceVertex[r+5]->x, spaceVertex[r+5]->y, spaceVertex[r+5]->z),
        vec3(spaceVertex[r+4]->x, spaceVertex[r+4]->y, spaceVertex[r+4]->z),
        
        // left wall
        // [color = glColor4f(0.5, 0.9, 0.1, 0.5)] [normal = (1, 0, 0)]
        vec3(spaceVertex[l]->x, spaceVertex[l]->y, spaceVertex[l]->z),
        vec3(spaceVertex[l+1]->x, spaceVertex[l+1]->y, spaceVertex[l+1]->z),
        vec3(spaceVertex[l+5]->x, spaceVertex[l+5]->y, spaceVertex[l+5]->z),
        vec3(spaceVertex[l+4]->x, spaceVertex[l+4]->y, spaceVertex[l+4]->z)
    };
    
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // since the box doesn't change, use static draw
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);
    
    // set attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//##ModelId=45F4D79602F5
void ViewSpace::Draw(int shaderID)    // Draw the view space
{    
    glBindVertexArray(VAO);
    
    // set world matrix
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "worldMatrix"), 1, GL_FALSE, &mat4(1.0f)[0][0]);
    // get color location
    GLuint ColorLocation = glGetUniformLocation(shaderID, "colorChoice");
    glDisable(GL_CULL_FACE);
    // set color and draw
    // floor
    glEnableClientState(GL_VERTEX_ARRAY);
    glUniform4f(ColorLocation, 1, 0.5, 0.1, 0.5);
    // TODO: I don't know why GL_QUAD is not working, but GL_TRIANGLE_FAN is working
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    // draw ceiling
    glUniform4f(ColorLocation, 1, 0.5, 0.1, 0.5);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 4);
    // draw backwall
    glUniform4f(ColorLocation, 0, 0, 1, 0.5);
    glDrawArrays(GL_TRIANGLE_FAN, 8, 4);
    // draw right wall
    glUniform4f(ColorLocation, 0.5, 0.9, 0.1, 0.5);
    glDrawArrays(GL_TRIANGLE_FAN, 12, 4);
    // draw left wall
    glUniform4f(ColorLocation, 0.5, 0.9, 0.1, 0.5);
    glDrawArrays(GL_TRIANGLE_FAN, 16, 4);
    
    glEnable(GL_CULL_FACE);
    glBindVertexArray(0);
}
