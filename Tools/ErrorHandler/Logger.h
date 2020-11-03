// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ERROR_HANDLER_LOGGER_H
#define _DYNAMIK_ERROR_HANDLER_LOGGER_H

#include <string>

#ifdef DMK_USE_WIDE_CHAR
#define TEXT(text)  Ltext# 
typedef std::wstring STRING;
typedef wchar_t CHR;				// wide char (UTF-8)

#else
#define TEXT(text)  text
typedef std::string STRING;
typedef char CHR;					// char (ASCII)

#endif // DMK_USE_WIDE_CHR

using UI32 = unsigned __int32;

namespace DMK
{
	namespace ErrorHandler
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
			void LogInfo(STRING message);

			/**
			 * Log a warning message to the console. 
			 * Color: Yellow. 
			 * 
			 * @param message: The message to be logged. 
			 */
			void LogWarn(STRING message);

			/**
			 * Log an error message to the console. 
			 * Color: Red.
			 * 
			 * @param message: The message to be logged. 
			 */
			void LogError(STRING message);

			/**
			 * Log a fatal error message to the console. 
			 * Color: Red + underlined.
			 * 
			 * @param message: The message to be logged. 
			 * @param file: The file the error had occurred.
			 * @param line: The line of the error.
			 */
			void LogFatal(STRING message, STRING file, UI32 line);

			/**
			 * Log a debug information to the console. 
			 * Color: Blue. 
			 * 
			 * @param message: The message to be logged. 
			 */
			void LogDebug(STRING message);
		}
	}
}

#endif // !_DYNAMIK_ERROR_HANDLER_LOGGER_H
