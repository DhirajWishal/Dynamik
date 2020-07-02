// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PLAYER_EVENT_CONTROLLER_H
#define _DYNAMIK_PLAYER_EVENT_CONTROLLER_H

/*
 Author:	Dhiraj Wishal
 Date:		02/07/2020
*/
#include "GameLibrary/PlayerObject.h"

namespace Dynamik
{
	/*
	 Dynamik Player Event Controller
	 This object handles all the events defined by the player object.
	*/
	class DMK_API DMKPlayerEventController {
	public:
		DMKPlayerEventController() {}
		~DMKPlayerEventController() {}

		void bindInstruction(const DMKEvent& eEvent, DMKPlayerObject* pPlayerObject, const DMKEventType& eEventType);
	};
}

#endif // !_DYNAMIK_PLAYER_EVENT_CONTROLLER_H
