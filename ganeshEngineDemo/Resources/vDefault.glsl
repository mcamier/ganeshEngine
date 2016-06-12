#version 430 core

layout(location = 0) in vec3 ghVertex;
layout(location = 1) in vec3 ghColor;
layout(location = 2) in vec2 ghUV;
layout(location = 3) in vec3 ghNormal;

out vec3 colorToFrag;

void main() {
    colorToFrag = ghColor;
    gl_Position = vec4(ghVertex, 1);
}