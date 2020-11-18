// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_ENGINE_H
#define _DYNAMIK_GRAPHICS_ENGINE_H

#include "GraphicsCore/Backend/Common/GDevice.h"
#include "Thread/CommandHub.h"

namespace DMK
{
	namespace GraphicsCore
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
			 * @return const GDevice pointer.
			 */
			const GDevice* GetDevice() const;

		public:
			/**
			 * Graphics thread function.
			 * This function will be executed on another thread by the engine. It takes a command hub object pointer
			 * as an argument to communitcate with the game thread and to share information.
			 *
			 * @param pCommandHub: The command hub object instance.
			 */
			static void GraphicsThread(Thread::CommandHub* pCommandHub);

		private:
			/**
			 * Get the graphics device used by the engine.
			 *
			 * @return GDevice pointer.
			 */
			GDevice* GetDevice();

		private:
			GDevice* pDevice = nullptr;	// The graphics backend device pointer.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_ENGINE_H
