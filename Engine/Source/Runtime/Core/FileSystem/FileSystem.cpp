#include "dmkafx.h"
#include "FileSystem.h"

#ifdef DMK_PLATFORM_WINDOWS
	#include <Windows.h>  

#endif // DMK_PLATFORM_WINDOWS


#define MAX_PATH_SIZE	256

namespace Dynamik
{
	DMK_CLASS_SINGLETON_IMPL(DMKFileSystem);

	STRING DMKFileSystem::getExecutablePath()
	{
		CHR _path[MAX_PATH_SIZE] = { 0 };

#ifdef DMK_PLATFORM_WINDOWS
		GetModuleFileNameA(NULL, (LPSTR)_path, MAX_PATH_SIZE);

#endif // DMK_PLATFORM_WINDOWS

		return _path;
	}
}