// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0
#include "GameLibrary/GameComponents/GameModule.h"

class Ball : public DMK::GameLibrary::GameEntity, public DMK::Graphics::GraphicsComponent {
public:
	Ball() {}
	~Ball() {}

	virtual void OnSpawn(const DMK::Vector3& location) override final
	{
		DMK::Logger::LogDebug(TEXT("Ball spawned!"));
	}

	virtual void OnDespawn() override final
	{
		DMK::Logger::LogDebug(TEXT("Ball despawned!"));
	}

	void callHello() { DMK::Logger::LogDebug(TEXT("Hello!!")); }
};

class TestModule : public DMK::GameLibrary::GameModule {
public:
	TestModule() {}
	~TestModule() {}

	virtual void OnModuleTransition(GameModule* pParentModule) override final
	{
		// Spawn an empty entity.
		auto pBall = SpawnEntity<Ball>(DMK::Vector3::ZeroAll);
		pBall->callHello();
		DespawnEntity<Ball>(0);
	}
};

int main()
{
	TestModule tModule;
	tModule.OnModuleTransition(nullptr);

	return 0;
}