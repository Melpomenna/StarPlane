#version 430 core

layout (location = 0) out vec4 frag_color;
layout (location = 2) in vec4 v_color;

layout (location = 3) in vec2 texture_coords;
layout (location = 30) uniform sampler2D u_texture;

void main()
{
    vec4 sampled = texture(u_texture, texture_coords);
    frag_color = sampled*v_color;   
}