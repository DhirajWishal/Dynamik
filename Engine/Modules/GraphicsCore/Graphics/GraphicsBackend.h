#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H
#define _DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H

#include "GraphicsCore/Common/GDefines.h"

#include "GraphicsCore/Common/GPrimitiveBuffer.h"

#include "GraphicsCore/Common/GDisplayHandle.h"

namespace DMK
{
	/**
	 * Graphics Backend Init Info structure.
	 * This structure contains information to initialize the required backend.
	 */
	struct DMK_API GraphicsBackendInitInfo {
		// Create info structure for the display object.
		GDisplayCreateInfo displayCreateInfo = {};

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
	class DMK_API GraphicsBackend : public GObject {
	public:
		/**
		 * Default constructor.
		 *
		 * @param backend: The backend API used. Default is GRAPHICS_BACKEND_API_VULKAN.
		 */
		GraphicsBackend(GraphicsBackendAPI backend = GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN)
			: backendAPI(backend) {}

		/**
		 * Default destructor.
		 */
		virtual ~GraphicsBackend() {}

		/**
		 * Get the backend API.
		 */
		GraphicsBackendAPI GetBackendAPI() const { return backendAPI; }

		/**
		 * Get the display handle pointer.
		 */
		GDisplayHandle* GetDisplayHandle() const { return pDisplayHandle; }

	public:
		/**
		 * Initialize the graphics backend.
		 *
		 * @param initInfo: Graphics Backend Init Info structure containing the initialization information.
		 */
		virtual void Initialize(const GraphicsBackendInitInfo& initInfo) {}

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
		virtual GMemoryHandle* AllocateMemory(UI64 size, GMemoryProperty memoryProperty) { return nullptr; }

		/**
		 * Deallocate an allocated block of memory from the GPU heap.
		 *
		 * @param pMemoryHandle: The memory handle of the allocated memory block.
		 */
		virtual void DeallocateMemory(GMemoryHandle* pMemoryHandle) {}

	public:
		/**
		 * Create a raw buffer in the GPU.
		 *
		 * @param size: The size of the buffer in bytes.
		 * @param memoryProperty: The memory properties of the block.
		 */
		virtual GBuffer* CreateRawBuffer(UI64 size, GMemoryProperty memoryProperty) { return nullptr; }

		/**
		 * Destroy an allocated buffer object.
		 * This method accepts any type of buffer.
		 *
		 * @param pBuffer: The buffer to be destroyed.
		 */
		virtual void DestroyBuffer(GBuffer* pBuffer) {}

		/**
		 * Create a vertex buffer in the GPU.
		 *
		 * @param stride: The number of bytes for the next vertex or the size of a single vertex.
		 * @param vertexCount: The number of vertexes to be stored.
		 * @param memoryProperty: The memory properties of the block.
		 */
		virtual GVertexBuffer* CreateVertexBuffer(UI64 stride, UI64 vertexCount, GMemoryProperty memoryProperty) { return nullptr; }

		/**
		 * Create an index buffer in the GPU.
		 *
		 * @param stride: The number of bytes for the next index or the size of a single index.
		 * @param vertexCount: The number of indexes to be stored.
		 * @param memoryProperty: The memory properties of the block.
		 */
		virtual GIndexBuffer* CreateIndexBuffer(UI64 stride, UI64 vertexCount, GMemoryProperty memoryProperty) { return nullptr; }

		/* Data */
	protected:
		GDisplayHandle* pDisplayHandle = nullptr;
		GraphicsBackendAPI backendAPI = GraphicsBackendAPI::GRAPHICS_BACKEND_API_VULKAN;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_GRAPHICS_BACKEND_H
