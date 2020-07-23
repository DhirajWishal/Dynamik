// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_HOLLOW_ENTITY_H
#define _DYNAMIK_HOLLOW_ENTITY_H

#include "../GameEntity.h"

namespace Dynamik
{
	/*
	 Dynamik Hollow Entity
	 This class is a default object which the user can use to import basic data.
	*/
	class DMK_API DMKHollowEntity : public DMKGameEntity {
	public:
		DMKHollowEntity() {}
		virtual ~DMKHollowEntity() {}

		virtual void initialize() override;

		void setAssetPath(const STRING& path);
		STRING assetPath = TEXT("");
	};
}

#endif // !_DYNAMIK_HOLLOW_ENTITY_H
