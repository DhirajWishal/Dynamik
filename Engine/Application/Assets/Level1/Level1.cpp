#include "Level1.h"
#include "Player.h"

void Level1::onLoad()
{
	playerObject = (POINTER<DMKPlayerObject>)StaticAllocator<Player>::allocate();

	myMoon.setupCamera(playerObject->getCameraModule());

	myEntities.pushBack(&myMoon);
}
