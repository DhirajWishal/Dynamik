// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "SceneObject.h"

namespace Dynamik
{
	namespace Experimental
	{
		UI64 DMKSceneObject::addInstance(const Vector3F& location, const Quaternion& rotation, const Vector3F& scale)
		{
			instances.pushBack(DMKSceneObjectInstance(location, rotation, scale, this));
			return instances.size() - 1;
		}

		DMKSceneObjectInstance* DMKSceneObject::getInstance(UI64 index)
		{
			return Cast<DMKSceneObjectInstance*>(instances.location(index));
		}
	}
}
