#version 430 core

layout (location = 0) in vec4 position;

layout(location = 1) in vec4 color;
layout(location = 2) out vec4 v_color;

layout (location = 3) out vec2 texture_coords;

layout(location = 27) uniform mat4 u_model;
layout(location = 28) uniform mat4 u_projection;

void main()
{
    gl_Position = u_model*u_projection*vec4(position.x,position.y, 0.0,1.0);
    v_color = color;
    texture_coords = vec2(position.z,position.w);

}