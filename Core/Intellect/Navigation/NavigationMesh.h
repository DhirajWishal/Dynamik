// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "NavMeshNode.h"
#include "Intellect/Algorithms/Dijkstra.h"

#include <type_traits>

namespace DMK
{
	namespace Intellect
	{
		/**
		 * Navigation Mesh object.
		 * This object is used for navigation.
		 *
		 * @tparam Node: The type of the node (2D or 3D). Default is NavMeshNode2D.
		 * @tparam SearchAlgorithm: The algorithm to be used for searching. Default is Dijkstra.
		 */
		template<class Node = DMK::Intellect::NavMeshNode2D, class SearchAlgorithm = DMK::Intellect::Dijkstra<Node, Node::EdgeType>>
		class NavigationMesh {
			using Edge = Node::EdgeType;

			// Check if the node type is valid.
			static_assert(
				std::is_same<Node, DMK::Intellect::NavMeshNode2D>::value || std::is_same<Node, DMK::Intellect::NavMeshNode3D>::value,
				"Invalid Node type! The navigation mesh requires the node type to be either DMK::Intellect::NavMeshNode2D or DMK::Intellect::NavMeshNode3D.");

			// Check if the search algorithm is valid.
			static_assert(
				std::is_same<SearchAlgorithm, DMK::Intellect::Dijkstra<Node, Edge>>::value,
				"Invalid Search Algorithrm! The navigation mesh requires the search algorithm to be one of,  DMK::Intellect::Dijkstra.");

		public:
			NavigationMesh() {}
			~NavigationMesh() {}

			void AddNode(const Node& node)
			{
				mNodes.insert(mNodes.end(), node);
			}

		private:
			std::vector<Node> mNodes;	// The nodes in the mesh.
		};
	}
}