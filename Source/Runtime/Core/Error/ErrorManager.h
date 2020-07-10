// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ERROR_MANAGER_H
#define _DYNAMIK_ERROR_MANAGER_H

/*
 Error manager for the Dynamik Engine.
*/

#include "../Types/DataTypes.h"
#include "MessageBox.h"

namespace Dynamik
{
	/*
	 This is a functional class that has two basic ways of flagging errors to the user.
	 * Message box.
	 * Console logging.
	*/
	class DMK_API DMKErrorManager {
	public:
		/* Issue an information box to the user */
		static UserOption issueInfoBox(STRING message);

		/* Issue a warning box to the user */
		static UserOption issueWarnBox(STRING message);

		/* Issue a question box to the user */
		static UserOption issueQuestionBox(STRING message);

		/* Issue an error box to the user */
		static UserOption issueErrorBox(STRING message);

		/* Print an information log to the console */
		static void logInfo(STRING message);

		/* Print a warning log to the console */
		static void logWarn(STRING message);

		/* Print an error log to the console */
		static void logError(STRING message);

		/* Print a fatal error to the console. This by default results in a debug breakpoint*/
		static void logFatal(STRING message, STRING file, UI32 line);

		/* Print a debug log to the console */
		static void logDebug(STRING message);
	};
}

#ifdef DMK_DEBUG
/* GLOBAL INIT LOG MACRO */

/* CLIENT LOG MACROS */
#define DMK_FATAL_FORMAT()

#define DMK_INFO(...)	::Dynamik::DMKErrorManager::logInfo(DMK_TEXT(##__VA_ARGS__))
#define DMK_WARN(...)	::Dynamik::DMKErrorManager::logWarn(DMK_TEXT(##__VA_ARGS__))
#define DMK_ERROR(...)	::Dynamik::DMKErrorManager::logError(DMK_TEXT(##__VA_ARGS__))
#define DMK_FATAL(...)	{																				\
							::Dynamik::DMKErrorManager::logFatal(DMK_TEXT(##__VA_ARGS__), __FILE__, __LINE__);	\
							__debugbreak();																\
						}

#define DMK_LOGGER(...)

// assertions
#define DMK_CORE_ASSERT(x, ...)		{										\
										if(!(x)) {							\
											 DMK_CORE_ERROR(__VA_ARGS__);	\
											 __debugbreak();				\
										}									\
									}

#define DMK_ERROR_BOX(msg)	{																				\
								::Dynamik::DMKErrorManager::issueErrorBox(DMK_TEXT(msg));					\
								__debugbreak();																\
							}																				\

#else
#define DMK_INFO(...)
#define DMK_WARN(...)
#define DMK_ERROR(...)
#define DMK_FATAL(...)

#define DMK_LOGGER(...)

/* CORE LOG MACROS */
#define DMK_CORE_INFO(...)
#define DMK_CORE_WARN(...)
#define DMK_CORE_ERROR(...)
#define DMK_CORE_FATAL(...)
#define DMK_CORE_MSG(...)

#define DMK_CORE_ASSERT(x, ...)

#define DMK_ERROR_BOX(msg)

// ----------
#endif

#endif // !_DYNAMIK_ERROR_MANAGER_H
