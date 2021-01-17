// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Maths/Vector/Vector2.h"
#include "Core/Maths/Vector/Vector3.h"

namespace DMK
{
	namespace Intellect
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		////	Navigation Mesh 2D
		///////////////////////////////////////////////////////////////////////////////////////////////////

		struct NavMeshNode2D;

		/**
		 * Navigation Node Link 2D structure.
		 * This is used as an edge in between 2 2D navigation nodes.
		 */
		struct NavMeshNodeLink2D {
			NavMeshNode2D* pNext = nullptr;	// The next node.
			UI64 mWeight = 0;	// The weight of the link.
		};

		/**
		 * Navigation Mesh Node 2D structure.
		 * These structures are vertices in the navigation mesh.
		 */
		struct NavMeshNode2D {
			typedef NavMeshNodeLink2D EdgeType;	// The edge type of the node.

			std::vector<EdgeType> mLinks;	// The other linked nodes.
			Vector2 mLocation = Vector2::ZeroAll;	// The location of the node.
		};

		///////////////////////////////////////////////////////////////////////////////////////////////////
		////	Navigation Mesh 3D
		///////////////////////////////////////////////////////////////////////////////////////////////////

		struct NavMeshNode3D;

		/**
		 * Navigation Node Link 3D structure.
		 * This is used as an edge in between 2 3D navigation nodes.
		 */
		struct NavMeshNodeLink3D {
			NavMeshNode2D* pNext = nullptr;	// The next node.
			UI64 mWeight = 0;	// The weight of the link.
		};

		/**
		 * Navigation Mesh Node 3D structure.
		 * These structures are vertices in the navigation mesh.
		 */
		struct NavMeshNode3D {
			typedef NavMeshNodeLink3D EdgeType;	// The edge type of the node.

			std::vector<EdgeType> mLinks;	// The other linked nodes.
			Vector3 mLocation = Vector3::ZeroAll;	// The location of the node.
		};
	}
}