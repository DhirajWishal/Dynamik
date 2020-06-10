#pragma once
#ifndef _DYNAMIK_CAMERA_COMPONENT_H
#define _DYNAMIK_CAMERA_COMPONENT_H

/*
 Author:	Dhiraj Wishal
 Date:		10/06/2020
*/
#include "../Component.h"

namespace Dynamik
{
	/*
	 Dynamik Camera Component
	*/
	class DMK_API DMKCameraComponent : public DMKComponent {
	public:
		DMKCameraComponent() {}
		~DMKCameraComponent() {}

		void setAttachment(POINTER<DMKComponent> attachment) override;
	};
}

#endif // !_DYNAMIK_CAMERA_COMPONENT_H
