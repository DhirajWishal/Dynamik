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
			RENDER_TARGET_ATTACHMENT_TYPE_SWAP_CHAIN,
			RENDER_TARGET_ATTACHMENT_TYPE_COLOR_BUFFER,
			RENDER_TARGET_ATTACHMENT_TYPE_DEPTH_BUFFER,
		};

		/**
		 * Render Target Attachment Specification structure.
		 * This describes how a render target attachment is defined.
		 */
		struct RenderTargetAttachmentSpecification {
			Vector3 extent = Vector3::ZeroAll;	// Extent of the attachment in the frame buffer.
			Format format = Format::FORMAT_UNDEFINED;	// Format of the attachment.
			RenderTargetAttachmentType type = RenderTargetAttachmentType::RENDER_TARGET_ATTACHMENT_TYPE_SWAP_CHAIN;	// Attachment Type.
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

			std::vector<RenderTargetAttachmentType> attachmentTypes;	// Attachment types.
			std::vector<UI64> attachmentIDs;	// Attachment IDs.
			UI64 mRenderTargetID = 0;	// Render target ID.
		};
	}
}