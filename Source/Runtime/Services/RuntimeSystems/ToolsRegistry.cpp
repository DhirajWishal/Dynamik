// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ToolsRegistry.h"

namespace Dynamik
{
	DMKToolsRegistry DMKToolsRegistry::instance;

	void DMKToolsRegistry::setDefaultToolsBasePath(const STRING& path)
	{
		instance.defaultToolsBasePath = path;
	}

	STRING DMKToolsRegistry::getDefaultToolsBasePath()
	{
		return instance.defaultToolsBasePath;
	}
	
	void DMKToolsRegistry::initializeDefaultTools()
	{
		instance.toolMap[TEXT("GLSL_VALIDATOR_EXE")] = instance.defaultToolsBasePath + TEXT("\\glslangValidator\\glslangValidator.exe");
	}
	
	void DMKToolsRegistry::addTool(const STRING& name, const STRING& tool)
	{
		instance.toolMap[name] = tool;
	}
	
	STRING DMKToolsRegistry::getTool(const STRING& name)
	{
		if (instance.toolMap.find(name) != instance.toolMap.end())
			return instance.toolMap[name];

		DMK_ERROR("The requested tool is not resisted in the registry!");
		return STRING();
	}

	UI64 DMKToolsRegistry::getNumberOfRegisteredTools()
	{
		return instance.toolMap.size();
	}

	ARRAY<STRING> DMKToolsRegistry::getAllRegisteredToolNames()
	{
		ARRAY<STRING> names;

		for (auto asset : instance.toolMap)
			names.pushBack(asset.first);

		return names;
	}

	std::unordered_map<STRING, STRING> DMKToolsRegistry::getToolMap()
	{
		return instance.toolMap;
	}
}
