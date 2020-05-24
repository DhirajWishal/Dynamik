#include "dmkafx.h"
#include "VulkanRBL.h"

namespace Dynamik
{
	namespace Backend
	{
		void VulkanRBL::initializeCore()
		{
			/* Initialize the Vulkan Instance */
#ifdef DMK_DEBUG
			myInstance.initialize(true);

#else
			myInstance.initialize(false);

#endif

			/* Initialize the Vulkan Surface */
			myBaseSurface.initialize(myInstance, baseWindowHandle);

			/* Initialize the Vulkan Device */
			myDevice.initialize(myInstance, myBaseSurface);

			/* Initialize the Vulkan Queues */
			myQueues.initializeQueues(myDevice);
		}
	}
}