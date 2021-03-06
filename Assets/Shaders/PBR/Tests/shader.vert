#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} Ubo;

layout(binding = 1) uniform CameraUniform {
    mat4 view;
    mat4 proj;
} Camera;

layout (push_constant) uniform constant
{
    vec4 surface;
    vec4 subSurface;
    float roughness;
    float metallic;
} pushBlock;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

const float mapSize = 1.0f;

void main() {
    gl_Position = Camera.proj * Camera.view * Ubo.model * vec4(inPosition, mapSize);

    fragColor = vec3(pushBlock.surface);
    fragTexCoord = inTexCoord;
}

