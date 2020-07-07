#include "dmkafx.h"
#include "AnimationComponent.h"

namespace Dynamik
{
	F32 DMKAnimationComponent::getDuration() const
	{
		return duration;
	}

	DMKAnimKeyFrame DMKAnimationComponent::getFame(I64 index) const
	{
		return frames[index];
	}

	ARRAY<DMKAnimKeyFrame> DMKAnimationComponent::getFrames() const
	{
		return frames;
	}
}
