// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_ENGINE_H
#define _DYNAMIK_GRAPHICS_ENGINE_H

#include "GraphicsCore/Graphics/Backend.h"

#include "GraphicsCore/Entities/StaticModel.h"

namespace DMK
{
	namespace GraphicsEngine
	{
		/**
		 * Graphics Engine of the Dynamik Engine.
		 */
		class DMK_API Engine {
		public:
			/**
			 * Default constructor.
			 */
			Engine() {}

			/**
			 * Default destructor.
			 */
			~Engine() {}

		public:
			/**
			 * Initialize the graphics backend API.
			 *
			 * @param API: The backend API.
			 * @param backendInitInfo: The graphics backend init info structure containing the initialization info.
			 */
			void InitializeBackend(GraphicsCore::BackendAPI API, GraphicsCore::BackendInitInfo backendInitInfo);

			/**
			 * Get the backend of the graphics engine.
			 */
			GraphicsCore::Backend* GetBackend() const { return pBackend; }

			/* Data */
		private:
			GraphicsCore::Backend* pBackend = nullptr;
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_ENGINE_H
