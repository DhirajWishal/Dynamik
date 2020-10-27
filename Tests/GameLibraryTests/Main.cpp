// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0
#include "GameLibrary/GameComponents/PlayerCharacter.h"

class Ball : public DMK::GameLibrary::PlayerCharacter {
public:
	Ball() {}
	~Ball() {}

	virtual void OnSpawn(const DMK::Vector3& location) override final
	{
		for (int i = 0; i < 10000; i++)
			AddProperty<int>(i);

		for (int i = 0; i < 10000; i++)
			auto value = GetProperty<int>(i);
	}

	virtual void OnDespawn() override final
	{

	}
};

int main()
{
	Ball ball;
	ball.OnSpawn(DMK::Vector3::ZeroAll);

	return 0;
}