// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_DEVICE_H
#define _DYNAMIK_GRAPHICS_CORE_DEVICE_H

#include "RenderTarget.h"
#include "Defines.h"
#include "Core/Types/DataTypes.h"

#include "ShaderModule.h"

namespace DMK
{
	namespace GraphicsCore
	{
		class BackendInstance;

		/**
		 * Device Init Info structure.
		 * This structure contains information required to initialize the device.
		 */
		struct DeviceInitInfo {
			const char* pTitle = "Engine Dev Kit";	// The title of the display/ window.
			const char* pIconFile = nullptr;	// The icon file path.

			UI32 windowWidth = 1280;	// The width of the window.
			UI32 windowHeight = 720;	// The height of the window.

			bool enableValidation = true;	// Enable validation. Default is true.
			bool enableRayTracing = false;	// Enable ray tracing. Default is false.
		};

		/**
		 * View Port object for the Device.
		 * This object contains information about the view port which is created by a device.
		 */
		struct ViewPort {
			/**
			 * Default constructor.
			 */
			ViewPort() = default;

			/**
			 * Construct the view port using the device which it was created with.
			 *
			 * @param pDevice: The device which created it.
			 */
			ViewPort(class GDevice* pDevice) : pDevice(pDevice) {}

			/**
			 * Set the device of the view port.
			 *
			 * @param pDevice: The device which created the view port.
			 */
			DMK_FORCEINLINE void SetDevice(class GDevice* pDevice) { this->pDevice = pDevice; }

			/**
			 * Get the device of the view port.
			 *
			 * @return GDevice class pointer.
			 */
			DMK_FORCEINLINE class GDevice* GetDevice() const { this->pDevice; }

			/**
			 * Set the offsets of the view port.
			 * Offsets are calculated from the top left corner of the window/ display in window coordinates.
			 *
			 * @param xOffset: The xOffset of the view port.
			 * @param yOffset: The yOffset of the view port.
			 */
			DMK_FORCEINLINE void SetOffsets(float xOffset, float yOffset) { this->xOffset = xOffset, this->yOffset = yOffset; }

			/**
			 * Get the offsets of the view port.
			 *
			 * @return std::pair<float, float> containing the xOffset and yOffset.
			 */
			DMK_FORCEINLINE std::pair<float, float> GetOffsets() const { return { xOffset, yOffset }; }

			/**
			 * Set the size of the viewport.
			 *
			 * @param width: The width of the viewport.
			 * @param height: The height of the viewport.
			 */
			DMK_FORCEINLINE void SetSize(UI32 width, UI32 height) { this->width = width, this->height = height; }

			/**
			 * Get the width and height of the view port.
			 *
			 * @return std::pair<UI32, UI32> containing the width and height.
			 */
			DMK_FORCEINLINE std::pair<UI32, UI32> GetSize() { return { width, height }; }

			class GDevice* pDevice = nullptr;	// The device which created the viewport.

			float xOffset = 0.0f, yOffset = 0.0f;	// Offsets of the view port in the window space.
			UI32 width = 0, height = 0;	// Width and Height of the view port.
		};

		/**
		 * Graphics Device for Dynamik.
		 * This object stores information about the graphics device which the graphics and compute engines use.
		 *
		 * This object also contains the display object which is used to render data to.
		 */
		class GDevice : public GObject {
		public:
			/**
			 * Default constructor.
			 */
			GDevice() {}

			/**
			 * Default destructor.
			 */
			virtual ~GDevice() {}

			/**
			 * Initialize the device.
			 *
			 * @param initInfo: The DeviceInitInfo structure contining the initialization information.
			 */
			virtual void Initialize(const DeviceInitInfo& initInfo) {}

			/**
			 * Get the init info of the device.
			 *
			 * @return DeviceInitInfo structure.
			 */
			DMK_FORCEINLINE DeviceInitInfo GetInitInfo() const { return initInfo; }

			/**
			 * Terminate the device.
			 */
			virtual void Terminate() {}

			/**
			 * Set the parent instance which created the device.
			 *
			 * @param pParentInstance: The parent instance pointer.
			 */
			DMK_FORCEINLINE void SetParentInstance(BackendInstance* pParentInstance) { this->pBackendInstance = pParentInstance; }

			/**
			 * Get the parent instance pointer.
			 *
			 * @return The pointer to the parent instance.
			 */
			DMK_FORCEINLINE BackendInstance* GetParentInstance() const { return this->pBackendInstance; }

			/**
			 * Get the anti aliasing samples supported by the device.
			 *
			 * @return DMK::GraphicsCore::AntiAliasingSamples enum.
			 */
			virtual AntiAliasingSamples GetMSAASamples() { return AntiAliasingSamples::ANTI_ALIASING_SAMPLES_1_BIT; }

			/**
			 * Get the display extent.
			 *
			 * @return std::pair<UI32, UI32> object containing the extent.
			 */
			DMK_FORCEINLINE std::pair<UI32, UI32> GetDisplayExtent() const { return { GetInitInfo().windowWidth, GetInitInfo().windowHeight }; }

			/**
			 * Create a view port using the device.
			 * Since view ports are API specific, the pointer of the created view port is returned.
			 *
			 * @param width: The width of the view port.
			 * @param height: The height of the view port.
			 * @param xOffset: The xOffset of the view port. Default is 0.0f.
			 * @param yOffset: The yOffset of the view port. Default is 0.0f.
			 */
			virtual ViewPort CreateViewPort(UI32 width, UI32 height, float xOffset = 0.0f, float yOffset = 0.0f) { return ViewPort(); }

			/**
			 * Makes the device stay idle for a short period of time. This is used when an command buffer is executed.
			 */
			virtual void IdleCall() {}

			/**
			 * Begin a new frame.
			 *
			 * @return 8 bit integer representing the frame index. Returns -1 if an error has occured.
			 */
			virtual I8 BeginFrame() { return 0; }

			/**
			 * End the new frame by execuring all the commands.
			 */
			virtual void EndFrame() {}

		public:
			/**
			 * Create a render target to render object to.
			 *
			 * @param flags: Render Target Attachment Flags containing the attachment information.
			 * @return The pointer to the created render target.
			 */
			virtual RenderTarget* CreateRenderTarget(RenderTargetAttachmentFlags flags) { return nullptr; }

			/**
			 * Destroy a created render target object.
			 *
			 * @param pRenderTarget: The created render target pointer.
			 */
			virtual void DestroyRenderTarget(RenderTarget* pRenderTarget) {}

		public:
			/**
			 * Create a new shader module object.
			 *
			 * @param pAsset: The shader asset path.
			 * @param location: The location of the shader in the graphics pipeline.
			 * @return The newly created shader module.
			 */
			ShaderModule CreateShaderModule(const wchar_t* pAsset, ShaderLocation location);

		protected:
			BackendInstance* pBackendInstance = nullptr;	// The backend object pointer which created the device.

			DeviceInitInfo initInfo = {};	// Initialize information of the device.
			I8 frameIndex = 0;	// The current frame index.
		};
	}
}

#endif // !_DYNAMIK_GRAPHICS_CORE_DEVICE_H
