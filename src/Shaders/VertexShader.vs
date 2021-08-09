#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

//Outputs the color for the Fragment Shader
out vec3 color;

out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
   //Outputs the positions/coordinates of all vertices
   gl_Position = camMatrix * vec4(aPos, 1.0);
   //Assigns the color from the Vertex Data to "color"
   color = aColor;
   //Assigns the texture coordinates from the Vertex Data ti "texCoord"
   texCoord = aTex;
}