#pragma once
#ifndef _DYNAMIK_GAME_ASSET_ATTACHMENT_H
#define _DYNAMIK_GAME_ASSET_ATTACHMENT_H

/*
 Game Asset Attachment for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Object/GameComponent.h"

namespace Dynamik
{
	/* Attachment types */
	enum class DMK_API DMKGameAssetAttachmentType {
		DMK_GAME_ASSET_ATTACHMENT_TYPE_TRANSFORM,
		DMK_GAME_ASSET_ATTACHMENT_TYPE_SCALE,
		DMK_GAME_ASSET_ATTACHMENT_TYPE_MATERIAL,
	};

	/*
	 Game Asset Attachments describe additional ways to manipulate game objects. This may include physics
	 body entities, destruction entities, particle systems, etc...
	 Game Objects can contain multiple attachments.
	*/
	class DMK_API DMKGameAssetAttachment : public DMKGameComponent {
	public:
		DMKGameAssetAttachment(DMKGameAssetAttachmentType ty)
			: DMKGameComponent(DMKGameComponentType::DMK_GAME_COMPONENT_TYPE_ATTACHMENT),
			attachmentType(ty) {}
		virtual ~DMKGameAssetAttachment() {}

		DMKGameAssetAttachmentType attachmentType;
	};
}

#endif // !_DYNAMIK_GAME_OBJECT_ATTACHMENT_H
