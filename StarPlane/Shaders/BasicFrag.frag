#version 430 core

layout(location = 0) out vec4 frag_color;
layout(location = 2) in vec4 v_color;


void main()
{
    frag_color = v_color;
}