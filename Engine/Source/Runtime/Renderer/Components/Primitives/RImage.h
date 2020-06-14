// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IMAGE_H
#define _DYNAMIK_RENDERER_IMAGE_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "RImageView.h"
#include "../PrimitiveTypeDefs.h"
#include "Core/Math/MathTypes.h"

namespace Dynamik
{
	/*
	 Renderer Image Create Info
	*/
	struct DMK_API RImageCreateInfo {
		VEC3F vDimentions = VEC3F(0.0f, 0.0f, 1.0f);
	};

	/*
	 Renderer Image
	*/
	class DMK_API RImage {
	public:
		RImage() {}
		virtual ~RImage() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, RImageCreateInfo createInfo) = 0;
		virtual void createImageView(POINTER<RCoreObject> pCoreObject) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;

		virtual POINTER<RImageView> getImageView() { return pImageView; }

	protected:
		POINTER<RImageView> pImageView;
	};
}

#endif // !_DYNAMIK_RENDERER_IMAGE_H
