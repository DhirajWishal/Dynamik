// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_BACKEND_H
#define _DYNAMIK_GRAPHICS_CORE_BACKEND_H

#include "GraphicsCore/Common/Defines.h"

#include "GraphicsCore/Common/PrimitiveBuffer.h"

#include "GraphicsCore/Common/DisplayHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Graphics Backend Init Info structure.
		 * This structure contains information to initialize the required backend.
		 */
		struct DMK_API BackendInitInfo {
			// Create info structure for the display object.
			DisplayCreateInfo displayCreateInfo = {};

			// Enable the backend validation which is API specific. 
			bool enableValidation = true;

			// Enable ray tracing. If GPU accelerated ray tracing is unavailable, compute shader will be used. 
			bool enableRayTracing = false;

			// Enable anti aliasing. 
			bool enableAntiAliasing = true;

			/**
			 * Graphcis card priorities.
			 * This specifies which graphics card should be selected out of multiple graphics card locations.
			 * Highest: 0
			 * Lowest: 4
			 */
			UI32 graphicsCardPriorities[5] = { 0 };
		};

		/**
		 * Graphics Backend for the Dynamik Engine.
		 * This object is the main API which is responsible for creating and destroying graphical objects.
		 */
		class DMK_API Backend : public GObject {
		public:
			/**
			 * Default constructor.
			 *
			 * @param backend: The backend API used. Default is BACKEND_API_VULKAN.
			 */
			Backend(BackendAPI backend = BackendAPI::BACKEND_API_VULKAN)
				: backendAPI(backend) {}

			/**
			 * Default destructor.
			 */
			virtual ~Backend() {}

			/**
			 * Get the backend API.
			 */
			BackendAPI GetBackendAPI() const { return backendAPI; }

			/**
			 * Get the display handle pointer.
			 */
			DisplayHandle* GetDisplayHandle() const { return pDisplayHandle; }

		public:
			/**
			 * Initialize the graphics backend.
			 *
			 * @param initInfo: Graphics Backend Init Info structure containing the initialization information.
			 */
			virtual void Initialize(const BackendInitInfo& initInfo) {}

			/**
			 * Terminate the graphics backend.
			 */
			virtual void Terminate() {}

		public:
			/**
			 * Allocate a block of memory in the GPU heap.
			 *
			 * @param size: The size of the block in bytes.
			 * @param memoryProperty: The memory block properties.
			 */
			virtual MemoryHandle* AllocateMemory(UI64 size, MemoryProperty memoryProperty) { return nullptr; }

			/**
			 * Deallocate an allocated block of memory from the GPU heap.
			 *
			 * @param pMemoryHandle: The memory handle of the allocated memory block.
			 */
			virtual void DeallocateMemory(MemoryHandle* pMemoryHandle) {}

		public:
			/**
			 * Create a raw buffer in the GPU.
			 *
			 * @param size: The size of the buffer in bytes.
			 * @param memoryProperty: The memory properties of the block.
			 */
			virtual Buffer* CreateRawBuffer(UI64 size, MemoryProperty memoryProperty) { return nullptr; }

			/**
			 * Destroy an allocated buffer object.
			 * This method accepts any type of buffer.
			 *
			 * @param pBuffer: The buffer to be destroyed.
			 */
			virtual void DestroyBuffer(Buffer* pBuffer) {}

			/**
			 * Create a vertex buffer in the GPU.
			 *
			 * @param stride: The number of bytes for the next vertex or the size of a single vertex.
			 * @param vertexCount: The number of vertexes to be stored.
			 * @param memoryProperty: The memory properties of the block.
			 */
			virtual VertexBuffer* CreateVertexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty) { return nullptr; }

			/**
			 * Create an index buffer in the GPU.
			 *
			 * @param stride: The number of bytes for the next index or the size of a single index.
			 * @param vertexCount: The number of indexes to be stored.
			 * @param memoryProperty: The memory properties of the block.
			 */
			virtual IndexBuffer* CreateIndexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty) { return nullptr; }

			/* Data */
		protected:
			DisplayHandle* pDisplayHandle = nullptr;
			BackendAPI backendAPI = BackendAPI::BACKEND_API_VULKAN;
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H
