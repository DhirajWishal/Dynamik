// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Object.
		 * This is the base class for all the graphics objects.
		 */
		class GraphicsObject {
		public:
			GraphicsObject() {}
			virtual ~GraphicsObject() {}

			template<class Type>
			constexpr Type* Derive() const { return dynamic_cast<Type*>(const_cast<Type*>(this)); }
		};
	}
}