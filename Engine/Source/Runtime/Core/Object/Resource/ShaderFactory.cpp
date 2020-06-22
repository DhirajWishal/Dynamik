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

	DMKShaderResourceMap DMKShaderFactory::createResourceMap(const STRING& path, const DMKShaderLocation& location)
	{
		if (path.find(".spv") == STRING::npos)
			DMK_FATAL(STRING(__FUNCSIG__) + "Function only supports SPIR-V!");

		DMKShaderModule _module;
		_module.loadCode(path);
		_module.location = location;

		Tools::SPIRVDisassembler dissassembler(_module);

		return DMKShaderResourceMap();
	}
	
	DMKShaderModule DMKShaderFactory::createModule(const STRING& filePath, const DMKShaderLocation& location, const DMKShaderResourceMap& resourceMap, const DMKShaderCodeType& codeType)
	{
		DMKShaderModule _module(location, codeType);
		_module.loadCode(filePath);
		_module.setResourceMap(resourceMap);

		return _module;
	}
}
