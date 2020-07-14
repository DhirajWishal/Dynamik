// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_H
#define _DYNAMIK_ANIMATION_NODE_H

#include "Core/Types/Array.h"
#include "Core/Math/Matrix/Matrix4F.h"

namespace Dynamik
{
	/*
	 Dynamik Animation Node (Anim-Node)
	 This object stores one node/ bone in an animation.

	 offsetMatrix: The offset matrix of the current node.
	 nodeMatrix: The matrix of this node in relation to the parent.
	 worldTransform: The matrix of this node in relation to the world.
	*/
	class DMK_API DMKAnimNode {
	public:
		DMKAnimNode() {}
		DMKAnimNode(UI32 parentIndex, STRING name, Matrix4F nodeMatrix)
			: parentIndex(parentIndex), name(name), nodeMatrix(nodeMatrix) {}
		~DMKAnimNode() {}

		/*
		 Set the offset matrix of this node.
		*/
		void setOffsetMatrix(const Matrix4F& mat);

		/*
		 Get the offset matrix of this node.
		*/
		Matrix4F getOffsetMatrix();

		/*
		 Set the node matrix of this node.
		*/
		void setNodeMatrix(const Matrix4F& mat);

		/*
		 Get the node matrix of this node.
		*/
		Matrix4F getNodeMatrix();

		/*
		 Set the world transform of this node.
		*/
		void setWorldTransform(const Matrix4F& mat);

		/*
		 Get the world transform of this node.
		*/
		Matrix4F getWorldTransform();

		/*
		 Add child node index.
		*/
		void addChildNodeIndex(const UI64& index);

		/*
		 Add vertex ID and vertex weight of the node.
		*/
		void addVertexData(const UI32& vertexID, const F32& weight);

		/* The offset matrix */
		Matrix4F offsetMatrix = Matrix4F(1.0f);

		/* The node matrix */
		Matrix4F nodeMatrix = Matrix4F(1.0f);		/* In relation to the parent */

		/* The world transform */
		Matrix4F worldTransform = Matrix4F(1.0f);

		/* Child node indexes */
		ARRAY<UI64> childNodeIndexes;

		/* Vertex IDs */
		ARRAY<UI32> vertexIDs;

		/* Weights */
		ARRAY<F32> weights;

		/* Node name */
		STRING name = TEXT("");

		/* Parent node index */
		UI64 parentIndex = 0;

		/* Index of the current node */
		UI64 index = 0;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_H
