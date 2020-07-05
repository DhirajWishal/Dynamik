// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CONFIGURATION_SERVICE_H
#define _DYNAMIK_CONFIGURATION_SERVICE_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

#include <fstream>

namespace Dynamik
{
	/* SINGLETON
	 Dynamik Configuration Service
	 This object handles, manipulates and maintains the EngineConfig.ini file.
	*/
	class DMK_API DMKConfigurationService {
		DMKConfigurationService();
		~DMKConfigurationService();

		static DMKConfigurationService instance;

	public:
		enum class DMK_API Token {
			TOKEN_VERSION,
			TOKEN_WINDOW_SIZE,
		};

	public:
		DMKConfigurationService(const DMKConfigurationService&) = delete;
		DMKConfigurationService(DMKConfigurationService&&) = delete;
		DMKConfigurationService operator=(const DMKConfigurationService&) = delete;
		DMKConfigurationService operator=(DMKConfigurationService&&) = delete;

		static void openConfigFile(const STRING& path);
		static void closeConfigFile();

		static void writeMessage(const STRING& message);
		static void writeEntry(const Token& token, const STRING& message);

		static void writeWindowSize(F32 width, F32 height);

	private:
		STRING _getTokenString(Token token);

		STRING path = DMK_TEXT("");
		std::fstream* pFile = nullptr;
	};
}

#endif // !_DYNAMIK_CONFIGURATION_SERVICE_H
