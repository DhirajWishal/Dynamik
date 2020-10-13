// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "AnimNodeGraph.h"

void DMKAnimNodeGraph::addNode(const DMKAnimNode& node)
{
	nodes.push_back(node);
}

DMKAnimNode DMKAnimNodeGraph::getNode(const STRING& name)
{
	for (auto node : nodes)
		if (node.name == name)
			return node;

	return DMKAnimNode();
}

UI64 DMKAnimNodeGraph::getNodeIndex(const STRING& name)
{
	for (UI64 index = 0; index < nodes.size(); index++)
		if (nodes[index].name == name)
			return index;

	return UI64();
}
