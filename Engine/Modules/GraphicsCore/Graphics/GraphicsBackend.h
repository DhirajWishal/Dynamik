#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H
#define _DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H

#include "GraphicsCore/Common/GBuffer.h"

namespace DMK
{
	/**
	 * Graphics Backend API for the Dynamik Engine.
	 * This enum contains all the available backend the engine contains.
	 */
	enum class DMK_API GraphicsBackendAPI {
		GRAPHICS_BACKEND_API_VULKAN,
		GRAPHICS_BACKEND_API_DIRECTX_12,
		GRAPHICS_BACKEND_API_WEB_GPU,
	};

	/**
	 * Graphics Backend for the Dynamik Engine.
	 * This object is the main API which is responsible for creating and destroying graphical objects.
	 */
	class DMK_API GraphicsBackend : public GObject {
	public:
		/**
		 * Default constructor.
		 *
		 * @param backend: The backend API used. Default is GRAPHICS_BACKEND_API_VULKAN.
		 */
		GraphicsBackend(GraphicsBackendAPI backend = GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN)
			: backendAPI(backend) {}

		/**
		 * Default destructor.
		 */
		virtual ~GraphicsBackend() {}

		/* Data */
	protected:
		GraphicsBackendAPI backendAPI = GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H
