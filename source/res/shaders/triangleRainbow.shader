#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colors;

uniform mat4 u_MVP;
out vec4 ourColor;

void main()
{
    gl_Position = u_MVP * position;
    ourColor = colors;
}

#shader fragment
#version 330 core

out vec4 FragColor;
in vec4 ourColor;

void main()
{
    FragColor = ourColor;
}