// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendAdapter.h"
#include "VulkanBackend/Macros.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Types/Utilities.h"

#include <iostream>

namespace DMK
{
	namespace VulkanBackend
	{
		void VulkanBackendAdapter::Initialize(bool enableValidation)
		{
			// Setup GLFW.
			InitializeGLFW();

			// Create the instance.
			vInstance = VulkanInstance::Create(enableValidation);
		}

		void VulkanBackendAdapter::Terminate()
		{
			// Destroy all devices.
			{
				for (auto itr = mDevices.Begin(); itr != mDevices.End(); itr++)
					VulkanDevice::Destroy(vInstance, *itr);

				mDevices.Clear();
			}

			// Destroy all displays.
			{
				for (auto itr = mDisplays.Begin(); itr != mDisplays.End(); itr++)
					VulkanDisplay::Destroy(*itr);

				mDisplays.Clear();
			}

			// Destroy the instance.
			VulkanInstance::Destroy(vInstance);

			// Terminate GLFW.
			TerminateGLFW();
		}

		GraphicsCore::DisplayHandle VulkanBackendAdapter::CreateDisplay(UI32 windowWidth, UI32 windowHeight, const char* pTitle, Inputs::InputCenter* pInputCenter)
		{
			return mDisplays.Insert(std::move(VulkanDisplay::Create(windowWidth, windowHeight, pTitle, pInputCenter)));
		}

		void VulkanBackendAdapter::DestroyDisplay(const GraphicsCore::DisplayHandle& handle)
		{
			VulkanDisplay::Destroy(mDisplays.Get(handle));
			mDisplays.Remove(handle);
		}

		GraphicsCore::DeviceHandle VulkanBackendAdapter::CreateDevice(const GraphicsCore::DisplayHandle& displayHandle, bool tryEnableRayTracing)
		{
			return mDevices.Insert(std::move(VulkanDevice::Create(vInstance, mDisplays.Get(displayHandle))));
		}

		GraphicsCore::ViewPort VulkanBackendAdapter::CreateViewPort(const GraphicsCore::DeviceHandle& deviceHandle, UI32 width, UI32 height, float xOffset, float yOffset)
		{
			return GraphicsCore::ViewPort(deviceHandle, width, height, xOffset, yOffset);
		}

		void VulkanBackendAdapter::DestroyDevice(const GraphicsCore::DeviceHandle& handle)
		{
			VulkanDevice::Destroy(vInstance, mDevices.Get(handle));
			mDevices.Remove(handle);
		}

		GraphicsCore::RenderTargetHandle VulkanBackendAdapter::CreateRenderTarget(const GraphicsCore::DeviceHandle& deviceHandle, GraphicsCore::RenderTargetType type, const GraphicsCore::ViewPort& viewPort)
		{
			VulkanDevice& device = mDevices[deviceHandle];

			switch (type)
			{
			case DMK::GraphicsCore::RenderTargetType::SCREEN_BOUND_2D:
				break;
			case DMK::GraphicsCore::RenderTargetType::SCREEN_BOUND_3D:
			{
				RenderTargetSB3D renderTarget = RenderTargetSB3D::Create(device, viewPort);
				return GraphicsCore::RenderTargetHandle(mRenderTargetsSB3D.Insert(std::move(renderTarget)), type);
			}

			break;
			case DMK::GraphicsCore::RenderTargetType::SCREEN_BOUND_RAY_TRACING:
				break;
			case DMK::GraphicsCore::RenderTargetType::OFF_SCREEN_2D:
				break;
			case DMK::GraphicsCore::RenderTargetType::OFF_SCREEN_3D:
				break;
			case DMK::GraphicsCore::RenderTargetType::OFF_SCREEN_RAY_TRACING:
				break;
			default:
				Logger::LogError(TEXT("Undefined or invalid Render Target Type!"));
				break;
			}

			return GraphicsCore::RenderTargetHandle();
		}
	}
}