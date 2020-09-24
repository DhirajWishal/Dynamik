// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_IM_GUI_BACKEND_HANDLE_H
#define _DYNAMIK_IM_GUI_BACKEND_HANDLE_H

#include "Core/Math/Vector/Vector2F.h"
#include <imgui.h>

/* Global mutex to lock render data from being updated while rendering. */
static std::mutex __globalLock;

/*
 Dynamik Im Gui Backend Handle
 This object is the base class for all the Im Gui backend implementations and is user accessible.
*/
class DMK_API DMKImGuiBackendHandle {
public:
	DMKImGuiBackendHandle() {}
	virtual ~DMKImGuiBackendHandle() {}

	virtual void initialize() = 0;
	virtual void drawFrame() = 0;
	virtual void terminate() = 0;

	virtual void setDrawData(ImDrawData* pDrawData) { this->pDrawData = pDrawData; };

	ImDrawData* pDrawData = nullptr;

	struct DMK_API ImGuiUniform {
		Vector2F scale = Vector2F(0.0f);
		Vector2F transform = Vector2F(0.0f);
	} uniformData;
};

#endif // !_DYNAMIK_IM_GUI_BACKEND_HANDLE_H
