#pragma once
#ifndef _DYNAMIK_GAME_PACKAGE_MANAGER_H
#define _DYNAMIK_GAME_PACKAGE_MANAGER_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "Types/Array.h"
#include "GameLibrary/GamePackage.h"

namespace Dynamik
{
	/*
	 Dynamik Game Packet Manager
	 Game data are submitted to the engine via a game packages. This manager manages all the resources in 
	 such packets.
	*/
	class DMK_API DMKGamePackageManager {
	public:
		DMKGamePackageManager() {}
		~DMKGamePackageManager() {}

	private:
		DMKGamePackage myCurrentPackage;
	};
}

#endif // _DYNAMIK_GAME_PACKAGE_MANAGER_H
