// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_COMPONENT_H
#define _DYNAMIK_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		06/06/2020
*/
#include "Core/Macros/Global.h"
#include "Core/Types/TSArray.h"
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

		virtual void setAttachment(DMKComponentAttachment* attachment) { attachments.pushBack(attachment); }

		ARRAY<DMKComponentAttachment*> attachments;
	};
}

#endif // !_DYNAMIK_COMPONENT_H
