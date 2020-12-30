// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_RENDER_TARGET_H
#define _DYNAMIK_GRAPHICS_RENDER_TARGET_H

#include "GObject.h"
#include "Core/Macros/Global.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Render Target Attachment Flags.
		 * These flags define what attachments the render target should have.
		 */
		enum class RenderTargetAttachmentFlags {
			RENDER_TARGET_ATTACHMENT_FLAG_SWAP_CHAIN = BIT_SHIFT(0),
			RENDER_TARGET_ATTACHMENT_FLAG_DEPTH_BUFFER = BIT_SHIFT(1),
			RENDER_TARGET_ATTACHMENT_FLAG_COLOR_BUFFER = BIT_SHIFT(2),
		};

		/**
		 * Render Target for Dynamik Graphics module.
		 */
		class RenderTarget : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			RenderTarget() {}

			/**
			 * Default destructor.
			 */
			virtual ~RenderTarget() {}

			/**
			 * Initialize the render target.
			 */
			virtual void Initialize() {}

			/**
			 * Terminat the render target.
			 */
			virtual void Terminate() {}
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_RENDER_TARGET_H
