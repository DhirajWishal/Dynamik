#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;

layout (binding = 0) uniform UBO 
{
	mat4 projection;
	mat4 model;
	mat4 view;
	vec3 camPos;
} ubo;

layout (location = 0) out vec3 outWorldPos;
layout (location = 1) out vec3 outNormal;
layout (location = 2) out vec2 outUV;
layout (location = 3) out mat4 outProjection;
layout (location = 4) out mat4 outModel;
layout (location = 5) out mat4 outView;

out gl_PerVertex 
{
	vec4 gl_Position;
};

void main() 
{
	outNormal = mat3(ubo.model) * inNormal;
	outUV = inUV;
	outUV.t = 1.0 - inUV.t;
	gl_Position =  ubo.projection * ubo.view * vec4(inPos, 1.0);

	outProjection = ubo.projection;
	outModel = ubo.model;
	outView = ubo.view;
}