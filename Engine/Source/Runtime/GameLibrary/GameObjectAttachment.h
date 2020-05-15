#pragma once
#ifndef _DYNAMIK_GAME_OBJECT_ATTACHMENT_H
#define _DYNAMIK_GAME_OBJECT_ATTACHMENT_H

/*
 Game Object Attachment for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "GameObject.h"

namespace Dynamik
{
    /*
     Game Object Attachments describe additional ways to manipulate game objects.
     Game Objects can contain multiple attachments.
    */
    DMK_ALIGN class DMK_API DMKGameObjectAttachment : public DMKGameComponent {
    public:
        DMKGameObjectAttachment() {}
        virtual ~DMKGameObjectAttachment() {}

        POINTER<DMKGameObject> myParentObject;  /* Game object address the attachment is attached to */
    };
}

#endif // !_DYNAMIK_GAME_OBJECT_ATTACHMENT_H
