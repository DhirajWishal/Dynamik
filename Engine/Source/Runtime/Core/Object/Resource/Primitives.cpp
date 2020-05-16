#include "dmkafx.h"
#include "Primitives.h"

namespace Dynamik
{
	UI32 DMKVertexBufferDescriptor::getVertexSize()
	{
		UI32 _size = 0;
		for (auto _attribute : attributes)
			_size += (UI32)_attribute.dataType;

		return _size;
	}
}
