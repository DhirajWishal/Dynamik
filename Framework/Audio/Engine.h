// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include "Thread/Commands/CommandQueue.h"

#include <thread>

namespace DMK
{
	namespace Audio
	{
		/**
		 * Audio Backend Type enum.
		 */
		enum class AudioBackendType : UI8 {
			UNDEFINED,
			X_AUDIO_2,
		};

		/**
		 * Audio Engine for Dynamik.
		 * This object is responsible of creating, maintaining and terminating the selected audio backend.
		 */
		class Engine {
		public:
			Engine() {}
			~Engine() {}

			/**
			 * Initialize the engine.
			 * This method initialized the basics of the engine and also the audio backend.
			 *
			 * @param mBackendType: The audio backend type.
			 */
			void Initialize(AudioBackendType mBackendType);

			/**
			 * Terminate the engine.
			 */
			void Terminate();

		public:
			/**
			 * Get the command queue of the Audio Engine.
			 *
			 * @return Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT> pointer.
			 */
			Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT>* GetCommandQueue() const { return const_cast<Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT>*>(&mCommandQueue); }

		private:
			std::thread mBackendThread;	// The backend thread.
			Thread::CommandQueue<THREAD_MAX_COMMAND_COUNT> mCommandQueue;

			AudioBackendType mBackendType = AudioBackendType::UNDEFINED;	// Backend type.
		};
	}
}