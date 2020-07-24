// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_PRE_FILTERED_CUBE_H
#define _DYNAMIK_RENDERER_PRE_FILTERED_CUBE_H

#include "../RRenderTarget.h"

namespace Dynamik
{
	class DMK_API REnvironmentMap;

	/*
	 Renderer PreFiltered Cube
	*/
	class DMK_API RPreFilteredCube {
	public:
		RPreFilteredCube() = default;
		virtual ~RPreFilteredCube() = default;

		virtual void initialize(RCoreObject* pCoreObject, REnvironmentMap* pEnvironmentMap, DMKExtent2D dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RGBA_16_SF32) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		RRenderTarget renderTarget = {};
		DMKExtent2D dimentions = DMKExtent2D(0.0f);
		REnvironmentMap* pParent = nullptr;
		RTexture* pTexture = nullptr;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
	};
}

#endif // !_DYNAMIK_RENDERER_PRE_FILTERED_CUBE_H
