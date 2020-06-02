#pragma once
#ifndef _DYNAMIK_ATTACHMENT_MANAGER_H
#define _DYNAMIK_ATTACHMENT_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      20/05/2020
*/
#include "GameLibrary/GameAssetAttachment.h"

namespace Dynamik
{
    /*
     Dynamik Attachment Manager
     Game objects use attachments to add aditional functionalities. Since these attachments are added inheritently,
     it is not that easy to make them cache friendly. This is where the attachment manager comes to play.
     The basic way the manager accomplishes this is by maintaining a pool of memory where all the attachment
     data are stored. When accessed, the CPU will load multiple data stored in the pool this reducing latency.

     Since most of the attachments are added and/ or removed by the studio, the allocation time and recompation
     time will not affect the game runtime preformance.
     This system is closely related to ECS (Entity Component System) but one of the core features of this is that
     components could have functionalities.
    */
    class DMK_API DMKAttachmentManager {
        struct DMK_API AttachmentMap {
            DMKGameAssetAttachmentType type;
            VPTR location = nullptr;
        };

    public:
        DMKAttachmentManager();
        ~DMKAttachmentManager();

        void addAttachment(POINTER<DMKGameAssetAttachment> attachment);

        VPTR getBuffer() { return myMemoryBuffer; }

    private:
        /*
         If already allocated, it automatically extend the heap and move the existing data
        */
        inline void _allocateHeap(UI32 byteSize);

        inline void _recreateReferenceTable();

        std::unordered_map<STRING, POINTER<BYTE>> myReferenceTable;
        ARRAY<AttachmentMap> componentMapping;
        VPTR myMemoryBuffer = nullptr;
        POINTER<BYTE> myNextPtr = myMemoryBuffer;
        UI32 myAllocationSize = 0;
        UI32 myDataIndex = 0;
    };
}

#endif // !_DYNAMIK_ATTACHMENT_MANAGER_H
