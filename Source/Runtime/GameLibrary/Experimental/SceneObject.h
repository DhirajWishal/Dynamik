// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EXPERIMENTAL_SCENE_OBJECT_H
#define _DYNAMIK_EXPERIMENTAL_SCENE_OBJECT_H

#include "Core/Macros/Global.h"
#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector/Vector3F.h"

namespace Dynamik
{
	namespace Experimental
	{
		class DMK_API DMKSceneObject;

		/*
		 Dynamik Scene Object Instance
		 This object contains all the necessary information required by a scene object's instance.
		*/
		struct DMK_API DMKSceneObjectInstance {
			DMKSceneObjectInstance() = default;
			DMKSceneObjectInstance(const Vector3F& location, const Quaternion& rotation, const Vector3F& scale, DMKSceneObject* pParent) :
				location(location), rotation(rotation), scale(scale), pParentObject(pParent) {}

			Quaternion rotation = Quaternion(0.0f);
			Vector3F location = Vector3F(0.0f);
			Vector3F scale = Vector3F(0.0f);

			DMKSceneObject* pParentObject = nullptr;
		};

		/*
		 Dynamik Scene Object
		 This object contains all the raw data about a single scene object. They does not contain any functionalities
		 by default but using components, behaviors can be added.
		*/
		class DMK_API DMKSceneObject {
		public:
			DMKSceneObject() = default;
			virtual ~DMKSceneObject() = default;

			/*
			 Add an instance to the scene object.
			 This method adds an instance to the object. These instances are stored internally and an index to it will
			 be returned. This index is the index of it in the instance array.

			 @param location: The location of the new instance.
			 @param rotation: The rotation of the new instance. Default is 0.
			 @param scale: The scale of the new instance. Default is { 1.0f, 1.0f, 1.0f };
			*/
			virtual UI64 addInstance(const Vector3F& location, const Quaternion& rotation = Quaternion(0.0f), const Vector3F& scale = Vector3F(1.0f, 1.0f, 1.0f));
			
			/*
			 Get an instance from the instance array. 

			 @param instanceID: The index of the instance.
			*/
			virtual DMKSceneObjectInstance* getInstance(UI64 index);

			/* The object instances */
			ARRAY<DMKSceneObjectInstance> instances;
		};
	}
}

#endif // !_DYNAMIK_EXPERIMENTAL_SCENE_OBJECT_H
