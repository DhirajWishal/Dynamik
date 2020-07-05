// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_FILE_SYSTEM_H
#define _DYNAMIK_FILE_SYSTEM_H

#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/*
	 File System based functions for the Dynamik Engine
	*/
	class DMK_API DMKFileSystem {
		DMKFileSystem() = default;
		~DMKFileSystem() = default;

		static DMKFileSystem instance;

	public:
		DMKFileSystem(const DMKFileSystem&) = delete;
		DMKFileSystem(DMKFileSystem&&) = delete;
		DMKFileSystem& operator=(const DMKFileSystem&) = delete;
		DMKFileSystem& operator=(DMKFileSystem&&) = delete;

	public:
		/* Get the path of the executable */
		static STRING getExecutablePath();

		/* Get the current working directory */
		static STRING getWorkingDirectory();

	private:
		STRING myExecutablePath = DMK_TEXT("");
		STRING myWorkingDirectory = DMK_TEXT("");
	};
}

#endif // !_DYNAMIK_FILE_SYSTEM_H
