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
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inTexCoord;

layout(location = 0) out vec3 outColor;
layout(location = 1) out vec2 fragTexCoord;


float distance  = 3;
vec3 lightColor = vec3(1.0,0.0,0.4);
vec3 lightDirection = vec3(1.0,0.0, -1.0);
float lightPower = 15;
vec3 materialDiffuseColor = vec3(1.0,1.0,1.0);


void main() {
    gl_Position = viewProjMat.proj * viewProjMat.view * modelMat.model * vec4(inPosition, 1.0);

    vec3 lightDirection_cameraspace = mat3(viewProjMat.view) * lightDirection;
    vec3 normal_cameraspace = mat3(viewProjMat.view) * mat3(modelMat.model) * inNormal;

    vec3 n = normalize(normal_cameraspace);

    float cosTheta = clamp(dot(n,lightDirection_cameraspace), 0, 1);

    vec3 materialAmbientColor = vec3(0.1,0.1,0.1) * materialDiffuseColor;
    outColor = materialAmbientColor + materialDiffuseColor * lightColor * lightPower * cosTheta / (distance*distance);
    fragTexCoord = vec2(1.0, 1.0);
}