// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATERIAL_H
#define _DYNAMIK_MATERIAL_H

#include "Core/Types/ComplexTypes.h"
#include "Texture.h"

namespace Dynamik
{
	/*
	 Material Texture Type
	 Defines a texture usage in the material system.
	*/
	enum class DMK_API MaterialTextureType {
		MATERIAL_TEXTURE_TYPE_DEFAULT,
		MATERIAL_TEXTURE_TYPE_DIFFUSE,
		MATERIAL_TEXTURE_TYPE_EMISSIVE,
		MATERIAL_TEXTURE_TYPE_NORMAL,
		MATERIAL_TEXTURE_TYPE_OPACITY,
		MATERIAL_TEXTURE_TYPE_SPECULAR,
		MATERIAL_TEXTURE_TYPE_GLOSS,
	};

	/*
	 Dynamik Material Object
	 This structure contains all the necessary information required to define a material.
	*/
	class DMK_API DMKMaterial {
		/* Material Texture Container Structure */
		struct DMK_API MTextureContainer {
			MaterialTextureType type = MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT;
			DMKTexture* pTexture = nullptr;
		};

	public:
		DMKMaterial() = default;
		DMKMaterial(STRING name, DMKColorComponent surface, DMKColorComponent subSurface, F32 roughness, F32 metalic)
		: name(name), surfaceColor(surface), subSurfaceColor(subSurface), roughness(roughness), metallicness(metalic) {}
		~DMKMaterial() = default;

		/*
		 Add a texture to the material.

		 @param pTexture: Dynamik texture.
		 @param textureType: Material texture type.
		*/
		void addTexture(DMKTexture* pTexture, MaterialTextureType textureType);

		/* Material Name */
		STRING name = TEXT("");

		/* Surface Color */
		DMKColorComponent surfaceColor;

		/* Sub Surface Color */
		DMKColorComponent subSurfaceColor;

		/* Roughness */
		F32 roughness = 0.0f;

		/* Metallicness */
		F32 metallicness = 0.0f;

		/* Textures */
		ARRAY<MTextureContainer> textureContainers;

	public:		/* Utility Functions */
		static DMKMaterial createMetalGold();
		static DMKMaterial createMetalCopper();
		static DMKMaterial createMetalChromium();
		static DMKMaterial createMetalNickel();
		static DMKMaterial createMetalTitanium();
		static DMKMaterial createMetalCobalt();
		static DMKMaterial createMetalPlatinum();

		static DMKMaterial createMetalWhite();
		static DMKMaterial createMetalRed();
		static DMKMaterial createMetalBlue();
		static DMKMaterial createMetalBlack();

	public:		/* Push Block Utilities */
		/*
		 This block is submitted to the shaders via constants.
		*/
		struct DMK_API MaterialPushBlock {
			MaterialPushBlock() = default;
			MaterialPushBlock(DMKColorComponent surface, DMKColorComponent subSurface, F32 roughness, F32 metalic)
				: surfaceColor(surface), subSurfaceColor(subSurface), roughness(roughness), metallicness(metalic) {}
			~MaterialPushBlock() = default;

			DMKColorComponent surfaceColor;
			DMKColorComponent subSurfaceColor;
			F32 roughness = 0;
			F32 metallicness = 0;
		};

		/*
		 Generate a push block using the current material.
		*/
		MaterialPushBlock generatePushBlock();
	};
}

#endif // !_DYNAMIK_MATERIAL_H
