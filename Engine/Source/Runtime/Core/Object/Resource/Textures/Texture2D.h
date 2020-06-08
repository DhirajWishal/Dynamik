#pragma once
#ifndef _DYNAMIK_TEXTURE_2D_H
#define _DYNAMIK_TEXTURE_2D_H

/*
 Author:	Dhiraj Wishal
 Date:		07/06/2020
*/
#include "../Texture.h"

namespace Dynamik
{
	/*
	 2D texture for the Dynamik Engine
	*/
	class DMK_API DMKTexture2D : public DMKTexture {
	public:
		DMKTexture2D() : DMKTexture(DMKTextureType::DMK_TEXTURE_TYPE_2D) {}
		~DMKTexture2D() {}

		void load(const STRING& path);
	};
}

#endif // !_DYNAMIK_TEXTURE_2D_H
