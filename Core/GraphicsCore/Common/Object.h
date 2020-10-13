// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_OBJECT_H
#define _DYNAMIK_GRAPHICS_CORE_OBJECT_H

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * The base class for all of the graphics objects.
		 */
		class DMK_API GObject {
		public:
			/**
			 * Default constructor.
			 */
			GObject() {}

			/**
			 * Default destructor.
			 */
			virtual ~GObject() {}

			/**
			 * Inherit this object by casting it to a child class.
			 *
			 * @tparam Type: The base type.
			 */
			template<class Type>
			Type* Inherit()
			{
				return dynamic_cast<Type*>(this);
			}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_OBJECT_H
