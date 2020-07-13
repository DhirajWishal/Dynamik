// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_NODE_H
#define _DYNAMIK_ANIMATION_NODE_H

#include "Core/Types/Array.h"
#include "Core/Math/Matrix/Matrix4F.h"

namespace Dynamik
{
	/* Animation Node Info */
	struct DMK_API AAnimNodeInfo {
		AAnimNodeInfo() {}
		~AAnimNodeInfo() {}

		Matrix4F offset;
		Matrix4F finalTransform;
	};

	/* Animation Node Data */
	struct DMK_API AAnimNodeData {
		ARRAY<UI32> vertexIDs;
		ARRAY<F32> weights;

		void add(const UI32& vertexID, const F32& weight);
	};

	/*
	 Dynamik Animation Node (Anim-Node)
	 This object stores one node/ bone in an animation.
	*/
	class DMK_API DMKAnimNode {
	public:
		DMKAnimNode() {}
		DMKAnimNode(UI32 parentIndex, STRING name, Matrix4F localTransform)
			: parentIndex(parentIndex), name(name), localTransform(localTransform) {}
		~DMKAnimNode() {}

		/*
		 Add a child node index.
		*/
		void addChildNodeIndex(UI64 iIndex);

		/*
		 Get the animated transform.
		*/
		Matrix4F getAnimatedTransform() const;

		/*
		 Set the animated transform.
		*/
		void setAnimatedTransform(const Matrix4F& transform);

		/*
		 Calculate the inverse bind transform.
		*/
		void calculateInverseBindTransform(const Matrix4F& parentBindTransform);

		/* Animated Transform */
		Matrix4F animatedTransform = Matrix4F(1.0f);
		Matrix4F localTransform = Matrix4F(1.0f);
		Matrix4F inverseBindTransform = Matrix4F(1.0f);

		Matrix4F offsetMatrix = Matrix4F(1.0f);
		Matrix4F nodeMatrix = Matrix4F(1.0f);		/* In relation to the parent */
		Matrix4F worldTransform = Matrix4F(1.0f);

		/* Child node indexes */
		ARRAY<UI64> childNodeIndexes;

		/* Node name */
		STRING name = TEXT("");

		/* Parent node index */
		UI64 parentIndex = 0;

		/* Index of the current node */
		UI64 index = 0;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_H
