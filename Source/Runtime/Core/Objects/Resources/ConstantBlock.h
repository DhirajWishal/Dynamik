// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CONSTANT_BLOCK_H
#define _DYNAMIK_CONSTANT_BLOCK_H

#include "UniformBuffer.h"

namespace Dynamik
{
	/* Dynamik Constant Attribute */
	struct DMK_API DMKConstantAttribute {
		DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_F32;
		UI64 dataCount = 1;
	};

	/* Dynamik Constant Block Descriptor */
	struct DMK_API DMKConstantBlockDescription {
		ARRAY<DMKConstantAttribute> attributes;
		DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		UI32 offset = 0;

		/* Block size */
		UI64 getBlockSize();
	};
}

#endif // !_DYNAMIK_CONSTANT_BLOCK_H
