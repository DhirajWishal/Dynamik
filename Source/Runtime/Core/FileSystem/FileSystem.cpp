// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "FileSystem.h"

#ifdef DMK_PLATFORM_WINDOWS
#include <Windows.h>  
#include <filesystem>

#endif // DMK_PLATFORM_WINDOWS


#define MAX_PATH_SIZE	256

DMKFileSystem DMKFileSystem::instance;

STRING DMKFileSystem::getExecutablePath()
{
	if (!instance.myExecutablePath.size())
	{
		CHR _path[MAX_PATH_SIZE] = { 0 };

#ifdef DMK_PLATFORM_WINDOWS
		GetModuleFileNameA(NULL, (LPSTR)_path, MAX_PATH_SIZE);

#endif // DMK_PLATFORM_WINDOWS
		return _path;
	}

	return instance.myExecutablePath;
}

STRING DMKFileSystem::getWorkingDirectory()
{
	if (!instance.myWorkingDirectory.size())
	{
		STRING path = getExecutablePath();
		instance.myWorkingDirectory = path.substr(0, path.find_last_of("\\"));
	}

	return instance.myWorkingDirectory;
}
