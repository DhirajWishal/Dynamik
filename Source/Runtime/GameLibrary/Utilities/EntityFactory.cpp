// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "EntityFactory.h"

#include "MeshFactory.h"
#include "Core/Utilities/TextureFactory.h"

namespace EntityFactory
{
	DMKStaticModelEntity CreateStaticEntity(const STRING& asset, ARRAY<STRING> textures, DMKCameraModule* pDefaultCamera)
	{
		_Helpers::_SetDefaultStaticModelCameraModule(pDefaultCamera);

		DMKStaticModelEntity myEntity = {};
		myEntity.setMeshObjects(DMKMeshFactory::loadMeshes(asset, DMKVertexLayout::createBasic()));

		if (textures.size() == myEntity.getMeshObjects()->size())
			for (UI32 index = 0; index < textures.size(); index++)
				myEntity.getMeshObject(index)->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, textures[index]), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);
		else
			for (UI32 index = 0; index < myEntity.getMeshObjects()->size(); index++)
				for (UI32 itr = 0; itr < textures.size(); itr++)
					myEntity.getMeshObject(index)->getMaterial().addTexture(DMKTextureFactory::create(DMKTextureType::TEXTURE_TYPE_2D, textures[itr]), MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT);

		return myEntity;
	}
}
