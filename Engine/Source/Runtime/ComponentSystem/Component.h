// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Macros/Global.h"
#include "Types/TSArray.h"
#include "ComponentAttachments/ComponentAttachment.h"

namespace Dynamik
{
	/*
	 Component object for the Dynamik Engine
	*/
	class DMK_API DMKComponent {
	public:
		DMKComponent() {}
		virtual ~DMKComponent() {}

		virtual void setAttachment(POINTER<DMKComponentAttachment> attachment) { attachments.pushBack(attachment); }

		ARRAY<POINTER<DMKComponentAttachment>> attachments;
	};
}

#endif // !_DYNAMIK_COMPONENT_H
