// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CommandBase.h"
#include "GraphicsCore/Backend/DeviceHandle.h"
#include "GraphicsCore/Backend/RenderTargetHandle.h"
#include "GraphicsCore/Backend/PipelineHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			struct CreateGraphicsPipelineCommand : public CommandBase {
				CreateGraphicsPipelineCommand(const DeviceHandle& deviceHandle, const RenderTargetHandle& renderTargetHandle, const PipelineSpecification& spec, PipelineObjectHandle* pPipelineHandle = nullptr)
					: mDeviceHandle(deviceHandle), mRenderTargetHandle(renderTargetHandle), mSpec(spec), pPipelineHandle(pPipelineHandle), CommandBase(CommandType::CREATE_GRAPHICS_PIPELINE) {}

				PipelineSpecification mSpec = {};

				DeviceHandle mDeviceHandle = {};
				RenderTargetHandle mRenderTargetHandle = {};
				PipelineObjectHandle* pPipelineHandle = nullptr;
			};
		}
	}
}