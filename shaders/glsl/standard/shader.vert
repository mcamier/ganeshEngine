#version 450
#extension GL_ARB_separate_shader_objects : enable

out gl_PerVertex {
    vec4 gl_Position;
};

layout(set = 0, binding = 0) uniform ModelTransformation {
    mat4 model;
} modelMat;

layout(set = 1, binding = 0) uniform ViewProjTransformation {
    mat4 view;
    mat4 proj;
} viewProjMat;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inColor;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;


void main() {
    gl_Position = viewProjMat.proj * viewProjMat.view * modelMat.model * vec4(inPosition, 1.0);
    //fragColor = vec3(1.0, 1.0, 0.0);
    fragTexCoord = vec2(1.0, 1.0);

    vec3 viewModelNormal = mat3(viewProjMat.view * modelMat.model) * inNormal;
    fragColor = vec3(max(0.0, dot(viewModelNormal, vec3(0.58, 0.58, 0.58))) + 0.1);

}