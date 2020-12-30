// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Interface
		{
			/** FUNCTION POINTER
			 * Create a new API instance.
			 *
			 * @param pInstanceData: The memory location to store instance data.
			 * @param enableValidation: To enable API validation or not.
			 */
			inline void (*pfCreateInstance) (void** pInstanceData, bool enableValidation) = nullptr;

			/** FUNCTION POINTER
			 * Destroy a created API instance.
			 *
			 * @param pInstanceData: The instance data pointer.
			 */
			inline void (*pfDestroyInstance) (void* pInstanceData) = nullptr;
		}
	}
}