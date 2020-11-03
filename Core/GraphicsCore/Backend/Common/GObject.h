// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_OBJECT_H
#define _DYNAMIK_GRAPHICS_CORE_OBJECT_H

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Object for the Dynamik Engine.
		 * This object is the base object for all the graphics objects used in the engine.
		 */
		class GObject {
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
			 * Inherit the class to a base or super type.
			 *
			 * @tparam Type: The base or super type to be casted.
			 * @return: Type pointer.
			 */
			template<class Type>
			Type* Inherit() { return dynamic_cast<Type*>(this); }
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_OBJECT_H
