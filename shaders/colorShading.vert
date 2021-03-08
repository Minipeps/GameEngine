#version 150
/*
 * The vertex shader operates on each vertex.
 */

// Input data from the VBO.
in vec2 vertexPosition;
in vec2 vertexUV;
in vec4 vertexColor;

out vec2 fragmentPosition;
out vec2 fragmentUV;
out vec4 fragmentColor;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
    
    fragmentPosition = vertexPosition;
    
    fragmentColor = vertexColor;
    
    fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}