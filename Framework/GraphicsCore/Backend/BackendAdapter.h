// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Handles.h"
#include "Inputs/InputCenter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Backend Adapter class.
		 * This is the base class for the backend and is responsible of creating the necessary backend objects,
		 * handling them and destroying them.
		 */
		class BackendAdapter {
		public:
			BackendAdapter() {}
			virtual ~BackendAdapter() {}

			virtual void Initialize(bool enableValidation = true) {}
			virtual void Terminate() {}

			virtual DisplayHandle CreateDisplay(UI32 width, UI32 height, const char* pTitle = "Dynamik Engine") { return DisplayHandle(); }
			virtual Inputs::InputCenter* GetDisplayInputCenter(const DisplayHandle& displayHandle) { return nullptr; }
			virtual void DestroyDisplay(const DisplayHandle& handle) {}

			virtual DeviceHandle CreateDevice(const DisplayHandle& displayHandle) { return DeviceHandle(); }
			virtual void DestroyDevice(const DeviceHandle& handle) {}
		};
	}
}