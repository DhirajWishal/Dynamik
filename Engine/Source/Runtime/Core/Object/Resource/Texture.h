#pragma once
#ifndef _DYNAMIK_TEXTURE_H
#define _DYNAMIK_TEXTURE_H

/*
 Author:	Dhiraj Wishal
 Date:		07/06/2020
*/
#include "Macros/Global.h"
#include "Types/DataTypes.h"

namespace Dynamik
{
	/*
	 Texture type
	*/
	enum class DMK_API DMKTextureType {
		DMK_TEXTURE_TYPE_2D,
		DMK_TEXTURE_TYPE_3D,
		DMK_TEXTURE_TYPE_SPRITE,
		DMK_TEXTURE_TYPE_CUBEMAP,
	};

	/*
	 Texture object for the Dynamik Engine
	*/
	class DMK_API DMKTexture {
	public:
		DMKTexture() {}
		DMKTexture(const DMKTextureType& ty) : type(ty) {}
		virtual ~DMKTexture();

		virtual void load(const STRING& path);

		CCPTR image = nullptr;
		UI32 width = 0;
		UI32 height = 0;
		UI32 channels = 0;
		DMKFormat format = DMKFormat::DMK_FORMAT_UNDEFINED;
		DMKTextureType type = DMKTextureType::DMK_TEXTURE_TYPE_2D;
	};
}

#endif // !_DYNAMIK_TEXTURE_MODULE_H
