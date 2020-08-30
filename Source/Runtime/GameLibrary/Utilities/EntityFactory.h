// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ENTITY_FACTORY_H
#define _DYNAMIK_ENTITY_FACTORY_H

#include "../Entities/StaticModelEntity.h"

/*
 Dynamik Entity Factory 
*/

namespace EntityFactory
{
	/*
	 Create an entity using an asset. 

	 @param asset: The asset to be loaded. 
	 @param textures: The textures to be mapped for the mesh objects. If the texture count is equal to the mesh count, 
	                  the provided texture will be mapped for each mesh (textureIndex = meshIndex). Else, all the available 
					  textures will be mapped to all the mesh objects.
	 @param pDefaultCamera: The default camera module used by the current game world.
	*/
	DMKStaticModelEntity CreateStaticEntity(const STRING& asset, ARRAY<STRING> textures, DMKCameraModule* pDefaultCamera);
}

#endif // !_DYNAMIK_ENTITY_FACTORY_H
