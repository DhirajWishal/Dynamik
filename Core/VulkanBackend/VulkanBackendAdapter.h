// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "GraphicsCore/Backend/BackendAdapter.h"
#include "Core/Types/SparseSet.h"
#include "Objects/Device.h"

#include "Objects/RenderTarget/RenderTargetSB3D.h"

#include <vulkan/vulkan.h>

namespace DMK
{
	namespace VulkanBackend
	{
		/**
		 * Vulkan Backend Adapter object.
		 */
		class VulkanBackendAdapter : public GraphicsCore::BackendAdapter {
		public:
			VulkanBackendAdapter() {}
			~VulkanBackendAdapter() {}

			/**
			 * Initialize the backend adapter.
			 *
			 * @param enableValidation: Whether or not to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) override final;

			/**
			 * Terminate the backend adapter.
			 */
			virtual void Terminate() override final;

		public:
			/**
			 * Create a new display.
			 *
			 * @param windowWidth: The width of the window.
			 * @param windowHeight: The height of the window.
			 * @param pTitle: The title of the window.
			 * @param pInputCenter: The input center pointer. Default is nullptr. Once an input center is attached,
			 *	inputs can be streamed from the device window to the application.
			 * @return The display handle.
			 */
			virtual GraphicsCore::DisplayHandle CreateDisplay(UI32 windowWidth, UI32 windowHeight, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr) override final;

			/**
			 * Destroy a created display.
			 *
			 * @param handle: The display handle.
			 */
			virtual void DestroyDisplay(const GraphicsCore::DisplayHandle& handle) override final;

		public:
			/**
			 * Create a new graphcis device.
			 *
			 * @param displayHandle: The display handle to which the device renders.
			 * @param tryEnableRayTracing: Try and enable ray tracing if available. Default is false. If it is requested
			 *	but unavailable, the device uses compute shaders to compute ray tracing.
			 * @return The device handle.
			 */
			virtual GraphicsCore::DeviceHandle CreateDevice(const GraphicsCore::DisplayHandle& displayHandle, bool tryEnableRayTracing = false) override final;

			/**
			 * Create a new view port using the device.
			 *
			 * @param deviceHandle: The device handle to create the view port.
			 * @param width: The width of the view port.
			 * @param height: The height of the view port.
			 * @param xOffset: The X offset of the view port.
			 * @param yOffset: The Y offset of the view port.
			 * @return ViewPort structure.
			 */
			virtual GraphicsCore::ViewPort CreateViewPort(const GraphicsCore::DeviceHandle& deviceHandle, UI32 width, UI32 height, float xOffset = 0.0f, float yOffset = 0.0f) override final;

			/**
			 * Destroy a created device handle.
			 * 
			 * @param handle: The device handle.
			 */
			virtual void DestroyDevice(const GraphicsCore::DeviceHandle& handle) override final;

		public:
			/**
			 * Create a new render target.
			 *
			 * @param deviceHandle: The device to which the swap chain is bound to.
			 * @param type: The render target handle.
			 * @param viewPort: The view port of the target.
			 * @return The render target handle.
			 */
			virtual GraphicsCore::RenderTargetHandle CreateRenderTarget(const GraphicsCore::DeviceHandle& deviceHandle, GraphicsCore::RenderTargetType type, const GraphicsCore::ViewPort& viewPort) override final;
		
		private:
			SparseSet<VulkanDevice, GraphicsCore::DeviceHandle> mDevices;
			SparseSet<VulkanDisplay, GraphicsCore::DisplayHandle> mDisplays;

			SparseSet<RenderTargetSB3D, UI16> mRenderTargetsSB3D;

			VulkanInstance vInstance = {};
		};
	}
}