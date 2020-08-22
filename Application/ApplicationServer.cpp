// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "ApplicationServer.h"
#include "Assets/Modules/Module00/Module00.h"

void ApplicationServer::onInitializeStageOne()
{
	loadGameModule(StaticAllocator<Module00>::allocate());
}

void ApplicationServer::onUpdate(const F32 frameTime)
{
}

void ApplicationServer::onTerminate()
{
}

DMK_SETUP_SERVER(ApplicationServer)
