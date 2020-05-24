#pragma once
#ifndef _DYNAMIK_ERROR_MANAGER_H
#define _DYNAMIK_ERROR_MANAGER_H

/*
 Error manager for the Dynamik Engine.

 Author:	Dhiraj Wishal
 Date:		15/05/2020
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
		static UserOption issueInfoBox(STRING message);
		static UserOption issueWarnBox(STRING message);
		static UserOption issueQuestionBox(STRING message);
		static UserOption issueErrorBox(STRING message);

		static void logInfo(STRING message);
		static void logWarn(STRING message);
		static void logError(STRING message);
		static void logFatal(STRING message, STRING file, UI32 line);
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

// ----------
#endif

#endif // !_DYNAMIK_ERROR_MANAGER_H
