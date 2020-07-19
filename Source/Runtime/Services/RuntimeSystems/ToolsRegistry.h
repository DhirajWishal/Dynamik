// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TOOLS_REGISTRY_H
#define _DYNAMIK_TOOLS_REGISTRY_H

#include "Core/FileSystem/FileSystem.h"

namespace Dynamik
{
	/*
	 Dynamik Tools Registry
	 This singleton stores information about external tools used by the engine.

	 The default registry path is:
	     $(SolutionDir)Dependencies/ThirdParty/Binaries/
	*/
	class DMKToolsRegistry {
		DMKToolsRegistry() {}
		~DMKToolsRegistry() {}

		static DMKToolsRegistry instance;
	public:
		DMKToolsRegistry(const DMKToolsRegistry&) = delete;
		DMKToolsRegistry(DMKToolsRegistry&&) = delete;
		DMKToolsRegistry& operator=(const DMKToolsRegistry&) = delete;
		DMKToolsRegistry& operator=(DMKToolsRegistry&&) = delete;

		/*
		 This function is handled by the engine!
		 Set the default tools path. These files are provided by the engine and are used by the engine 
		 runtime.

		 @param path: The default path.
		*/
		static void setDefaultToolsBasePath(const STRING& path);

		/*
		 Get the default tools path.
		*/
		static STRING getDefaultToolsBasePath();

		/*
		 Initialize the default tools.
		*/
		static void initializeDefaultTools();

		/*
		 Add a tool to the registry.

		 @param name: The name of the tool.
		 @param tool: The path to the tool.
		*/
		static void addTool(const STRING& name, const STRING& tool);

		/*
		 Get a tool which is registered in the registry.

		 @param name: The name of the tool.
		*/
		static STRING getTool(const STRING& name);

		/*
		 Get the total number of registered tools.
		*/
		static UI64 getNumberOfRegisteredTools();

		/*
		 Get all the registered tool names.
		*/
		static ARRAY<STRING> getAllRegisteredToolNames();

		/*
		 Get the tool map of the registry.
		*/
		static std::unordered_map<STRING, STRING> getToolMap();

	private:
		std::unordered_map<STRING, STRING> toolMap;
		STRING defaultToolsBasePath = TEXT("");
	};
}

#endif // !_DYNAMIK_TOOLS_REGISTRY_H
