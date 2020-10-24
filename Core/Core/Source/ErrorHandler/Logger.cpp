// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/ErrorHandler/Logger.h"

#include <iostream>
#include <vector>
#include <time.h>

namespace DMK
{
	namespace Logger
	{
		const CHR blue[8] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };		// core info
		const CHR green[8] = { 0x1b, '[', '1', ';', '9', '2', 'm', 0 };		// info
		const CHR yellow[8] = { 0x1b, '[', '1', ';', '9', '3', 'm', 0 };	// warning
		const CHR errRed[8] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 };	// error
		const CHR fatalRed[8] = { 0x1b, '[', '4', ';', '3', '1', 'm', 0 };	// fatal
		const CHR normal[8] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };	// default

		void changeToColor(int severity) {
			switch (severity) {
			case 0:
				std::wcout << green;
				break;
			case 1:
				std::wcout << yellow;
				break;
			case 2:
				std::wcout << errRed;
				break;
			case 3:
				std::wcout << errRed << fatalRed; break;
			case 4:
				std::wcout << blue; break;
			default:
				break;
			}
		}

		std::vector<String> LOG_INFO = {
			TEXT("INFO-> "),
			TEXT("WARN-> "),
			TEXT("ERROR-> "),
			TEXT("FATAL-> "),
			TEXT("DEBUG-> "),
		};

		/**
		 * Log information to the console by submitting a color.
		 *
		* @param severity: Message priority.
		* @param msg: The actual message to be logged.
		 */
		void LOG(int severity, String msg) {
			CHR tmpBuff[128];
			_tzset();

			changeToColor(severity);

			_strtime_s(tmpBuff, 128);
			printf(TEXT("[%s] %s%s%s\n"), tmpBuff, LOG_INFO[severity].c_str(), msg.c_str(), normal);
		}

		void LogInfo(String message)
		{
			changeToColor(0);
			LOG(0, message);
		}

		void LogWarn(String message)
		{
			changeToColor(1);
			LOG(1, message);
		}

		void LogError(String message)
		{
			changeToColor(2);
			LOG(2, message);
		}

		void LogFatal(String message, String file, UI32 line)
		{
			changeToColor(3);
			printf(TEXT("[%s:%u] %s%s%s\n"), file.c_str(), line, LOG_INFO[3].c_str(), message.c_str(), normal);
		}

		void LogDebug(String message)
		{
			changeToColor(4);
			LOG(4, message);
		}
	}
}