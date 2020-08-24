// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATED_MODEL_ENTITY_H
#define _DYNAMIK_ANIMATED_MODEL_ENTITY_H

#include "StaticModelEntity.h"
#include "Animation/Objects/Animation.h"

namespace Dynamik
{
	/*
	 Dynamik Animated Model Entity
	 This object holds information about an animated model.
	*/
	class DMK_API DMKAnimatedModelEntity {
	public:
		DMKAnimatedModelEntity() {}
		virtual ~DMKAnimatedModelEntity() {}

		virtual void onAnimatedEntityUpdate() {}

	public:
		/*
		 Add an instance to the static model.

		 @param name: The name of the instance.
		 @param position: The position of the instance.
		 @param rotation: The rotation of the instance.
		 @param scale: The scale of the instance.
		*/
		void addInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale) {}

		/* The mesh objects. */
		ARRAY<DMKMeshObject> meshObjects;

	public:
		/*
		 Add a shader module.

		 @param sModule: The shader module.
		*/
		void addShaderModule(const DMKShaderModule& sModule);

		/*
		 Set the shader modules.

		 @param sModules: The shader modules to be set.
		*/
		void setShaderModules(ARRAY<DMKShaderModule> sModules);

		/*
		 Get a shader module stored in this object.

		 @param index: The index of the shader module.
		*/
		DMKShaderModule* getShaderModule(I32 index);

		/*
		 Get all the shaders stored in the object.
		*/
		ARRAY<DMKShaderModule> getShaders();

		/* The shader modules. */
		ARRAY<DMKShaderModule> shaders;

	public:
		/*
		 Add a resource request to the object.

		 @param request: The request to be added.
		*/
		void addResourceRequest(const DMKResourceRequest& request);

		/*
		 Set the resource requests of the object.

		 @param requests: The requests to be set.
		*/
		void setResourceRequests(ARRAY<DMKResourceRequest> requests);

		/*
		 Get a resource request from the array.

		 @param index: The index of the request.
		*/
		DMKResourceRequest getResourceRequest(I64 index);

		/*
		 Get all the resource requests stored.
		*/
		ARRAY<DMKResourceRequest> getResourceRequests() const;

		/* Resource Requests */
		ARRAY<DMKResourceRequest> resourceRequests;

		/* Animations of the animated model */
		ARRAY<DMKAnimation> animations;
	};
}

#endif // !_DYNAMIK_ANIMATED_MODEL_ENTITY_H
