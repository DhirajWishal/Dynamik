// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_IMAGE_VIEW_H
#define _DYNAMIK_RENDERER_IMAGE_VIEW_H

/*
 Author:	Dhiraj Wishal
 Date:		14/06/2020
*/
#include "../RCoreObject.h"

namespace Dynamik
{
	class DMK_API RImage;

	/*
	 Renderer Image View
	*/
	class DMK_API RImageView {
	public:
		RImageView() {}
		virtual ~RImageView() {}

		virtual void initialize(POINTER<RCoreObject> pCoreObject, POINTER<RImage> pImage) = 0;
		virtual void terminate(POINTER<RCoreObject> pCoreObject) = 0;
	};
}

#endif // !_DYNAMIK_RENDERER_IMAGE_VIEW_H
