// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Macros/Global.h"
#include "GraphicsCore/Backend/Device.h"

#include "CommandBuffer.h"
#include "Macros.h"
#include "Queue.h"
#include "ShaderModule.h"

#include "VulkanBackend/RenderTarget/SwapChain.h"
#include "VulkanBackend/RenderTarget/ColorBuffer.h"
#include "VulkanBackend/RenderTarget/DepthBuffer.h"
#include "VulkanBackend/RenderTarget/RenderPass.h"
#include "VulkanBackend/RenderTarget/FrameBuffer.h"

#include "VulkanBackend/Primitives/Buffers/StaggingBuffer.h"
#include "VulkanBackend/Primitives/Buffers/UniformBuffer.h"
#include "VulkanBackend/Primitives/VertexBufferManager.h"


#include <optional>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_beta.h>							

namespace DMK
{
	namespace VulkanBackend
	{
		class VulkanInstance;

		/**
		 * Structure containing support details for a Vulkan Swap Chain.
		 */
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities = {};		// Swap Chain capabilities.
			std::vector<VkSurfaceFormatKHR> formats = {};	// Swap Chain formats.
			std::vector<VkPresentModeKHR> presentModes = {};	// Swap Chain present modes.
		};

		/**
		 * Vulkan Device for Dynamik.
		 * This object creates all the device bound objects and structures and stores them which can be accessed by
		 * handles.
		 *
		 * This uses GLFW to create and manage the window and inputs.
		 */
		class VulkanDevice : public GraphicsCore::Device {
		public:
			VulkanDevice() {}
			~VulkanDevice() {}

			/**
			 * Initialize the device.
			 *
			 * @param initInfo: The DeviceInitInfo structure contining the initialization information.
			 * @param pInstance: The instance which the device belongs to.
			 */
			virtual void Initialize(const GraphicsCore::DeviceInitInfo& initInfo, GraphicsCore::Instance* pInstance) override final;

			/**
			 * Terminate the device.
			 * This will terminate all the created resources and objects with it.
			 */
			virtual void Terminate() override final;

		public:
			/**
			 * Create a buffer object.
			 *
			 * @param type: The type of the buffer.
			 * @param size: The size of the buffer in bytes.
			 * @return The buffer reference.
			 */
			virtual GraphicsCore::BufferRef CreateBuffer(GraphicsCore::BufferType type, UI64 size) override final;

			/**
			 * Get the buffer pointer from the device.
			 *
			 * @param ref: The buffer reference.
			 * @return The buffer pointer.
			 */
			virtual GraphicsCore::Buffer* GetBuffer(const GraphicsCore::BufferRef& ref) override final;

			/**
			 * Terminate the buffer.
			 *
			 * @param ref: The buffer ref.
			 */
			virtual void TerminateBuffer(const GraphicsCore::BufferRef& ref) override final;

		public:
			/**
			 * Begin a new frame.
			 *
			 * @return 8 bit integer representing the frame index. Returns -1 if an error has occured.
			 */
			I8 BeginFrame();

			/**
			 * End the new frame by execuring all the commands.
			 */
			void EndFrame();

		public:
			/**
			 * Get the GLFW window handle.
			 *
			 * @return GLFWwindow pointer.
			 */
			DMK_FORCEINLINE GLFWwindow* GetWindowHandle() const { return pWindowHandle; }

			/**
			 * Get the Vulkan surface.
			 *
			 * @return VkSurfaceKHR handle.
			 */
			DMK_FORCEINLINE VkSurfaceKHR GetSurface() const { return vSurface; }

			/**
			 * Get the Vulkan physical device.
			 *
			 * @return VkPhysicalDevice handle.
			 */
			DMK_FORCEINLINE VkPhysicalDevice GetPhysicalDevice() const { return vPhysicalDevice; }

			/**
			 * Get Vulkan logical device.
			 *
			 * @return VkDevice handle.
			 */
			DMK_FORCEINLINE VkDevice GetLogicalDevice() const { return vLogicalDevice; }

			/**
			 * Get the Vulkan Queues.
			 *
			 * @return Queue object.
			 */
			DMK_FORCEINLINE Queue GetQueue() const { return vQueue; }

			/**
			 * Get the init info of the device.
			 *
			 * @return DeviceInitInfo structure.
			 */
			DMK_FORCEINLINE GraphicsCore::DeviceInitInfo GetInitInfo() const { return initInfo; }

			/**
			 * Get the parent instance which the device is bound to.
			 *
			 * @return The VulkanInstance object.
			 */
			DMK_FORCEINLINE VulkanInstance* GetParentInstance() const { return pInstance; }

			/**
			 * Get the Vulkan MSAA samples.
			 *
			 * @return VkSampleCountFlags enum.
			 */
			DMK_FORCEINLINE VkSampleCountFlags GetMsaaSamples() const { return vMsaaSamples; }

			/**
			 * Vulkan Queue operator.
			 */
			operator Queue() const { return vQueue; }

			/**
			 * Vulkan Surface operator.
			 */
			operator VkSurfaceKHR() const { return vSurface; }

			/**
			 * Vulkan Physical Device operator.
			 */
			operator VkPhysicalDevice() const { return vPhysicalDevice; }

			/**
			 * Vulkan Device (logical) operator.
			 */
			operator VkDevice() const { return vLogicalDevice; }

		private:
			/**
			 * Initialize the display object.
			 */
			void InitializeDisplay();

			/**
			 * Terminate the display object.
			 */
			void TerminateDisplay();

			/**
			 * Create the window surface.
			 */
			void CreateSurface();

			/**
			 * Destroy the window surface.
			 */
			void DestroySurface();

			/**
			 * Create the Vulkan Physical Device.
			 */
			void InitializePhysicalDevice();

			/**
			 * Terminate the Vulkan Physical Device.
			 */
			void TerminatePhysicalDevice();

			/**
			 * Initialize the Vulkan logical device.
			 */
			void InitializeLogicalDevice();

			/**
			 * Terminate the Vulkan logical device.
			 */
			void TerminateLogicalDevice();

		public:
			/**
			 * Get the physical device properties.
			 *
			 * @return VkPhysicalDeviceProperties structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceProperties GetPhysicalDeviceProperties() const { return vPhysicalDeviceProperties; }

			/**
			 * Get the physical device ray tracing properties.
			 *
			 * @return VkPhysicalDeviceRayTracingPropertiesKHR structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceRayTracingPropertiesKHR GetPhysicalDeviceRayTracingProperties() const { return vPhysicalDeviceRayTracingProperties; }

			/**
			 * Get the physical device ray tracing properties.
			 *
			 * @return VkPhysicalDeviceRayTracingFeaturesKHR structure.
			 */
			DMK_FORCEINLINE VkPhysicalDeviceRayTracingFeaturesKHR GetPhysicalDeviceRayTracingFeatures() const { return vPhysicalDeviceRayTracingFeatures; }

			/**
			 * Get the surface capabilities.
			 *
			 * @return VkSurfaceCapabilitiesKHR structure.
			 */
			DMK_FORCEINLINE VkSurfaceCapabilitiesKHR GetSurfaceCapabilities() const { return vSurfaceCapabilities; }

			/**
			 * Get the Swap Chain support details.
			 *
			 * @return SwapChainSupportDetails structure.
			 */
			DMK_FORCEINLINE SwapChainSupportDetails GetSwapChainSupportDetails() const { return vSwapChainSupportDetails; }

			VkPhysicalDeviceProperties vPhysicalDeviceProperties = {};	// Physical device properties.
			VkPhysicalDeviceRayTracingFeaturesKHR vPhysicalDeviceRayTracingFeatures = {};	// Ray tracing features.
			VkPhysicalDeviceRayTracingPropertiesKHR vPhysicalDeviceRayTracingProperties = {};	// Ray tracing properties.
			VkSurfaceCapabilitiesKHR vSurfaceCapabilities = {};	// Surface capabilities.
			SwapChainSupportDetails vSwapChainSupportDetails = {};	// Vulkan Swap Chain support details.

		private:
			/**
			 * Check if a physical device is suitable to use.
			 *
			 * @param vDevice: The physical device to be checked.
			 * @return Boolean value.
			 */
			bool IsPhysicalDeviceSuitable(VkPhysicalDevice vDevice);

			/* Command Buffer */
		public:
			/**
			 * Create a new command buffer.
			 *
			 * @param vCommandBufferLevel: The level of the command buffer. Default is VK_COMMAND_BUFFER_LEVEL_PRIMARY.
			 * @return CommandBuffer object.
			 */
			CommandBuffer CreateCommandBuffer(VkCommandBufferLevel vCommandBufferLevel = VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY);

			/**
			 * Flush commands recorded in a command buffer.
			 *
			 * @param vCommandBuffer: The command buffer to execute the commands.
			 */
			void FlushCommands(const CommandBuffer& vCommandBuffer);

			/**
			 * Terminate a command buffer.
			 * This method flushes the commands (executes them) before terminating them and the command pool which
			 * they are built on.
			 *
			 * @param vCommandBuffer: The command buffer object.
			 */
			void TerminateCommandBuffer(const CommandBuffer& vCommandBuffer);

			/**
			 * Terminate a created command pool.
			 *
			 * @param commandPoolIndex: The index of the command pool.
			 */
			void TerminateCommandPool(UI64 commandPoolIndex);

			std::vector<CommandPool> vCommandPools;	// Command pools container.

			/* Render Target */
		public:
			/**
			 * Create a Swap Chain object.
			 *
			 * @param bufferCount: The number of buffers to create.
			 * @param spec: The render target attachment specification.
			 * @param extent: The extent of the buffers.
			 * @return Vulkan Swap Chain handle.
			 */
			GraphicsCore::RenderTargetAttachmentHandle CreateSwapChain(UI64 bufferCount, GraphicsCore::RenderTargetAttachmentSpecification spec, const VkExtent2D& extent);

			/**
			 * Destroy a created swap chain.
			 *
			 * @param vSwapChainHandle: The swap chain object handle to be destroyed.
			 */
			void DestroySwapChain(GraphicsCore::RenderTargetAttachmentHandle vSwapChainHandle);

			/**
			 * This method destroys all the created swap chain objects.
			 */
			void DestroyAllSwapChains();

			/**
			 * Get a swap chain from the store.
			 *
			 * @param mHandle: The handle of the swap chain.
			 * @return Vulkan Swap Chain pointer.
			 */
			SwapChain* GetSwapChain(GraphicsCore::RenderTargetAttachmentHandle mHandle) const;

			std::vector<SwapChain> vSwapChains;	// All the created swap chains.

			/**
			 * Create a Color Buffer object.
			 *
			 * @param bufferCount: The number of buffers to create.
			 * @param spec: The render target attachment specification.
			 * @param extent: The extent of the buffers.
			 * @return Vulkan Color Buffer handle.
			 */
			GraphicsCore::RenderTargetAttachmentHandle CreateColorBuffer(UI64 bufferCount, GraphicsCore::RenderTargetAttachmentSpecification spec, const VkExtent2D& extent);

			/**
			 * Destroy a created Color Buffer object.
			 *
			 * @param vColorBufferHandle: The handle of the color buffer to be destroyed.
			 */
			void DestroyColorBuffer(GraphicsCore::RenderTargetAttachmentHandle vColorBufferHandle);

			/**
			 * This method will destroy all the created color buffers in this device.
			 */
			void DestroyAllColorBuffers();

			/**
			 * Get a color buffer from the store.
			 *
			 * @param mHandle: The handle of the swap chain.
			 * @return Vulkan Color Buffer pointer.
			 */
			ColorBuffer* GetColorBuffer(GraphicsCore::RenderTargetAttachmentHandle mHandle) const;

			std::vector<ColorBuffer> vColorBuffers;	// All the created color buffers.

			/**
			 * Create a Depth Buffer object.
			 *
			 * @param bufferCount: The number of buffers to create.
			 * @param spec: The render target attachment specification.
			 * @param extent: The extent of the buffers.
			 * @return Vulkan Depth Buffer handle.
			 */
			GraphicsCore::RenderTargetAttachmentHandle CreateDepthBuffer(UI64 bufferCount, GraphicsCore::RenderTargetAttachmentSpecification spec, const VkExtent2D& extent);

			/**
			 * Destroy a created Depth Buffer object.
			 *
			 * @param vDepthBufferHandle: The handle of the depth buffer to be destroyed.
			 */
			void DestroyDepthBuffer(GraphicsCore::RenderTargetAttachmentHandle vDepthBufferHandle);

			/**
			 * This method will destroy all the created depth buffers in this device.
			 */
			void DestroyAllDepthBuffers();

			/**
			 * Get a depth buffer from the store.
			 *
			 * @param mHandle: The handle of the swap chain.
			 * @return Vulkan Depth Buffer pointer.
			 */
			DepthBuffer* GetDepthBuffer(GraphicsCore::RenderTargetAttachmentHandle mHandle) const;

			std::vector<DepthBuffer> vDepthBuffers;	// All the created depth buffers.

			/**
			 * Create a new render pass and return its handle.
			 *
			 * @param mAttachments: The render target attachment handles.
			 * @return The render pass handle.
			 */
			RenderPassHandle CreateRenderPass(const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments, std::vector<VkSubpassDependency> vDependencies = { RenderPass::CreateDefaultSubpassDependency() });

			/**
			 * Terminate a created render pass object.
			 *
			 * @param mHandle: The handle of the render pass.
			 */
			void DestroyRenderPass(const RenderPassHandle& mHandle);

			/**
			 * Destroy all the created render passes.
			 */
			void DestroyAllRenderPasses();

			/**
			 * Get a render pass from the store.
			 *
			 * @param mHandle: The handle of the render pass.
			 * @return The render pass pointer.
			 */
			RenderPass* GetRenderPass(RenderPassHandle mHandle) const;

			std::vector<RenderPass> vRenderPasses;	// All the created render passes.

			/**
			 * Create a new frame buffer and return its handle.
			 * The frame buffer structure contains all the Vulkan Frame Buffer handles.
			 *
			 * @param mRenderPassHandle: The render pass handle.
			 * @param mAttachments: The render target attachments.
			 * @param bufferCount: The number of frame buffer handles to create.
			 * @param extent: The extent of the buffers.
			 */
			FrameBufferHandle CreateFrameBuffer(const RenderPassHandle& mRenderPassHandle, const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments, UI64 bufferCount, const VkExtent2D& extent);

			/**
			 * Terminate a frame buffer using its handle.
			 *
			 * @param mHandle: The frame buffer handle.
			 */
			void DestroyFrameBuffer(const FrameBufferHandle& mHandle);

			/**
			 * Destroy all the created frame buffers.
			 */
			void DestroyAllFrameBuffers();

			/**
			 * Get a frame buffer from the store.
			 *
			 * @param mHandle: The frame buffer handle.
			 * @return The frame buffer object pointer.
			 */
			FrameBuffer* GetFrameBuffer(FrameBufferHandle mHandle) const;

			std::vector<FrameBuffer> vFrameBuffers;	// All the created frame buffers.

			/* Shaders */
		public:
			ShaderModule CreateShaderModule(const GraphicsCore::ShaderCode& code);

			/* Buffers */
		public:
			/**
			 * Destroy a buffer.
			 *
			 * @param handle: The buffer handle.
			 */
			void DestroyBuffer(const GraphicsCore::BufferHandle& handle);

			/**
			 * Destroy all buffers of a specific type.
			 * If the type is UNDEFINED, all the buffers are terminated (buffers of all types).
			 *
			 * @param type: The buffer type.
			 */
			void DestroyAllBuffers(GraphicsCore::BufferType type = GraphicsCore::BufferType::UNDEFINED);

			/**
			 * Submit data to the buffer.
			 *
			 * @param handle: The buffer handle.
			 * @param pData: The data pointer.
			 * @param size: The size of the data block to be submitted.
			 * @param offset: The offset of the buffer to be submitted to.
			 */
			void SubmitDataToBuffer(const GraphicsCore::BufferHandle& handle, void* pData, UI64 size, UI64 offset);

			VertexBufferManager mVertexBuffermanager = {};	// The vertex buffer manager.
			std::vector<StaggingBuffer> mStaggingBuffers;	// All the stagging buffers owned by the device.
			std::vector<UniformBuffer> mUniformBuffers;	// All the uniform buffers owned by the device.

		private:
			Queue vQueue = {};	// Vulkan queue object.

			std::vector<const char*> deviceExtensions;	// Device extensions.

			GLFWwindow* pWindowHandle = nullptr;	// The GLFW window pointer.
			VkSurfaceKHR vSurface = VK_NULL_HANDLE;	// The display surface.

			VkPhysicalDevice vPhysicalDevice = VK_NULL_HANDLE;	// The physical device.
			VkDevice vLogicalDevice = VK_NULL_HANDLE;	// The logical device.

			VulkanInstance* pInstance = nullptr;	// The Vulkan instance pointer.

			GraphicsCore::DeviceInitInfo initInfo = {};	// Initialize information of the device.

			VkSampleCountFlags vMsaaSamples = VK_SAMPLE_COUNT_1_BIT;	// Vulkan Multi Sampling Anti Aliasing bits.

			I8 frameIndex = 0;	// The current frame index.
		};
	}
}
