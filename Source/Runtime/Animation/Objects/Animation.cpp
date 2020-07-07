#include "dmkafx.h"
#include "Animation.h"

namespace Dynamik
{
	F32 DMKAnimation::getDuration() const
	{
		return duration;
	}

	DMKAnimKeyFrame DMKAnimation::getFame(I64 index) const
	{
		return frames[index];
	}

	ARRAY<DMKAnimKeyFrame> DMKAnimation::getFrames() const
	{
		return frames;
	}
}
