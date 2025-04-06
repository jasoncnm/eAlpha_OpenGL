#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

uniform mat4 VP;

out vec4 interpColor;

void main()
{
   interpColor = color;
   gl_Position = VP * vec4(position, 1.0);
}
