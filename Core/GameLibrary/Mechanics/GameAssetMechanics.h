// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GAME_ASSET_MECHANICS_H
#define _DYNAMIK_GAME_ASSET_MECHANICS_H

#include "../GameMechanics.h"

/*
 Dynamik Game Asset Mechanics
 This class defines the mechanics of a game asset.
*/
class DMK_API DMKGameAssetMechanics : public DMKGameMechanics {
public:
	DMKGameAssetMechanics() {}
	virtual ~DMKGameAssetMechanics() {}
};

#endif // !_DYNAMIK_GAME_ASSET_MECHANICS_H