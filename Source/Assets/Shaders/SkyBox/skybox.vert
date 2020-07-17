#version 450

layout (location = 0) in vec3 aPos;

layout (location = 0) out vec3 TexCoords;

layout (binding = 0) uniform UBO 
{
	mat4 model;
} Model;

layout (binding = 1) uniform Cam
{
    mat4 view;
	mat4 projection;
} Camera;

void main()
{
    TexCoords = aPos;
    gl_Position = Camera.projection * Model.model * Camera.view * vec4(aPos.xyz, 0.01f);
}  