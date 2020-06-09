#include "dmkafx.h"
#include "SPIRVTools.h"

#include <spirv_glsl.hpp>
#include <spirv_cross.hpp>
#include <spirv-tools/libspirv.h>

namespace Dynamik
{
	namespace Tools
	{
		ARRAY<CHR> SPIRVTools::compileGLSL(const STRING& code)
		{
			return ARRAY<CHR>();
		}
		
		STRING SPIRVTools::toGLSL(ARRAY<UI32> code)
		{
			spirv_cross::CompilerGLSL _compiler(std::move(code.toVector()));
			return _compiler.compile();
		}
	}
}
