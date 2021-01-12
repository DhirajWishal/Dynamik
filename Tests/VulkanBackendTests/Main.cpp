// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include <iostream>

#include "ShaderTools/SPIR-V/Transpiler.h"
#include "VulkanBackend/VulkanBackendAdapter.h"

#include "AssetLoader/ImageLoader.h"

#include "Core/Benchmark/Timer.h"
#include "Thread/Utilities.h"

#define ITERATIONS	100

void TestHandles()
{
	DMK::Benchmark::Timer t;
	DMK::GraphicsCore::BackendAdapter* pAdapter = new DMK::VulkanBackend::VulkanBackendAdapter();

#ifdef DMK_DEBUG
	pAdapter->Initialize(true);

#else
	pAdapter->Initialize(false);

#endif // DMK_DEBUG

	auto display = pAdapter->CreateDisplay(1280, 720, "Dynamik Engine: Vulkan Tests");

	for (UI32 i = 0; i < ITERATIONS; i++)
	{
		auto device = pAdapter->CreateDevice(display);

		DMK::Thread::Utilities::Sleep((10));

		pAdapter->DestroyDevice(device);
	}

	pAdapter->DestroyDisplay(display);
	pAdapter->Terminate();

	delete pAdapter;
}

void TestInheritance()
{
	DMK::Benchmark::Timer t;
	DMK::GraphicsCore::Instance* pInstance = new DMK::VulkanBackend::VulkanInstance();

#ifdef DMK_DEBUG
	pInstance->Initialize(true);

#else
	pInstance->Initialize(false);

#endif // DMK_DEBUG

	DMK::GraphicsCore::Display* pDisplay = new DMK::VulkanBackend::VulkanDisplay();
	pDisplay->Initialize(pInstance, 1280, 720, "Dynamik Engine: Vulkan Tests");

	for (UI32 i = 0; i < ITERATIONS; i++)
	{
		DMK::GraphicsCore::Device* pDevice = new DMK::VulkanBackend::VulkanDevice();
		pDevice->Initialize(pDisplay);

		DMK::Thread::Utilities::Sleep((10));

		pDevice->Terminate();
		delete pDevice;
	}

	pDisplay->Terminate();
	delete pDisplay;

	pInstance->Terminate();
	delete pInstance;
}

int main()
{
	//auto image = DMK::AssetLoader::LoadImageData("E:\\Dynamik\\Version\\DynamikEngine\\Assets\\Textures\\SkyBox\\back.jpg");

	for (UI32 i = 0; i < 10; i++)
		TestInheritance();

	std::cout << "\n";
	DMK::Thread::Utilities::Sleep(GET_MICROSECONDS_FROM_SECONDS(1));

	for (UI32 i = 0; i < 10; i++)
		TestHandles();
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


/*
Time taken: 954 (microseconds)
Time taken: 952 (microseconds)
Time taken: 948 (microseconds)
Time taken: 959 (microseconds)
Time taken: 984 (microseconds)
Time taken: 987 (microseconds)
Time taken: 973 (microseconds)
Time taken: 980 (microseconds)
Time taken: 971 (microseconds)
Time taken: 966 (microseconds)

Time taken: 961 (microseconds)
Time taken: 954 (microseconds)
Time taken: 961 (microseconds)
Time taken: 965 (microseconds)
Time taken: 962 (microseconds)
Time taken: 953 (microseconds)
Time taken: 954 (microseconds)
Time taken: 953 (microseconds)
Time taken: 956 (microseconds)
Time taken: 958 (microseconds)
*/