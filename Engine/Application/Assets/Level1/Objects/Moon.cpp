#include "Moon.h"

void Moon::initialize()
{
	auto _mesh = createMeshComponent("E:/Projects/Dynamik Engine/Game Repository/assets/assets/moon/Moon 2K.fbx", { createUniformMVP() });
}
