#include "dmkafx.h"
#include "AssemblerSPIRV.h"

#include <spirv-tools/libspirv.hpp>
#include <spirv-tools/optimizer.hpp>

namespace Dynamik
{
	namespace Tools
	{
		ARRAY<CHR> AssemblerSPIRV::getCodeSPIRV(const STRING& glslCode)
		{
			spvtools::SpirvTools core(SPV_ENV_UNIVERSAL_1_3);
			spvtools::Optimizer opt(SPV_ENV_UNIVERSAL_1_3);

			return ARRAY<CHR>();
		}
	}
}
