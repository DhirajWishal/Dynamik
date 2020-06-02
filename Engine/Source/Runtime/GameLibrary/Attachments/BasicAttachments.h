#pragma once
#ifndef _DYNAMIK_BASIC_ATTACHMENTS_H
#define _DYNAMIK_BASIC_ATTACHMENTS_H

/*
 Author:    Dhiraj Wishal
 Date:      21/05/2020
*/
#include "../GameAssetAttachment.h"
#include "Math/MathTypes.h"
#include "Types/DataTypes.h"

namespace Dynamik
{
    /*
     Transform Attachment
    */
    class DMK_API TransformAttachment : public DMKGameAssetAttachment {
    public:
        TransformAttachment() : DMKGameAssetAttachment(DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_TRANSFORM){}
        ~TransformAttachment() {}

        VEC3F location = { 0.0f, 0.0f, 0.0f };
    };

    /*
     Scale Attachment
    */
    class DMK_API ScaleAttachment : public DMKGameAssetAttachment {
    public:
        ScaleAttachment() : DMKGameAssetAttachment(DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_SCALE){}
        ~ScaleAttachment() {}

        VEC3F scale = { 0.0f, 0.0f, 0.0f };
    };

    /*
     Material Attachment
    */
    class DMK_API MaterialAttachment : public DMKGameAssetAttachment {
    public:
        MaterialAttachment() : DMKGameAssetAttachment(DMKGameAssetAttachmentType::DMK_GAME_ASSET_ATTACHMENT_TYPE_MATERIAL) {}
        ~MaterialAttachment() {}

        VEC4F baseColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        VEC4F subsurfaceColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        F32 metalic = 1.0f;
        F32 specular = 1.0f;
        F32 roughness = 1.0f;
        F32 alpha = 1.0f;
    };
}

#endif // !_DYNAMIK_BASIC_ATTACHMENTS_H
