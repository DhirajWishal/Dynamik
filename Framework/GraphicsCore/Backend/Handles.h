// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/Handle.h"

/**
 * In some handles, there will be *SB* and *OS* at the end. These are named as following,
 * - Screen Bound 2D (SB2D)
 * - Screen Bound 3D (SB3D)
 * - Screen Bound Ray Traced (SBRT)
 * - Off Screen 2D (OS2D)
 * - Off Screen 3D (OS3D)
 * - Off Screen Ray Traced (OSRT)
 */

namespace DMK
{
	namespace GraphicsCore
	{
		DMK_DEFINE_UI64_HANDLE(DisplayHandle);
		DMK_DEFINE_UI64_HANDLE(DeviceHandle);

		DMK_DEFINE_UI64_HANDLE(CommandBuffer);
		DMK_DEFINE_UI64_HANDLE(CommandBufferChild);

		DMK_DEFINE_UI64_HANDLE(VertexBuffer);
		DMK_DEFINE_UI64_HANDLE(IndexBuffer);
		DMK_DEFINE_UI64_HANDLE(UniformBuffer);
		DMK_DEFINE_UI64_HANDLE(StorageBuffer);
		DMK_DEFINE_UI64_HANDLE(StaggingBuffer);
		DMK_DEFINE_UI64_HANDLE(AccellerationBuffer);
		DMK_DEFINE_UI64_HANDLE(TopLevelScratchBuffer);
		DMK_DEFINE_UI64_HANDLE(BottomLevelScratchBuffer);

		DMK_DEFINE_UI64_HANDLE(Image2D);
		DMK_DEFINE_UI64_HANDLE(Image3D);
		DMK_DEFINE_UI64_HANDLE(ImageCubeMap);

		DMK_DEFINE_UI64_HANDLE(StorageImage2D);
		DMK_DEFINE_UI64_HANDLE(StorageImage3D);
		DMK_DEFINE_UI64_HANDLE(StorageImageCubeMap);

		DMK_DEFINE_UI64_HANDLE(GraphicsPipeline);
		DMK_DEFINE_UI64_HANDLE(RayTracingPipeline);
		DMK_DEFINE_UI64_HANDLE(ComputePipeline);

		DMK_DEFINE_UI64_HANDLE(RenderTargetSB2D);
		DMK_DEFINE_UI64_HANDLE(RenderTargetSB3D);
		DMK_DEFINE_UI64_HANDLE(RenderTargetSBRT);

		DMK_DEFINE_UI64_HANDLE(RenderTargetOS2D);
		DMK_DEFINE_UI64_HANDLE(RenderTargetOS3D);
		DMK_DEFINE_UI64_HANDLE(RenderTargetOSRT);
	}
}