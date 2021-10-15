#version 330 core

layout (location = 0) in vec4 v_pos;
layout (location = 1) in vec3 v_color;

out vec3 fragColor;

uniform mat4 u_mvp;

void main() {

    fragColor = v_color;
    gl_Position = u_mvp * v_pos;
}
