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
		DMKAnimNode(UI32 index, STRING name, Matrix4F localTransform)
			: index(index), name(name), localTransform(localTransform) {}
		~DMKAnimNode() {}

		/*
		 Set the parent node.
		*/
		void setParentNode(DMKAnimNode* pAnimNode);

		/*
		 Add a child node.
		*/
		void addChildNode(DMKAnimNode* pAnimNode);

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

		/* Child node pointers of this node */
		ARRAY<DMKAnimNode*> pChildNodes;

		/* Node name */
		STRING name = TEXT("");

		/* Parent node pointer of this node */
		DMKAnimNode* pParentNode = nullptr;

		/* Node index */
		UI32 index = 0;
	};
}

#endif // !_DYNAMIK_ANIMATION_NODE_H
