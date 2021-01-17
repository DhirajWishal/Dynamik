// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GObject.h"
#include "Core/Maths/Vector/Vector3.h"

#define DMK_IMAGE_COMPONENT_RED			BIT_SHIFT(0)
#define DMK_IMAGE_COMPONENT_GREEN		BIT_SHIFT(0)
#define DMK_IMAGE_COMPONENT_BLUE		BIT_SHIFT(0)
#define DMK_IMAGE_COMPONENT_ALPHA		BIT_SHIFT(0)
#define DMK_IMAGE_COMPONENT_DEPTH		BIT_SHIFT(0)

#define DMK_IMAGE_DATA_UNORMAL			BIT_SHIFT(0)
#define DMK_IMAGE_DATA_UINT				BIT_SHIFT(0)
#define DMK_IMAGE_DATA_SINT				BIT_SHIFT(0)
#define DMK_IMAGE_DATA_SFLOAT			BIT_SHIFT(0)
#define DMK_IMAGE_DATA_PACK8			BIT_SHIFT(0)
#define DMK_IMAGE_DATA_PACK16			BIT_SHIFT(0)
#define DMK_IMAGE_DATA_USCALED			BIT_SHIFT(0)
#define DMK_IMAGE_DATA_SSCALED			BIT_SHIFT(0)

namespace DMK
{
	namespace GraphicsCore
	{
		class Device;

		/**
		 * Image Type enum.
		 */
		enum class ImageType : UI8 {
			UNDEFINED,

			STORAGE_2D,
			STORAGE_3D,

			RENDER_2D,
			RENDER_3D,

			CUBE_MAP,
		};

		struct ImageExtent {
			UI32 mWidth = 0;
			UI32 mHeight = 0;
			UI32 mDepth = 0;
		};

		/**
		 * Graphics Image object.
		 */
		class Image : public GObject {
		public:
			Image() {}
			virtual ~Image() {}

			/**
			 * Initialize the image.
			 *
			 * @param pDevice: The device pointer.
			 * @param type: The type of the image.
			 * @param extent: The image extent.
			 * @param mipLevels: The number of mip levels to use.
			 * @param pAsset: The asset path. Default is nullptr.
			 */
			virtual void Initialize(Device* pDevice, ImageType type, Vector3 extent, UI8 mipLevels, const wchar* pAsset = nullptr) {}

			/**
			 * Terminate the image.
			 *
			 * @param pDevice: The device pointer.
			 */
			virtual void Terminate(Device* pDevice) {}

		public:
			Vector3 GetExtent() const { return mExtent; }
			UI64 GetSize() const { return static_cast<UI64>(static_cast<double>(mExtent.x) * static_cast<double>(mExtent.y) * static_cast<double>(mExtent.z)); }
			Format GetFormat() const { return mFormat; }
			ImageType GetType() const { return mType; }

		protected:
			Vector3 mExtent = Vector3::ZeroAll;
			UI8 mMipLevels = 0;

			Format mFormat = Format::UNDEFINED;
			ImageType mType = ImageType::UNDEFINED;

		public:
			/**
			 * Load image data from an asset file.
			 * 
			 * @param pAsset: The asset path.
			 */
			unsigned char* LoadImageData(const char* pAsset);
		};
	}
}