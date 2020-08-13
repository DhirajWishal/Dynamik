// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationServer.h"

#include "Assets/Level1/Level1.h"

void ApplicationServer::onInitializeStageOne()
{
	loadGameModule(new Level1);
}

void ApplicationServer::onUpdate(const F32 frameTime)
{
}

void ApplicationServer::onTerminate()
{
}

DMK_SETUP_SERVER(ApplicationServer)
