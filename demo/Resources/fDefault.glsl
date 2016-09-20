#version 330 core

in vec3 colorToFrag;
in vec2 uvToFrag;

out vec4 finalColor;

void main() {
    finalColor = vec4(colorToFrag, 1.0);
}