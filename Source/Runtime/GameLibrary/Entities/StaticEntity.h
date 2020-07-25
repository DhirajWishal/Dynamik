// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_ENTITY_H
#define _DYNAMIK_STATIC_ENTITY_H

#include "../GameEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Static Entity
	 This object can be used to store a static model.

	 By default, a PBR based shader along with default uniform buffers will be set to every mesh. If a mesh
	 already contains a shader, this process will be skipped but updating those meshes must be done externally.
	 Internally assigned shaders and uniform buffers will be managed by this object itself.
	*/
	class DMK_API DMKStaticEntity : public DMKGameEntity {
	public:
		DMKStaticEntity() = default;
		virtual ~DMKStaticEntity() = default;

		/*
		 Load an asset from a file.

		 @param asset: The asset file name.
		 @param pTextures: The textures each mesh contains. If submitted textures are equal to the number of
		   stored meshes, each mesh will be assigned a texture in the given order. If the submitted textures
		   are less than the number of meshes, all the textures will be assigned to different meshes but
		   for the meshes which doesn't contain any textures, the last texture will be added. Default is null.
		 @param vLayout: The vertex layout of all the meshes, Default is basic.
		 @param shaders: The shaders which all the shaders will use. Default is none but will be resolved
		   internally. If submitted externally, users must handle updating its uniforms.
		*/
		void loadAsset(const STRING& asset,
			ARRAY<DMKTexture*> pTextures = {},
			const DMKVertexLayout& vLayout = DMKVertexLayout::createBasic(),
			ARRAY<DMKShaderModule> shaders = {});

		/*
		 On update function.

		 @param timeStep: The time step of the current iteration.
		*/
		virtual void onUpdate(F32 timeStep) override;

		/* Is textures available */
		B1 isTexturesAvailable = false;
	};
}

#endif // !_DYNAMIK_STATIC_ENTITY_H
