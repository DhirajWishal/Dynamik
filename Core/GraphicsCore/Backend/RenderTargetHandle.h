// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Maths/Vector/Vector3.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Render Target Attachmen Type enum.
		 */
		enum class RenderTargetAttachmentType : UI8 {
			SWAP_CHAIN,
			COLOR_BUFFER,
			DEPTH_BUFFER,
		};

		/**
		 * Render Target Attachment Specification structure.
		 * This describes how a render target attachment is defined.
		 */
		struct RenderTargetAttachmentSpecification {
			Format format = Format::UNDEFINED;	// Format of the attachment.
			RenderTargetAttachmentType type = RenderTargetAttachmentType::SWAP_CHAIN;	// Attachment Type.
		};

		/**
		 * Render Target Attachment Handle structure.
		 * This contains information about a single render target attachment handle.
		 */
		struct RenderTargetAttachmentHandle {
			/**
			 * Default constructor.
			 */
			RenderTargetAttachmentHandle() = default;

			/**
			 * Construct the structure using the handle and the type.
			 *
			 * @param mHandle: The attachment handle.
			 * @param mType: The attachment type.
			 */
			RenderTargetAttachmentHandle(UI64 mHandle, RenderTargetAttachmentType mType)
				: mHandle(mHandle), mType(mType) {}

			UI64 mHandle = 0;	// The attachment handle.
			RenderTargetAttachmentType mType = RenderTargetAttachmentType::SWAP_CHAIN;	// Attachment type.
		};

		/**
		 * Render Target Handle object.
		 * This object holds information about a render target in a given Graphics Backend.
		 */
		class RenderTargetHandle {
		public:
			/**
			 * Default constructor.
			 */
			RenderTargetHandle() {}

			/**
			 * Construct the handle by setting the value of the ID.
			 *
			 * @param ID: The ID of the render target handle.
			 */
			RenderTargetHandle(const UI64& ID) : mRenderTargetID(ID) {}

			/**
			 * Default destructor.
			 */
			~RenderTargetHandle() {}

			std::vector<RenderTargetAttachmentHandle> attachmentHandles;	// Attachment handles.

			UI64 mRenderPassID = 0;	// The render pass ID.
			UI64 mFrameBufferID = 0;	// The frane buffer ID.

			UI64 mRenderTargetID = 0;	// Render target ID.
		};
	}
}