#pragma once
#ifndef _DYNAMIK_SPIRV_TOOLS_H
#define _DYNAMIK_SPIRV_TOOLS_H

/*
 Author:	Dhiraj Wishal
 Date:		09/06/2020
*/
#include "Types/Array.h"

namespace Dynamik
{
	namespace Tools {
		class DMK_API SPIRVTools {
		public:
			SPIRVTools() {}
			~SPIRVTools() {}

			ARRAY<CHR> compileGLSL(const STRING& code);
			STRING toGLSL(ARRAY<UI32> code);
		};
	}
}

#endif // !_DYNAMIK_SPIRV_TOOLS_H
