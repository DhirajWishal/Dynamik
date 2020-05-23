#pragma once
#ifndef _DYNAMIK_GAME_OBJECT_ATTACHMENT_H
#define _DYNAMIK_GAME_OBJECT_ATTACHMENT_H

/*
 Game Object Attachment for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Object/GameComponent.h"

namespace Dynamik
{
	/*
	 Game Object Attachments describe additional ways to manipulate game objects. This may include physics
	 body entities, destruction entities, particle systems, etc...
	 Game Objects can contain multiple attachments.
	*/
	class DMK_API DMKGameAssetAttachment : public DMKGameComponent {
	public:
		DMKGameAssetAttachment() : DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_ATTACHMENT) {}
		virtual ~DMKGameAssetAttachment() {}
	};
}

#endif // !_DYNAMIK_GAME_OBJECT_ATTACHMENT_H
