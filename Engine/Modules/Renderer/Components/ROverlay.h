// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_OVERLAY_H
#define _DYNAMIK_RENDERER_OVERLAY_H

#include "Context/RRenderPass.h"
#include "../ThirdParty/stb_font_consolas_24_latin1.inl"

/*
 Dynamik Text Align
*/
enum class DMK_API DMKTextAlign {
	DMK_TEXT_ALIGN_LEFT,
	DMK_TEXT_ALIGN_RIGHT,
	DMK_TEXT_ALIGN_CENTER,
};

/*
 Renderer Overlay
 This object can be used to render full screen, transparent images to display debug information, HUDs and other
 information or game data.
*/
class DMK_API ROverlay {
public:
	ROverlay() = default;
	virtual ~ROverlay() = default;

	virtual void initialize(RCoreObject* pCoreObject) = 0;
	virtual void terminate(RCoreObject* pCoreObject) = 0;

	virtual void initializeResources(RCoreObject* pCoreObject) = 0;
	virtual void initializeContext(RCoreObject* pCoreObject) = 0;

	virtual void beginUpdate(RCoreObject* pCoreObject) = 0;
	virtual void addText(const STRING& text, DMKExtent2D location, DMKTextAlign alignment) = 0;
	virtual void endUpdate(RCoreObject* pCoreObject) = 0;
};

#endif // !_DYNAMIK_RENDERER_IMAGE_OVERLAY_H
