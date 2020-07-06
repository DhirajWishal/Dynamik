// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_H
#define _DYNAMIK_ANIMATION_NODE_H

#include "Core/Types/Array.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node (Anim-Node)
	 This object stores one node/ bone in an animation.
	*/
	class DMK_API DMKAnimNode {
	public:
		DMKAnimNode() {}
		~DMKAnimNode() {}

		/* Root node pointer of this node */
		DMKAnimNode* pRootNode = nullptr;

		/* Child node pointers of this node */
		ARRAY<DMKAnimNode*> pChildNodes;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_H
