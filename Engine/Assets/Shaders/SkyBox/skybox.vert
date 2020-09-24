#version 450

layout (location = 0) in vec3 aPos;

layout (location = 0) out vec3 TexCoords;

layout (binding = 0) uniform Cam
{
	mat4 projection;
    mat4 view;
	mat4 model;
} Camera;

void main()
{
    TexCoords = aPos;
    gl_Position = Camera.projection * Camera.model * Camera.view * vec4(aPos.xyz, 0.01f);
}  