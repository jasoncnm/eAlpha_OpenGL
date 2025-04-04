#version 330


out vec4 fragColor;

in vec4 interpColor;

void main()
{
    fragColor = interpColor;
}