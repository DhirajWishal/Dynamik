// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "FileSystem.h"

#ifdef DMK_PLATFORM_WINDOWS
	#include <Windows.h>  
	#include <filesystem>

#endif // DMK_PLATFORM_WINDOWS


#define MAX_PATH_SIZE	256

namespace Dynamik
{
	STRING DMKFileSystem::getExecutablePath()
	{
		CHR _path[MAX_PATH_SIZE] = { 0 };

#ifdef DMK_PLATFORM_WINDOWS
		GetModuleFileNameA(NULL, (LPSTR)_path, MAX_PATH_SIZE);

#endif // DMK_PLATFORM_WINDOWS
		return _path;
	}
	
	STRING DMKFileSystem::getWorkingDirectory()
	{
		return std::filesystem::current_path().string();
	}
}