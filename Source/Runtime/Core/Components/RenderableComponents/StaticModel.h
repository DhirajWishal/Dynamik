// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_MODEL_H
#define _DYNAMIK_STATIC_MODEL_H

#include "StaticMeshComponent.h"
#include "Core/Math/Quaternion.h"

namespace Dynamik
{
	class DMK_API DMKStaticModel;

	/*
	*  Static model instance.
	*/
	struct DMK_API DMKStaticModelInstance {
		STRING name = TEXT("");
		Quaternion rotation = Quaternion(0.0f);
		Vector3F location = Vector3F(0.0f);
		Vector3F scale = Vector3F(0.0f);
		DMKStaticModel* pParent = nullptr;
	};

	/*
	 Dynamik Static Model
	 This object contains multiple static mesh components.
	*/
	class DMKStaticModel {
	public:
		DMKStaticModel() {}
		~DMKStaticModel() {}

		/*
		 Add a static mesh component.

		 @param staticMesh: The new static mesh.
		*/
		void addMesh(const DMKStaticMeshComponent& staticMesh);

		/*
		 Get a static mesh located at a index.

		 @param index: The index of the mesh.
		*/
		DMKStaticMeshComponent& getMesh(I64 index = 0);

		/*
		 Get the number of stored meshes.
		*/
		UI64 getMeshCount() const;

		/*
		 Set position to the model.

		 @param position: The position.
		 @warn: This must be set after initializing/ loading all the meshes.
		*/
		void setPosition(const Vector3F& position);

		/*
		 Set scale to the model.

		 @param scale: The scale.
		 @warn: This must be set after initializing/ loading all the meshes.
		*/
		void setScale(const Vector3F& scale);

		/*
		 Set the rotation to the mode.

		 @param rotation: The rotation.
		 @warn: This must be set after initializing/ loading all the meshes.
		*/
		void setRotation(const Quaternion& rotation);

		/*
		 Add an instance to the static model.

		 @param name: The name of the instance.
		 @param location: The location of the new instance.
		 @param rotation: Rotation of the new instance.
		 @param scale: Scale of the new instance.
		*/
		void addInstance(const STRING& name, const Vector3F& location, const Quaternion& roation, const Vector3F& scale);

	public:		/* Mesh Store */
		ARRAY<DMKStaticMeshComponent> staticMeshes;

		ARRAY<DMKStaticModelInstance*> pInstances;
	};
}

#endif // !_DYNAMIK_STATIC_MODEL_H
