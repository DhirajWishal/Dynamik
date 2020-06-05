#pragma once
#ifndef _DYNAMIK_LEVEL_1_H
#define _DYNAMIK_LEVEL_1_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "GameLibrary/LevelComponent.h"
using namespace Dynamik;

class Level1 : public DMKLevelComponent {
public:
	Level1() {}
	~Level1() {}

	void onLoad() override;
};

#endif // !_DYNAMIK_LEVEL_1_H
