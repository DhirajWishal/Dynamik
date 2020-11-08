// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Common/GDevice.h"

namespace DMK
{
	namespace GraphicsCore
	{
		ShaderModule GDevice::CreateShaderModule(const wchar_t* pAsset, ShaderLocation location)
		{
			ShaderModule sModule = {};
			sModule.InitializeShaderModule;

			return sModule;
		}
	}
}