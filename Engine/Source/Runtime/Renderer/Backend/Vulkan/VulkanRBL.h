#pragma once
#ifndef _DYNAMIK_VULKAN_RBL_H
#define _DYNAMIK_VULKAN_RBL_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "../RendererBackendLayer.h"

#include "Common/VulkanInstance.h"
#include "Common/VulkanSurface.h"
#include "Common/VulkanDevice.h"
#include "Common/VulkanQueue.h"

namespace Dynamik
{
	namespace Backend
	{
		class DMK_API VulkanRBL : public DMKRendererBackendLayer {
		public:
			VulkanRBL() {}
			~VulkanRBL() {}

			void initializeCore() override;

		private:
			VulkanInstance myInstance;
			VulkanSurface myBaseSurface;
			VulkanDevice myDevice;
			VulkanQueue myQueues;

			POINTER<GLFWwindow> baseWindowHandle;
		};
	}
}

#endif // !_DYNAMIK_VULKAN_RBL_H
