#include "dmkafx.h"
#include "Primitives.h"

namespace Dynamik
{
	UI32 DMKVertexBufferDescriptor::getVertexSize()
	{
		UI32 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI32)_attribute.dataType * _attribute.dataCount);

		return _size;
	}
	
	UI64 DMKUniformBufferObject::getUniformSize()
	{
		UI32 _size = 0;
		for (auto _attribute : attributes)
			_size += ((UI32)_attribute.dataType * _attribute.dataCount);

		return _size;
	}
}
