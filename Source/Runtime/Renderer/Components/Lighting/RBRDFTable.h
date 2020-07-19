// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_BRDF_TABLE_H
#define _DYNAMIK_RENDERER_BRDF_TABLE_H

#include "../Primitives/RTexture.h"
#include "../RRenderTarget.h"

namespace Dynamik
{
	/*
	 Renderer BRDF Table
	*/
	class DMK_API RBRDFTable {
	public:
		RBRDFTable() {}
		virtual ~RBRDFTable() {}

		virtual void initialize(RCoreObject* pCoreObject, DMKExtent2D dimentions, DMKFormat format = DMKFormat::DMK_FORMAT_RG_16_SF32) = 0;
		virtual void terminate(RCoreObject* pCoreObject) = 0;

		RRenderTarget renderTarget = {};
		DMKExtent2D dimentions = DMKExtent2D(0.0f);
		RTexture* pTexture = nullptr;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
	};
}

#endif // !_DYNAMIK_RENDERER_BRDF_TABLE_H
