#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;


layout(set = 0, binding = 0) uniform ModelTransformation {
    mat4 model;
} modelMat;

layout(set = 1, binding = 0) uniform ViewProjTransformation {
    mat4 view;
    mat4 proj;
} viewProjMat;


out gl_PerVertex {
    vec4 gl_Position;
};

layout(location = 0) out vec4 vert_normal;


void main() {
    mat4 mv = viewProjMat.view * modelMat.model;

    gl_Position = mv * vec4(inPosition, 1.0);
    vert_normal = vec4(mat3(mv) * inNormal *0.1, 0.0);

}