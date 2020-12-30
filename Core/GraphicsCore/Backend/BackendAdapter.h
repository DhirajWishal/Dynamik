// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "ViewPort.h"
#include "Inputs/InputCenter.h"

namespace DMK
{
	namespace GraphicsCore
	{
		/**
		 * Backend Adapter class.
		 * This object is the base class for the backend instances and is used by the graphics engine to create
		 * GPU bound objects.
		 */
		class BackendAdapter {
		public:
			BackendAdapter() {}
			virtual ~BackendAdapter() {}

			/**
			 * Initialize the backend adapter.
			 *
			 * @param enableValidation: Whether or not to enable API validation.
			 */
			virtual void Initialize(bool enableValidation) {}

			/**
			 * Terminate the backend adapter.
			 */
			virtual void Terminate() {}

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
			virtual DisplayHandle CreateDisplay(UI32 windowWidth, UI32 windowHeight, const char* pTitle, Inputs::InputCenter* pInputCenter = nullptr) { return DisplayHandle(); }

			/**
			 * Destroy a created display.
			 *
			 * @param handle: The display handle.
			 */
			virtual void DestroyDisplay(const DisplayHandle& handle) {}

		public:
			/**
			 * Create a new graphcis device.
			 *
			 * @param displayHandle: The display handle to which the device renders.
			 * @param tryEnableRayTracing: Try and enable ray tracing if available. Default is false. If it is requested
			 *	but unavailable, the device uses compute shaders to compute ray tracing.
			 * @return The device handle.
			 */
			virtual DeviceHandle CreateDevice(const DisplayHandle& displayHandle, bool tryEnableRayTracing = false) { return DeviceHandle(); }

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
			virtual ViewPort CreateViewPort(const DeviceHandle& deviceHandle, UI32 width, UI32 height, float xOffset = 0.0f, float yOffset = 0.0f) { return ViewPort(); }

			/**
			 * Destroy a created device handle.
			 */
			virtual void DestroyDevice(const DeviceHandle& handle) {}

		public:
			/**
			 * Create a new render target.
			 * 
			 * @param deviceHandle: The device to which the swap chain is bound to.
			 * @param type: The render target handle.
			 * @param viewPort: The view port of the target.
			 * @return The render target handle.
			 */
			virtual RenderTargetHandle CreateRenderTarget(const DeviceHandle& deviceHandle, RenderTargetType type, const ViewPort& viewPort) { return RenderTargetHandle(); }
		};
	}
}