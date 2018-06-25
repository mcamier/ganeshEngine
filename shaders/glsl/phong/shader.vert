#version 450
#extension GL_ARB_separate_shader_objects : enable
//
// INs
//
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;
//
// UNIFORMs
//
layout(set = 0, binding = 0) uniform ModelTransformation {
    mat4 model;
} modelMat;

layout(set = 1, binding = 0) uniform ViewProjTransformation {
    mat4 view;
    mat4 proj;
} viewProjMat;
//
// OUT
//
out gl_PerVertex {
    vec4 gl_Position;
};
layout(location = 0) out vec3 outColor;
layout(location = 1) out vec3 outNormal;


void main() {
    gl_Position = viewProjMat.proj * viewProjMat.view * modelMat.model * vec4(inPosition, 1.0);
    outNormal = inNormal;
}