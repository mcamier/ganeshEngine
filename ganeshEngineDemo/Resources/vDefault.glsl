#version 430 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec3 color;

out vec3 colorToFrag;

void main() {
    colorToFrag = color;
    gl_Position = vec4(vert, 1);
}