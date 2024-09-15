#version 430 core

layout(location = 0) in vec4 position;


layout(location = 1) in vec4 color;
layout(location = 2) out vec4 v_color;

layout(location = 3) out vec2 t_color;
layout(location = 4) in vec2 ti_color;

layout(location = 27) uniform mat4 u_model;
layout(location = 28) uniform mat4 u_projection;

void main()
{
    gl_Position = u_projection*u_model*position;
    v_color = color;
    t_color = ti_color;
}
