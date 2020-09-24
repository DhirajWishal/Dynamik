// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "ConfigurationService.h"

DMKConfigurationService DMKConfigurationService::instance;

DMKConfigurationService::DMKConfigurationService()
{
	pFile = StaticAllocator<std::fstream>::rawAllocate();
}

DMKConfigurationService::~DMKConfigurationService()
{
	StaticAllocator<std::fstream>::rawDeallocate(pFile);
}

void DMKConfigurationService::openConfigFile(const STRING& path)
{
	instance.path = path;
	instance.pFile->open(path);

	if (!instance.pFile->is_open())
	{
		DMK_WARN("The Engine Configuration file at location (" + path + ") does not exist. Creating a new file!");

		std::ofstream _newFile(path);
		_newFile << "VERSION: " << DMK_ENGINE_VERSION << "\n";
		_newFile.close();
	}

	instance.pFile->open(path);
}

void DMKConfigurationService::closeConfigFile()
{
	instance.pFile->close();
}

void DMKConfigurationService::writeMessage(const STRING& message)
{
	*instance.pFile << message;
}

void DMKConfigurationService::writeEntry(const Token& token, const STRING& message)
{
	writeMessage(instance._getTokenString(token) + message);
}

void DMKConfigurationService::writeWindowSize(F32 width, F32 height)
{
	writeEntry(Token::TOKEN_WINDOW_SIZE, std::to_string(width) + " " + std::to_string(height));
}

STRING DMKConfigurationService::_getTokenString(Token token)
{
	switch (token)
	{
	case DMKConfigurationService::Token::TOKEN_VERSION:
		return "VERSION: ";
	case DMKConfigurationService::Token::TOKEN_WINDOW_SIZE:
		return "WINDOW_SIZE: ";
	default:
		DMK_ERROR("Invalid Configuration Token!");
		break;
	}

	return STRING();
}
