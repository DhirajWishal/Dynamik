// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class GObject {
		public:
			GObject() {}
			virtual ~GObject() {}

			template<class Type>
			constexpr Type* Derive() { return dynamic_cast<Type*>(this); }
		};
	}
}