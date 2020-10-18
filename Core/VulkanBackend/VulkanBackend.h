// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_H
#define _DYNAMIK_VULKAN_BACKEND_H

#include "GraphicsCore/Graphics/Backend.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace GraphicsCore
	{
		namespace VulkanBackend
		{
			/**
			 * Vulkan Backend object for the Dynamik Engine.
			 */
			class DMK_API VulkanBackend : public Backend {
			public:
				/**
				 * Default constructor.
				 */
				VulkanBackend() : Backend(BackendAPI::BACKEND_API_VULKAN) {}

				/**
				 * Default destructor.
				 */
				~VulkanBackend() {}

			public:
				/**
				 * Initialize the graphics backend.
				 *
				 * @param initInfo: Graphics Backend Init Info structure containing the initialization information.
				 */
				virtual void Initialize(const BackendInitInfo& initInfo) override final;

				/**
				 * Terminate the graphics backend.
				 */
				virtual void Terminate() override final;

			public:
				/**
				 * Allocate a block of memory in the GPU heap.
				 *
				 * @param size: The size of the block in bytes.
				 * @param memoryProperty: The memory block properties.
				 */
				virtual MemoryHandle* AllocateMemory(UI64 size, MemoryProperty memoryProperty) override final;

				/**
				 * Deallocate an allocated block of memory from the GPU heap.
				 *
				 * @param pMemoryHandle: The memory handle of the allocated memory block.
				 */
				virtual void DeallocateMemory(MemoryHandle* pMemoryHandle) override final;

			public:
				/**
				 * Create a raw buffer in the GPU.
				 *
				 * @param size: The size of the buffer in bytes.
				 * @param memoryProperty: The memory properties of the block.
				 */
				virtual Buffer* CreateRawBuffer(UI64 size, MemoryProperty memoryProperty) override final;

				/**
				 * Destroy an allocated buffer object.
				 * This method accepts any type of buffer.
				 *
				 * @param pBuffer: The buffer to be destroyed.
				 */
				virtual void DestroyBuffer(Buffer* pBuffer) override final;

				/**
				 * Create a vertex buffer in the GPU.
				 *
				 * @param stride: The number of bytes for the next vertex or the size of a single vertex.
				 * @param vertexCount: The number of vertexes to be stored.
				 * @param memoryProperty: The memory properties of the block.
				 */
				virtual VertexBuffer* CreateVertexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty) override final;

				/**
				 * Create an index buffer in the GPU.
				 *
				 * @param stride: The number of bytes for the next index or the size of a single index.
				 * @param vertexCount: The number of indexes to be stored.
				 * @param memoryProperty: The memory properties of the block.
				 */
				virtual IndexBuffer* CreateIndexBuffer(UI64 stride, UI64 vertexCount, MemoryProperty memoryProperty) override final;

			private:
				/**
				 * Create the Vulkan instance.
				 */
				void CreateInstance();

				/**
				 * Create the Vulkan debugger.
				 */
				void CreateDebugger();

				/**
				 * Create the display object.
				 */
				void CreateDisplay(const DisplayCreateInfo& displayCreateInfo);

				/**
				 * Create the Vulkan physical device.
				 */
				void CreatePhysicalDevice();

				/**
				 * Create the Vulkan logical device.
				 */
				void CreateLogicalDevice();

				/**
				 * Destroy the Vulkan instance.
				 */
				void DestroyInstance();

				/**
				 * Destroy the Vulkan debugger.
				 */
				void DestroyDebugger();

				/**
				 * Destroy the display object.
				 */
				void DestroyDisplay();

				/**
				 * Destroy the Vulkan physical device.
				 */
				void DestroyPhysicalDevice();

				/**
				 * Destroy the Vulkan logical device.
				 */
				void DestroyLogicalDevice();

				/* Utilities */
			private:
				/**
				 * Get the Vulkan instance.
				 */
				VkInstance GetInstance() const { return vInstance; }

				/**
				 * Get the Vulkan logical device.
				 */
				VkDevice GetLogicalDevice() const { return vLogicalDevice; }

				/**
				 * Get the Vulkan physical device.
				 */
				VkPhysicalDevice GetPhysicalDevice() const { return vPhysicalDevice; }

				/* Data */
			private:
				bool enableValidation = true;

				VkInstance vInstance = VK_NULL_HANDLE;
				VkDevice vLogicalDevice = VK_NULL_HANDLE;
				VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;
				VkDebugUtilsMessengerEXT vDebugMessenger = VK_NULL_HANDLE;

				std::vector<const char*> instanceExtensions;
				std::vector<const char*> validationLayers;
				std::vector<const char*> deviceExtensions;
			};
		}
	}
}

#endif // !_DYNAMIK_VULKAN_BACKEND_H
