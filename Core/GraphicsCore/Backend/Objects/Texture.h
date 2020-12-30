// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHCIS_CORE_TEXTURE_H
#define _DYNAMIK_GRAPHCIS_CORE_TEXTURE_H

#include "StaggingBuffer.h"
#include "Core/Types/Utilities.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Texture Extent structure containing the extent information of the texture.
		 */
		struct TextureExtent {
			/**
			 * Default constructor.
			 */
			TextureExtent() = default;

			/**
			 * Contruct the structure using the extent values.
			 *
			 * @param width: The width value.
			 * @param height: The height value.
			 * @param depth: The depth value. Default is 1.
			 */
			TextureExtent(UI32 width, UI32 height, UI32 depth = 1) : width(width), height(height), depth(depth) {}

			/**
			 * Set the width in the extent.
			 *
			 * @param value: The extent value.
			 */
			void SetWidth(UI32 value) { width = value; }

			/**
			 * Get the width in the extent.
			 *
			 * @return Unsigned 32 bit value.
			 */
			UI32 GetWidth() const { return width; }

			/**
			 * Set the height in the extent.
			 *
			 * @param value: The extent value.
			 */
			void SetHeight(UI32 value) { height = value; }

			/**
			 * Get the height in the extent.
			 *
			 * @return Unsigned 32 bit value.
			 */
			UI32 GetHeight() const { return height; }

			/**
			 * Set the depth in the extent.
			 *
			 * @param value: The extent value.
			 */
			void SetDepth(UI32 value) { depth = value; }

			/**
			 * Get the depth in the extent.
			 *
			 * @return Unsigned 32 bit value.
			 */
			UI32 GetDepth() const { return depth; }

			/**
			 * Get the total size of the extent (width * height * depth).
			 *
			 * @return Unsigned 64 bit integer.
			 */
			UI64 GetSize() const { return Cast<UI64>(width * height * depth); }

			UI32 width = 0, height = 0, depth = 1;	// Width, Height and Depth values.
		};

		/**
		 * Base class for all the supported texture objects in DMK.
		 */
		class Texture : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			Texture() {}

			/**
			 * Default destructor.
			 */
			virtual ~Texture() {}

			/**
			 * Set the extent of the texture.
			 *
			 * @param extent: The extent to be set.
			 */
			void SetExtent(const TextureExtent& extent) { this->extent = extent; }

			/**
			 * Get the extent of the texture.
			 *
			 * @return Texture Extent structure containing the data.
			 */
			TextureExtent GetExtent() const { return extent; }

			/**
			 * Set the format of the texture.
			 * This method only changes locally stored format identifier.
			 *
			 * @param format: The format to be set.
			 */
			void SetFormat(Format format) { this->format = format; }

			/**
			 * Switch format from the current format to another.
			 *
			 * @param newFormat: The format to be switched to.
			 */
			virtual void SwitchFormat(Format newFormat) {}

			/**
			 * Get the current format of the texture.
			 *
			 * @return DMK::Format enum.
			 */
			Format GetFormat() const { return format; }

			/**
			 * Copy texture data from a stagging buffer.
			 *
			 * @param pStaggingBuffer: The stagging buffer pointer to copy the data from.
			 */
			virtual void CopyFromBuffer(StaggingBuffer* pStaggingBuffer) {}

		protected:
			TextureExtent extent = {};	// The extent of the texture.
			Format format = Format::FORMAT_UNDEFINED;	// Texture format.
		};
	}
}

#endif // !_DYNAMIK_GRAPHCIS_CORE_TEXTURE_H
