#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 vertexColor;
out vec4 glPosition;
void main()
{
    glPosition = vec4(aPos, 1.0);
    vertexColor = vec4(1.0, 0.375, 0.0, 1.0);
}