#include "PlayerMoon.h"

void PlayerMoon::initialize()
{
	auto meshComponent = DMKMeshComponent::create(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx"), { DMKUniformBufferObject::createUniformMVP() })[0];

	DMKShaderModule _shaderModuleV(DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	_shaderModuleV.loadCode(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/vert.spv"));
	meshComponent.renderSpecifications.shaderModules.pushBack(_shaderModuleV);

	DMKShaderModule _shaderModuleF(DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
	_shaderModuleF.loadCode(DMK_TEXT("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/frag.spv"));
	meshComponent.renderSpecifications.shaderModules.pushBack(_shaderModuleF);

	componentManager.addComponent<DMKMeshComponent>(meshComponent);
}
