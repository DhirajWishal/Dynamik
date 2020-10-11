#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H
#define _DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H

#include "GObject.h"
#include <vector>

namespace DMK
{
	/**
	 * Graphics Render Target Attachment Type enum.
	 */
	enum class DMK_API GRenderTargetAttachmentType {
		RENDER_RATGET_ATTACHMENT_TYPE_SWAP_CHAIN,
		RENDER_RATGET_ATTACHMENT_TYPE_COLOR_BUFFER,
		RENDER_RATGET_ATTACHMENT_TYPE_DEPTH_BUFFER,
	};

	/**
	 * Graphics Render Target Attachment object.
	 * The render target is made up of multiple attachments and these attachments are described by this base class.
	 */
	class DMK_API GRenderTargetAttachment : public GObject {
	public:
		/**
		 * Deafult constructor.
		 */
		GRenderTargetAttachment(GRenderTargetAttachmentType type) : type(type) {}

		/**
		 * Deafult destructor.
		 */
		virtual ~GRenderTargetAttachment() {}

		/* Data */
	protected:
		GRenderTargetAttachmentType type = GRenderTargetAttachmentType::RENDER_RATGET_ATTACHMENT_TYPE_SWAP_CHAIN;
	};

	/**
	 * Graphics Swap Chain Attachment object.
	 * This contains the information about swap chain attachment of the render target.
	 */
	class DMK_API GSwapChainAttachment : public GRenderTargetAttachment {
	public:
		/**
		 * Deafult constructor.
		 */
		GSwapChainAttachment() : GRenderTargetAttachment(GRenderTargetAttachmentType::RENDER_RATGET_ATTACHMENT_TYPE_SWAP_CHAIN) {}

		/**
		 * Deafult destructor.
		 */
		~GSwapChainAttachment() {}
	};

	/**
	 * Graphics Render Target object.
	 * All the objects which are to be rendered are rendered to a specific render target.
	 */
	class DMK_API GRenderTarget : public GObject {
	public:
		/**
		 * Deafult constructor.
		 */
		GRenderTarget() {}

		/**
		 * Deafult destructor.
		 */
		virtual ~GRenderTarget() {}

		/* Data */
	protected:
		std::vector<GRenderTargetAttachment*> pAttachments;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_RENDER_TARGET_H
