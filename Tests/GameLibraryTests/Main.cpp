// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GameLibrary/GameModule.h"

class Ball : public DMK::GameLibrary::GameEntity {
public:
	Ball() {}
	~Ball() {}

	virtual void OnSpawn(DMK::GameLibrary::GameModule* pParentModule, const DMK::Vector3& location) override final
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

	virtual void OnInitialize(GameModule* pParentModule) override final
	{
		// Spawn an empty entity.
		auto pBall = SpawnEntity<Ball>(DMK::Vector3::ZeroAll);
		pBall->callHello();
		DespawnEntity(pBall);
	}
};

int main()
{
	TestModule tModule;
	tModule.OnInitialize(nullptr);

	return 0;
}