// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_BUFFER_H
#define _DYNAMIK_GRAPHICS_CORE_BUFFER_H

#include "GraphicsCore/Backend/Common/GObject.h"
#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Buffer object for the Dynamik Engine.
		 * This object is the base class for all the graphics and compute buffers.
		 */
		class Buffer : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			Buffer() {}

			/**
			 * Default destructor.
			 */
			virtual ~Buffer() {}

			/**
			 * Set the size of the buffer.
			 *
			 * @param size: The size of the buffer in bytes.
			 */
			void SetSize(UI64 size) { this->size = size; }

			/**
			 * Get the size of the buffer.
			 *
			 * @return: Unsigned 64 bit integer.
			 */
			UI64 GetSize() const { return size; }

		protected:
			UI64 size = 0;	// Size of the buffer in bytes.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_BUFFER_H
