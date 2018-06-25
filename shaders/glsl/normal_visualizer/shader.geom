#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(triangles) in;
layout(location=0) in vec4 vert_normal[3];


layout(set = 1, binding = 0) uniform ViewProjTransformation {
    mat4 view;
    mat4 proj;
} viewProjMat;


layout(line_strip, max_vertices=6) out;
layout(location=0) out vec4 vertex_color;


void main() {
int i;

  for(i=0; i<3; i++)
  {
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vert_normal[i].xyz;

    gl_Position = viewProjMat.proj * vec4(P, 1.0);
    vertex_color = vec4(1, 1, 1, 1);
    EmitVertex();

    gl_Position = viewProjMat.proj * vec4(P + N * 0.5, 1.0);
    vertex_color = vec4(1, 1, 1, 1);
    EmitVertex();

    EndPrimitive();
  }

}