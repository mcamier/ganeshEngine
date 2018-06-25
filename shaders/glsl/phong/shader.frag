#version 450
#extension GL_ARB_separate_shader_objects : enable
//
// INs
//
layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec3 inNormal;
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
// OUTs
//
layout(location = 0) out vec4 outColor;


float distance  = 3;
vec3 lightColor = vec3(1.0, 0.0, 0.4);
vec3 lightDirection = vec3(1.0, 0.0, -1.0);
float lightPower = 15;
vec3 materialDiffuseColor = vec3(1.0, 1.0, 1.0);


void main() {
    outColor = vec4(fragColor, 1.0);

    vec3 lightDirection_cameraspace = mat3(viewProjMat.view) * lightDirection;
    vec3 normal_cameraspace = normalize(mat3(viewProjMat.view) * mat3(modelMat.model) * inNormal);

    float cosTheta = clamp(dot(normal_cameraspace,lightDirection_cameraspace), 0, 1);
    vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
    vec3 color = materialAmbientColor + materialDiffuseColor * lightColor * lightPower * cosTheta / (distance*distance);
    outColor = vec4(color, 1.0);
}