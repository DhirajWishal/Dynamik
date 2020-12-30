// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "GraphicsCore/Backend/Pipelines/RasterGraphicsPipelineSpecification.h"
#include "Core/Hash/Hasher.h"

namespace DMK
{
	namespace GraphicsCore
	{
		UI64 RasterGraphicsPipelineSpecification::Hash() const
		{
			UI64 hash = 0;
			for (auto itr = mShaders.begin(); itr != mShaders.end(); itr++)
			{
				auto codeHash = itr->Hash();
				hash = Hasher::GetHash(&codeHash, sizeof(UI64), hash);
			}

			return hash;
		}
	}
}