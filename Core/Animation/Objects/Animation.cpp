// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Animation.h"

void DMKAnimation::bake(DMKAnimNodeGraph nodeGraph, std::unordered_map<STRING, UI64> nodeMap)
{
	for (auto node : nodeGraph.nodes)
	{
		ANodeFrames frames;

		if (nodePoseMap.find(node.name) != nodePoseMap.end())
		{
			for (auto pose : nodePoseMap[node.name])
				frames.transforms.push_back(pose.getMatrix());
		}
		else
			frames.transforms.resize(Cast<UI32>(std::ceilf(framesPerSecond * duration)), node.worldTransform);

		nodeFrames.push_back(frames);
	}
}

std::vector<Matrix4F> DMKAnimation::getMatrices(float timeStep)
{
	std::vector<Matrix4F> matrices;

	for (auto frame : nodeFrames)
		matrices.push_back(frame.transforms[Cast<UI32>(timeStep)]);

	return matrices;
}
