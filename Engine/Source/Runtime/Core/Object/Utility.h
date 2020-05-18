#pragma once
#ifndef _DYNAMIK_UTILITY_H
#define _DYNAMIK_UTILITY_H

/*
 All the Utility classes are derived from this class.
 Types of utilities:
 * Error Message box

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Object.h"

namespace Dynamik
{
	class DMK_API DMKUtility : public DMKObject {
	public:
		DMKUtility() {}
		virtual ~DMKUtility() {}
	};
}

#endif // !_DYNAMIK_UTILITY_H
