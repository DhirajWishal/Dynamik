// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/VulkanBackendAdapter.h"
#include "ShaderTools/SPIR-V/Transpiler.h"

#include "Core/Benchmark/Timer.h"
#include "Thread/Utilities.h"

int main()
{
	DMK::VulkanBackend::VulkanBackendAdapter adapter = {};

	DMK::GraphicsCore::DisplayHandle displayID = 0;
	DMK::GraphicsCore::DeviceHandle deviceID = 0;
	DMK::GraphicsCore::RenderTargetHandle renderTargetHandle;


	{
		DMK::Benchmark::Timer timer;
#ifdef DMK_DEBUG
		adapter.Initialize(true);

#else
		adapter.Initialize(false);

#endif // DMK_DEBUG

		displayID = adapter.CreateDisplay(1280, 720, "Dynamik Engine: Vulkan Backend Tests");
		deviceID = adapter.CreateDevice(displayID);
		renderTargetHandle = adapter.CreateRenderTarget(deviceID, DMK::GraphicsCore::RenderTargetType::SCREEN_BOUND_3D, DMK::GraphicsCore::ViewPort(deviceID, 1280, 720));
	}

	DMK::Thread::Utilities::Sleep(5000000);

	{
		DMK::Benchmark::Timer timer;
		adapter.DestroyDevice(deviceID);
		adapter.DestroyDisplay(displayID);
		adapter.Terminate();
	}
}


/**
 * auto pDevice = GetGraphicsEngine()->CreateNewDevice(DefaultWindowData());
 * 
 * // Create the render target with the buffer count of 1.
 * auto pRenderTarget = pDevice->CreateRenderTarget(RenderTargetType::OFF_SCREEN_3D, GetDefaultExtent(), 1);
 * 
 * auto pPipeline = pRenderTarget->CreateRasterPipeline({ GetVertexShader(), GetFragmentShader() }, GetDefaultRasterPipelineSpec());
 * 
 * auto pVertexBuffer = pDevice->CreateVertexBuffer(GetVertexBufferObject());
 * auto pIndexBuffer = pDevice->CreateIndexBuffer(GetIndexBufferObject());
 * auto pTexture = pDevice->CreateImage(ImageType::2D, GetDefaultTexture());
 * 
 * pRenderTarget->AddToRenderList({ pVertexBuffer, pIndexBuffer }, { pTexture }, pPipeline);
 * 
 * // OR
 * 
 * pRenderTarget->AddCustomRenderCommand(
 *		[=](CommandBuffer* pCommandBuffer, RenderResource* pRenderResource)
 *		{
 *			pCommandBuffer->BindPipeline(pRenderResource->GetPipeline());
 *			pCommandBuffer->BindVertexBuffer(pRenderResource->GetVertexBuffer());
 *			pCommandBuffer->DrawIndexed(pRenderResource->GetIndexBuffer());
 *		}
 * );
 * 
 * GetGraphicsEngine()->Execute(pRenderTarget); 
 * 
 * auto pTexture = pRenderTarget->GetRenderAsImage();
 * 
 * pDevice->DestroyRenderTarget(pRenderTarget);
 * pDevice->DestroyVertexBuffer(pVertexBuffer);
 * pDevice->DestroyIndexBuffer(pIndexBuffer);
 * pDevice->DestroyImage(pTexture);
 */