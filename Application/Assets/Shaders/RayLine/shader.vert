#version 450 core

layout (location = 0) in vec3 inPosition;

layout(binding = 0) uniform Camera {
    mat4 view;
    mat4 proj;
} camera;

void main()
{
	gl_Position = camera.proj * camera.view * mat4(1.0f) * vec4(inPosition, 1.0f);
}