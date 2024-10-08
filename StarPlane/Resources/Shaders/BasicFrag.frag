#version 430 core

layout(location = 0) out vec4 frag_color;
layout(location = 2) in vec4 v_color;

layout(location = 3) in vec2 t_color;
layout (location = 30) uniform sampler2D u_texture;

void main()
{   
    vec4 texture_color = texture(u_texture, t_color);
    frag_color = texture_color*v_color;
}