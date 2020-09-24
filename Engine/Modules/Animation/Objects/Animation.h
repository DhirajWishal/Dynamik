// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ANIMATION_H
#define _DYNAMIK_ANIMATION_H

#include "AnimNodePose.h"
#include "AnimNodeGraph.h"

/* Animation Node Frames */
struct DMK_API ANodeFrames {
	ARRAY<Matrix4F> transforms;
};

/*
 Dynamik Animation
 This stores all the relevant information required to store and render animations.

 Dynamik animations work by pre computing all the final transforms of all the nodes for a given
 frame/ tick, and playing all of them sequentially as required by the client. The client is allowed to
 update the duration, ticks per second and other factors and this may result in re-baking the whole
 animation transforms for each frame.
 Baking the animations help in improving rendering performance as the engine is not required to
 compute all the node transforms on each frame.

 Contents:
   - Node Poses (All the poses a node will contain)
   - Final Node Transforms (All the final transforms for each node)
   - Duration
   - Ticks Per Second/ Frames Per Second
*/
class DMK_API DMKAnimation {
public:
	DMKAnimation() {}
	~DMKAnimation() {}

	/*
	 Bake the animation.
	*/
	void bake(DMKAnimNodeGraph nodeGraph, std::unordered_map<STRING, UI64> nodeMap);

	/*
	 Get all matrices in a given time step.
	*/
	ARRAY<Matrix4F> getMatrices(F32 timeStep);

	/* All the node poses */
	std::unordered_map<STRING, ARRAY<DMKAnimNodePose>> nodePoseMap;

	/* All the node frames */
	ARRAY<ANodeFrames> nodeFrames;

	/* Total duration of the animation. */
	F32 duration = 0.0f;

	/*
	 FPS rate which the animation gets played.
	 Default is 30.
	*/
	F32 framesPerSecond = 30.0f;
};

#endif // !_DYNAMIK_ANIMATION_H
