// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Device.h"

namespace DMK
{
	namespace GraphcisCore
	{
		/**
		 * Graphics Instance object.
		 */
		class Instance {
		public:
			Instance() {}
			~Instance() {}

			void Initialize() {}

		public:
			constexpr Device* CreateDevice(UI32 width, UI32 height, const char* pTitle) { return pfCreateDevice(this, width, height, pTitle); }

		private:
			void SetupVulkan();
			//void SetupDirectX12() {}
			//void SetupWebGPU() {}

		private:
			Device* (*pfCreateDevice)(Instance* pInstance, UI32 width, UI32 height, const char* pTitle) = nullptr;

		public:
			void* pBackendDataPointer = nullptr;
		};
	}
}