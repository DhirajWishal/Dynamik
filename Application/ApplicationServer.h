// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_SERVER_H
#define _APPLICATION_SERVER_H

#include "GameServer.h"

class ApplicationServer final : public DMKGameServer {
public:
	ApplicationServer() {}
	~ApplicationServer() {}

protected:
	void onInitializeSystems() override final;
	void onInitializeServices() override final;
	void onInitializeGame() override final;
	void onInitializeFinal() override final;

	void onBeginUpdate() override final;
	void onUpdateGame() override final;
	void onUpdateSystems() override final;
	void onEndUpdate() override final;

	void onTerminateGame() override final;
	void onTerminateSystems() override final;
	void onTerminateServices() override final;
	void onTerminateFinal() override final;
};

#endif // !_APPLICATION_SERVER_H
