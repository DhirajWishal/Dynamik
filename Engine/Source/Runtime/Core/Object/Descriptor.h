#pragma once
#ifndef _DYNAMIK_DESCRIPTOR_H
#define _DYNAMIK_DESCRIPTOR_H

/*
 All the descriptor classes are derived from this class.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
	class DMK_API DMKDescriptor : public DMKObject {
	public:
		DMKDescriptor() {}
		virtual ~DMKDescriptor() {}
	};
}

#endif // !_DYNAMIK_DESCRIPTOR_H
