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
