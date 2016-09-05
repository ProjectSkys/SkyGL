#version 330 core
layout (location = 0) in vec3 position;

// From OpenGL 4.2, you can set binding point by:
// layout (std140, binding = 0) uniform Matrices
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
}
