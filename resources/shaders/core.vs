#version 330 core
// (For vertex position) attribute position; vector size and name
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// uniform matrix for transformation, scaling and rotating
uniform mat4 worldMatrix;
// uniform view matrix
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 colorChoice;
out vec4 vertexColor;

void main()
{
    vertexColor = colorChoice;
//    vertexColor = aColor;
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
}
