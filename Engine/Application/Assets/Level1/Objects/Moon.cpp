#include "Moon.h"

void Moon::initialize()
{
	auto _mesh = DMKMeshComponent::create("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx", { DMKUniformBufferObject::createUniformMVP() });

	addToMeshStore(_mesh);
}
