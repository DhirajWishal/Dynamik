// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_TREE_H
#define _APPLICATION_TREE_H

#include "GameLibrary/GameEntity.h"
using namespace Dynamik;

class Tree : public DMKGameEntity {
public:
	Tree() {}
	~Tree() {}

	virtual void initialize() override final;
	virtual void onUpdate(F32 timeStep) override final;

	struct Uniform {
		Matrix4F Model = Matrix4F::Identity;
		Matrix4F View = Matrix4F::Identity;
		Matrix4F Projection = Matrix4F::Identity;
	} uniformMVP;
};

#endif // !_APPLICATION_TREE_H

