// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Thread/CommandHub.h"
#include "Thread/Commands/CommandQueue.h"

namespace DMK
{
	namespace GraphicsCore
	{
		using namespace GraphicsCore;

		/**
		 * Graphics Backend API enum.
		 */
		enum class GraphicsBackendAPI {
			GRAPHICS_BACKEND_API_VULKAN,
			GRAPHICS_BACKEND_API_DIRECT_X,
			GRAPHICS_BACKEND_API_WEB_GPU,
		};

		/**
		 * Graphics Engine Create Info structure.
		 * This structure defines how the graphics engine should be initialized.
		 */
		struct GraphicsEngineCreateInfo {
			GraphicsBackendAPI backendAPI = GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN;	// Backend API.

			bool enableValidation = true;	// Enable API validation.
			bool tryEnableRayTracing = true;	// Try and enable ray tracing. If not supported, compute shaders are used.
		};

		/**
		 * Graphics Engine for the Dynamik Engine.
		 * This object is the high level API of the Graphics system. All the graphics related tasks are done through
		 * this.
		 * The graphics backend (the backend thread) is managed by this object and direct commands to it shall be
		 * dont by this object by calling the GetCommandQueue() method.
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
			 * Get the backend command queue.
			 *
			 * @return Threads::CommandQueue<> pointer.
			 */
			Threads::CommandQueue<THREAD_MAX_COMMAND_COUNT>* GetCommandQueue() { return &mCommandQueue; }

			/**
			 * Initialize the Graphics Backend.
			 *
			 * By enabling validation, if any invalid data were to be passed, the backend API can detect it and
			 * log it to the console. This ofcourse cost a little bit of performance. Enabling this is highly
			 * recommended for Debugging the application and when shipping the product, we recommend disabling
			 * API validation.
			 * 
			 * @param enableValidation: Boolean value to enable or disable validation. Default is true.
			 */
			void InitializeBackend(bool enableValidation = true);

		private:
			std::thread mBackendThread;	// Backend thread object.
			Threads::CommandQueue<THREAD_MAX_COMMAND_COUNT> mCommandQueue;	// Backend command queue.
		};
	}
}
