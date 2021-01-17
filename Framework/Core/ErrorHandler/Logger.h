// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"

namespace DMK
{
	/**
	 *  The logger is a namespace which contains functions which allows the user to log messages to the console.
	 */
	namespace Logger
	{
		/**
		 * Log basic information to the console.
		 * Color: Green.
		 *
		* @param message: The message to be logged.
		 */
		void LogInfo(const wchar* message);

		/**
		 * Log a warning message to the console.
		 * Color: Yellow.
		 *
		* @param message: The message to be logged.
		 */
		void LogWarn(const wchar* message);

		/**
		 * Log an error message to the console.
		 * Color: Red.
		 *
		* @param message: The message to be logged.
		 */
		void LogError(const wchar* message);

		/**
		 * Log a fatal error message to the console.
		 * Color: Red + underlined.
		 *
		* @param message: The message to be logged.
		* @param file: The file the error had occurred.
		* @param line: The line of the error.
		 */
		void LogFatal(const wchar* message, const wchar* file, UI32 line);

		/**
		 * Log a debug information to the console.
		 * Color: Blue.
		 *
		* @param message: The message to be logged.
		 */
		void LogDebug(const wchar* message);
	}
}

#ifdef DMK_DEBUG

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)

#define DMK_LOG_INFO(...)		::DMK::Logger::LogInfo(__VA_ARGS__)
#define DMK_LOG_DEBUG(...)		::DMK::Logger::LogDebug(__VA_ARGS__)
#define DMK_LOG_WARN(...)		::DMK::Logger::LogWarn(__VA_ARGS__)
#define DMK_LOG_ERROR(...)		::DMK::Logger::LogError(__VA_ARGS__)
#define DMK_LOG_FATAL(...)		::DMK::Logger::LogFatal(__VA_ARGS__, WIDE1(__FILE__), __LINE__), __debugbreak()

#define DMK_ASSERT(exp, ...)	if(exp != true)	DMK_LOG_FATAL(__VA_ARGS__)

#else

#define DMK_LOG_INFO(...)
#define DMK_LOG_DEBUG(...)
#define DMK_LOG_WARN(...)
#define DMK_LOG_ERROR(...)
#define DMK_LOG_FATAL(...)

#define DMK_ASSERT(exp, ...)	//

#endif // DMK_DEBUG

