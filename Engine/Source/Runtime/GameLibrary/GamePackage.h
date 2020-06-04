#pragma once
#ifndef _DYNAMIK_GAME_PACKAGE_H
#define _DYNAMIK_GAME_PACKAGE_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "LevelComponent.h"

namespace Dynamik
{
	/*
	 Dynamik Game Package
	 This defines the game instance which the client has created. This also provides the engine with all
	 the necessary data to execute a game.
	*/
	class DMK_API DMKGamePackage {
	public:
		DMKGamePackage() {}
		~DMKGamePackage() {}

		/*
		 All the levels in a game.
		*/
		ARRAY<POINTER<DMKLevelComponent>> levels;

		/*
		 Basic game data
		*/
		STRING gameName = DMK_TEXT("Dynamik Engine");
		UI64 gameVersion = 1;
		STRING gameDataPath = DMK_TEXT("");
		STRING gameAssetBasePath = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_GAME_PACKAGE_H
