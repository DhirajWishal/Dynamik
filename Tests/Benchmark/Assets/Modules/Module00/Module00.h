// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_MODULE_00_H
#define _APPLICATION_MODULE_00_H

#include "GameLibrary/GameModule.h"

class Module00 final : public DMKGameModule {
public:
	Module00() {}
	~Module00() {}

	virtual void onInitialize() override final;
};

#endif // !_APPLICATION_MODULE_00_H
