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
	
	DMKShaderModule DMKShaderFactory::createAnimated(const DMKShaderLocation& location)
	{
		switch (location)
		{
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX:
			return createModule(instance.myWorkingDir + "/Runtime/Shaders/SkeletalAnimation/vert.spv", location, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
		
		case Dynamik::DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT:
			return createModule(instance.myWorkingDir + "/Runtime/Shaders/SkeletalAnimation/frag.spv", location, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV);
		
		default:
			DMK_FATAL("This function only accepts Vertex and Fragment shader location arguments!");
			break;
		}

		return DMKShaderModule();
	}
}
