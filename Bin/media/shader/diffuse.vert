#version 130

in vec3 VertexPosition;
in vec3 VertexColor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 rotateMatrix;

out vec3 Color;

void main()
{
	Color =VertexColor;
	//gl_Position=vec4(VertexPosition,1.0);
	gl_Position = rotateMatrix * projectionMatrix * viewMatrix * modelMatrix * vec4(VertexPosition, 1.0);
}