#include "dmkafx.h"
#include "ShaderFactory.h"

#include "Tools/Shader/SPIR-V/Disassembler.h"

namespace Dynamik
{
	DMKShaderFactory DMKShaderFactory::instance;

	void DMKShaderFactory::setWorkingDirectory(const STRING& path)
	{
		instance.myWorkingDir = path;
	}
	
	DMKShaderModule DMKShaderFactory::createModule(const STRING& filePath, const DMKShaderLocation& location, const DMKShaderCodeType& codeType)
	{
		DMKShaderModule _module(location, codeType);
		_module.loadCode(filePath);

		return _module;
	}
}
