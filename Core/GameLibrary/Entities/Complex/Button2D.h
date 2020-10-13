// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_BUTTON_2D_H
#define _DYNAMIK_BUTTON_2D_H

#include "../TriggerEntity2D.h"
#include "../CanvasEntity.h"

/*
 Dynamik Button 2D entity
*/
class DMK_API DMKButton2D :
	public DMKTriggerEntity2D,
	public DMKCanvasEntity {
public:
	DMKButton2D() {}
	virtual ~DMKButton2D() {}

	/*
	 On initialize method.
	*/
	virtual void onInitializeButton2D() {}

	/*
	 On update method.
	*/
	virtual void onUpdateButton2D() {}

	/*
	 On terminate method.
	*/
	virtual void onTerminateButton2D() {}
};

#endif // !_DYNAMIK_BUTTON_2D_H
