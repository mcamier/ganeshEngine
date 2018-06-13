#version 450

layout(set = 0, binding = 0) uniform ModelTransformation {
    mat4 model;
} modelMat;

layout(set = 1, binding = 0) uniform ViewProjTransformation {
    mat4 view;
    mat4 proj;
} viewProjMat;

layout(triangles) in;
layout(location=0) in vec4 vert_normal[3];

layout(line_strip, max_vertices=6) out;
layout(location=0) out vec4 geom_color;


void main() {
    for( int vertex = 0; vertex < 3; ++vertex ) {
        gl_Position = gl_in[vertex].gl_Position;
        geom_color = vec4(1.0, 0.0, 0.0, 1.0);
        EmitVertex();

        gl_Position = (gl_in[vertex].gl_Position + normalize(vert_normal[vertex]));
        geom_color = vec4(0.0, 1.0, 0.0, 1.0);
        EmitVertex();

        EndPrimitive();
    }
}