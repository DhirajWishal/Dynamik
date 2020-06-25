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

	DMKShaderResourceLayout DMKShaderFactory::createResourceMap(const STRING& path, const DMKShaderLocation& location)
	{
		if (path.find(".spv") == STRING::npos)
			DMK_FATAL(STRING(__FUNCSIG__) + "Function only supports SPIR-V!");

		DMKShaderModule _module;
		_module.loadCode(path);
		_module.location = location;

		Tools::SPIRVDisassembler dissassembler(_module);

		return DMKShaderResourceLayout();
	}
	
	DMKShaderModule DMKShaderFactory::createModule(const STRING& filePath, const DMKShaderLocation& location, const DMKShaderResourceLayout& resourceLayout, const DMKShaderCodeType& codeType)
	{
		DMKShaderModule _module(location, codeType);
		_module.loadCode(filePath);
		_module.setResourceLayout(resourceLayout);

		return _module;
	}
}
