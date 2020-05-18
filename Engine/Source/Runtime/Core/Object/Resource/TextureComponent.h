#pragma once
#ifndef _DYNAMIK_TEXTURE_COMPONENT_H
#define _DYNAMIK_TEXTURE_COMPONENT_H

/*
 Dynamik Texture Component.
 All the texture types are derived from this component.
 Supported texture types:
 * 2D
 * 3D
 * Cubemap
 * Spritesheet

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../Resource.h"
#include "Pointer.h"

namespace Dynamik
{
	/*
	 Dynamik Texture Type enum.
	*/
	enum class DMK_API DMKTextureType {
		DMK_TEXTURE_TYPE_2D,
		DMK_TEXTURE_TYPE_3D,
		DMK_TEXTURE_TYPE_CUBEMAP,
		DMK_TEXTURE_TYPE_SPRITE_SHEET,
	};

	/*
	 Dynamik Texture Component for the Dynamik Engine.
	*/
	class DMK_API DMKTextureComponent : public DMKResource {
	public:
		DMKTextureComponent(DMKTextureType ty) : type(ty) {}
		virtual ~DMKTextureComponent() {}

		POINTER<UCHR> data();

		DMKTextureType type = DMKTextureType::DMK_TEXTURE_TYPE_2D;

	protected:
		POINTER<UCHR> myTextureData;
		UI32 myTextureWidth = 0;
		UI32 myTextureHeight = 0;
		UI32 myTextureChennels = 0;
	};
}

#endif // !_DYNAMIK_TEXTURE_COMPONENT_H
