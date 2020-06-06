#include "PlayerMoon.h"

void PlayerMoon::initialize()
{
	myComponentManager.addComponent<DMKMeshComponent>();
	auto meshComponent = myComponentManager.getComponent<DMKMeshComponent>(0);
	meshComponent = DMKMeshComponent::create("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx", { DMKUniformBufferObject::createUniformMVP() })[0];
}
