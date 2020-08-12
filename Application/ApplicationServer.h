// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_SERVER_H
#define _APPLICATION_SERVER_H

#include "GameServer.h"
using namespace Dynamik;

class ApplicationServer final : public DMKGameServer {
public:
	ApplicationServer() {}
	~ApplicationServer() {}

	virtual void onInitializeStageOne() override final;
	virtual void onUpdate(const F32 frameTime) override final;
	virtual void onTerminate() override final;
};

#endif // !_APPLICATION_SERVER_H
