// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H
#define _DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H

#include "Object.h"
#include <vector>

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Render Target Attachment object.
		 * The render target is made up of multiple attachments and these attachments are described by this base class.
		 */
		class DMK_API RenderTargetAttachment : public GObject {
		public:
			/**
			 * Deafult constructor.
			 */
			RenderTargetAttachment() {}

			/**
			 * Deafult destructor.
			 */
			virtual ~RenderTargetAttachment() {}
		};

		/**
		 * Graphics Swap Chain Attachment object.
		 * This contains the information about swap chain attachment of the render target.
		 */
		class DMK_API SwapChainAttachment : public RenderTargetAttachment {
		public:
			/**
			 * Deafult constructor.
			 */
			SwapChainAttachment() {}

			/**
			 * Deafult destructor.
			 */
			~SwapChainAttachment() {}
		};

		/**
		 * Graphics Render Target object.
		 * All the objects which are to be rendered are rendered to a specific render target.
		 */
		class DMK_API RenderTarget : public GObject {
		public:
			/**
			 * Deafult constructor.
			 */
			RenderTarget() {}

			/**
			 * Deafult destructor.
			 */
			virtual ~RenderTarget() {}

			/* Data */
		protected:
			std::vector<RenderTargetAttachment*> pAttachments;
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H
