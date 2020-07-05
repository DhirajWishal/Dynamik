// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_PACKAGE_H
#define _APPLICATION_PACKAGE_H

#include "GameLibrary/GamePackage.h"
#include "Assets/Level1/Level1.h"
using namespace Dynamik;

class ApplicationPackage : public DMKGamePackage {
public:
	ApplicationPackage();
	~ApplicationPackage() {}

	virtual void onLoad() override final;
	virtual void onInit() override final;
	virtual void onLevelLoad(UI64 levelIndex) override final;

private:
	Level1 myFirstLevel;
};

#endif // !_APPLICATION_PACKAGE_H
