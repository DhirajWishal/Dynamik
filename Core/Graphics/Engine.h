// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_ENGINE_H
#define _DYNAMIK_GRAPHICS_ENGINE_H

#include "GraphicsCore/Backend/Common/GDevice.h"

#include "Mesh/MeshHandle.h"

namespace DMK
{
	namespace Graphics
	{
		using namespace GraphicsCore;

		/**
		 * Graphics Engine Create Info structure.
		 * This structure defines how the graphics engine should be initialized.
		 */
		struct GraphicsEngineCreateInfo {

		};

		/**
		 * Graphics Engine for the Dynamik Engine.
		 * This object is the high level API of the Graphics system. All the graphics related tasks are done through
		 * this.
		 */
		class Engine {
		public:
			/**
			 * Default constructor.
			 */
			Engine() {}

			/**
			 * Default destructor.
			 */
			~Engine() {}

			/**
			 * Initialize the Graphics Engine.
			 *
			 * @param initInfo: The initialization information structure.
			 */
			void Initialize(const GraphicsEngineCreateInfo& initInfo);

			/**
			 * Get the graphics device used by the engine.
			 *
			 * @return: const GDevice pointer.
			 */
			const GDevice* GetDevice() const;

		private:
			/**
			 * Get the graphics device used by the engine.
			 *
			 * @return: GDevice pointer.
			 */
			GDevice* GetDevice();

		private:
			GDevice* pDevice = nullptr;	// The graphics backend device pointer.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_ENGINE_H
