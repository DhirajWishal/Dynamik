#version 450

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inUV;
layout (location = 3) in vec3 inColor;
layout (location = 4) in vec4 inBoneWeights;
layout (location = 5) in ivec4 inBoneIDs;

#define MAX_BONES 64

/* Model Matrix */
layout (binding = 0) uniform ModelMat 
{
	mat4 model;
} model;

/* Camera Matrix */
layout (binding = 1) uniform CameraMat 
{
	mat4 view;
	mat4 projection;
} camera;

/* Bone Information Matrix */
layout (binding = 2) uniform BoneInfo 
{
	mat4 bones[MAX_BONES];	
} bones;

/* World Information Uniform */
layout (binding = 3) uniform WorldInfo 
{
	vec4 lightPos;
	vec4 viewPos;
} world;

layout (location = 0) out vec3 outNormal;
layout (location = 1) out vec3 outColor;
layout (location = 2) out vec2 outUV;
layout (location = 3) out vec3 outViewVec;
layout (location = 4) out vec3 outLightVec;

out gl_PerVertex 
{
	vec4 gl_Position;   
};

const float matSize = 2.0f;

void main() 
{
	mat4 boneTransform = bones.bones[inBoneIDs[0]] * inBoneWeights[0];
	boneTransform     += bones.bones[inBoneIDs[1]] * inBoneWeights[1];
	boneTransform     += bones.bones[inBoneIDs[2]] * inBoneWeights[2];
	boneTransform     += bones.bones[inBoneIDs[3]] * inBoneWeights[3];	

	gl_Position = camera.view * camera.projection * model.model * boneTransform * vec4(inPos.xyz, matSize);

	vec4 pos = model.model * vec4(inPos, matSize);
	outNormal = mat3(boneTransform) * inNormal;
	outLightVec = world.lightPos.xyz - pos.xyz;
	outViewVec = world.viewPos.xyz - pos.xyz;	
	outColor = inColor;
	outUV = inUV;
}