// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_ENGINE_H
#define _DYNAMIK_GRAPHICS_ENGINE_H

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
			bool enableValidation = true;	// Enable API validation.
			bool tryEnableRayTracing = true;	// Try and enable ray tracing. If not supported, compute shaders are used.
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

		public:
			/**
			 * Graphics thread function.
			 * This function will be executed on another thread by the engine. It takes a command hub object pointer
			 * as an argument to communitcate with the game thread and to share information.
			 *
			 * @param pCommandHub: The command hub object instance.
			 */
			static void GraphicsThread(Thread::CommandHub* pCommandHub);
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_ENGINE_H
