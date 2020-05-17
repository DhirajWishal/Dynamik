#pragma once
#ifndef _DYNAMIK_MATERIAL_DESCRIPTOR_H
#define _DYNAMIK_MATERIAL_DESCRIPTOR_H

/*
 Material Descriptor for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/
#include "Object/Descriptor.h"

namespace Dynamik
{
    /*
     This object defines the basic components tied to the Dynamik Material system.
    */
    DMK_ALIGN class DMK_API DMKMaterialDescriptor : public DMKDescriptor {
    public:
        DMKMaterialDescriptor() {}
        virtual ~DMKMaterialDescriptor() {}
    };
}

#endif // !_DYNAMIK_MATERIAL_DESCRIPTOR_H
