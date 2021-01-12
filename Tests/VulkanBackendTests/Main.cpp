// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ShaderTools/SPIR-V/Transpiler.h"
#include "VulkanBackend/VulkanInstance.h"

#include "AssetLoader/ImageLoader.h"

#include "Core/Benchmark/Timer.h"
#include "Thread/Utilities.h"

int main()
{
	auto image = DMK::AssetLoader::LoadImageData("E:\\Dynamik\\Version\\DynamikEngine\\Assets\\Textures\\SkyBox\\back.jpg");

	DMK::VulkanBackend::VulkanInstance instance = {};

#ifdef DMK_DEBUG
	instance.Initialize(true);

#else
	instance.Initialize(false);

#endif // DMK_DEBUG

	auto pDisplay = instance.CreateDisplay(1280, 720, "Dynamik Engine: Vulkan Tests");
	auto pDevice = pDisplay->CreateDevice();

	DMK::Thread::Utilities::Sleep(GET_NANOSECONDS_FROM_SECONDS(10));

	pDisplay->DestroyDevice(pDevice);
	instance.DestroyDisplay(pDisplay);
	instance.Terminate();
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
 *
 * //////////////////////////////////////////////////////////////////////////////////////////////////
 * //////////////////////////////////////////////////////////////////////////////////////////////////
 *
 * DisplayHandle mDisplay = GraphicsEngine()->CreateDisplay(GetDefaultDisplaySpec());
 * DeviceHandle mDevice = GraphicsEngine()->CreateDevice(mDisplay);
 * RenderTargetHandle mRenderTarget = GraphicsEngine()->CreateRenderTarget(mDevice, RenderTargetType::SCREEN_BOUND_3D, GetDefaultViewPort());
 *
 * PipelineHandle mPipeline = GraphicsEngine()->CreatePipeline(mRenderTarget, GetDefaultShaders(), GetDefaultPipelineSpec());
 *
 * BufferHandle mVBuffer = GraphicsEngine()->CreateBuffer(mDevice, GetVertexSize(), nullptr);
 * BufferHandle mIBuffer = GraphicsEngine()->CreateBuffer(mDevice, GetIndexSize(), nullptr);
 *
 * MaterialHandle mMaterial = GraphicsEngine()->CreateImage(mDevice, GetTexture());
 *
 * GraphicsEngine()->AddToRenderList(mPipeline, { mVBuffer, mIBuffer }, { mMaterial });
 * 
 * GraphicsEngine()->Execute(mRenderTarget);
 * 
 * // OR
 * 
 * GraphcisEngine()->ExecuteAsync(mRenderTarget);
 * 
 * GraphicsEngine()->DestroyPipeline(mPipeline);
 * GraphicsEngine()->DestroyRenderTarget(mRenderTarget);
 * GraphicsEngine()->DestroyVertexBuffer(mVBuffer);
 * GraphicsEngine()->DestroyIndexBuffer(mIBuffer);
 * GraphicsEngine()->DestroyImage(mMaterial);
 * GraphicsEngine()->DestroyDevice(mDevice);
 * GraphicsEngine()->DestroyDisplay(mDisplay);
 */