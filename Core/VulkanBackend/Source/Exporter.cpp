// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/Exporter.h"

#include "VulkanBackend/VulkanInstance.h"

#include "GraphicsCore/Backend/Interface/InstanceFunctions.h"

namespace DMK
{
	namespace VulkanBackend
	{
		void ExportFunctions()
		{
			GraphicsCore::Interface::pfCreateInstance = CreateInstance;
			GraphicsCore::Interface::pfDestroyInstance = DestroyInstance;
		}
	}
}