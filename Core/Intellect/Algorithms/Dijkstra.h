// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <vector>

namespace DMK
{
	namespace Intellect
	{
		/**
		 * Dijkstra search algorithm.
		 * This algorithm is used by the other structures to fins the shortest path to a specific destination.
		 *
		 * @tparam Node: The node type.
		 * @tparam Edge: The edge type.
		 */
		template<class Node, class Edge>
		class Dijkstra {
		public:
			Dijkstra() {}
			~Dijkstra() {}

			/**
			 * Search operator.
			 * This operator searchs the nodes and returns the list of nodes to travel.
			 */
			std::vector<Node> operator()(const std::vector<Node>& mNodes)
			{

			}
		};
	}
}