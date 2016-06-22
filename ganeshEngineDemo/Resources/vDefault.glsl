#version 330 core

uniform mat4 gh_u_modelview_mat;
uniform mat4 gh_u_projection_mat;
uniform mat4 gh_u_eye_mat;

layout(location = 0) in vec3 ghVertex;
layout(location = 1) in vec3 ghColor;
layout(location = 2) in vec2 ghUV;
layout(location = 3) in vec3 ghNormal;

out vec3 colorToFrag;
out vec2 uvToFrag;

void main() {
    uvToFrag = ghUV;
    colorToFrag = ghColor;
    gl_Position = gh_u_modelview_mat * vec4(ghVertex, 1);
}