// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_GRAPH_H
#define _DYNAMIK_ANIMATION_NODE_GRAPH_H

#include "AnimNode.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node Graph
	 This object stores all the nodes/ bones of a skeletal mesh.

	 All nodes are stored in an array and parent-child relationship is based on array location pointers.
	*/
	class DMK_API DMKAnimNodeGraph {
	public:
		DMKAnimNodeGraph() {}
		~DMKAnimNodeGraph() {}

		/*
		 Add a node to the store.
		*/
		void addNode(const DMKAnimNode& node);

		/*
		 Get a node using its name.
		*/
		DMKAnimNode getNode(const STRING& name);

		/*
		 Get the node index of a given node.
		*/
		UI64 getNodeIndex(const STRING& name);

		/* Node store */
		ARRAY<DMKAnimNode> nodes;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_GRAPH_H
