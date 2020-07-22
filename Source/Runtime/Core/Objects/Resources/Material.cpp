// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Material.h"

#include "Core/Utilities/TextureFactory.h"

namespace Dynamik
{
	void DMKMaterial::addTexture(DMKTexture* pTexture, MaterialTextureType textureType)
	{
		MTextureContainer container;
		container.pTexture = pTexture;
		container.type = textureType;
		textureContainers.pushBack(container);
	}
	
	DMKMaterial DMKMaterial::createMetalGold()
	{
		return DMKMaterial("Gold", DMKColorComponent(1.0f, 0.765557f, 0.336057f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalCopper()
	{
		return DMKMaterial("Copper", DMKColorComponent(0.955008f, 0.637427f, 0.538163f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalChromium()
	{
		return DMKMaterial("Chromium", DMKColorComponent(0.549585f, 0.556114f, 0.554256f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalNickel()
	{
		return DMKMaterial("Nickel", DMKColorComponent(0.659777f, 0.608679f, 0.525649f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalTitanium()
	{
		return DMKMaterial("Titanium", DMKColorComponent(0.541931f, 0.496791f, 0.449419f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalCobalt()
	{
		return DMKMaterial("Cobalt", DMKColorComponent(0.662124f, 0.654864f, 0.633732f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalPlatinum()
	{
		return DMKMaterial("Platinum", DMKColorComponent(0.672411f, 0.637331f, 0.585456f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalWhite()
	{
		return DMKMaterial("White", DMKColorComponent(1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalRed()
	{
		return DMKMaterial("Red", DMKColorComponent(1.0f, 0.0f, 0.0f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalBlue()
	{
		return DMKMaterial("Blue", DMKColorComponent(0.0f, 0.0f, 1.0f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createMetalBlack()
	{
		return DMKMaterial("Black", DMKColorComponent(0.0f, 0.0f, 0.0f, 1.0f), DMKColorComponent(), 0.1f, 1.0f);
	}

	DMKMaterial DMKMaterial::createDefaultTexture(const STRING& path, DMKTextureType type)
	{
		DMKMaterial newMaterial;
		newMaterial.name = TEXT("DefaultTexture");
		newMaterial.addTexture(DMKTextureFactory::create(type, path), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		return newMaterial;
	}
	
	DMKMaterial::MaterialPushBlock DMKMaterial::generatePushBlock()
	{
		return MaterialPushBlock(surfaceColor, subSurfaceColor, roughness, metallicness, specular);
	}
}
