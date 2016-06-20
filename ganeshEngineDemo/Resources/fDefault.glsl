#version 430 core

in vec3 colorToFrag;
in vec3 uvToFrag;

out vec4 finalColor;

void main() {
    finalColor = vec4(colorToFrag, 1.0);
}