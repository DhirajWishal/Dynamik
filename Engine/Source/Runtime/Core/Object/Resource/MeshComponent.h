#pragma once
#ifndef _DYNAMIK_MESH_COMPONENT_H
#define _DYNAMIK_MESH_COMPONENT_H

/*
 Dynamik Mesh Component.
 This component contains all the necessary variables to store all the available mesh data of an imported
 mesh.
 This also contains all the functionalities to manipulate a mesh object.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../Resource.h"

namespace Dynamik
{
    /*
     Mesh Component super class for the Dynamik Engine.
     This class itself does not store any mesh data. Mesh components are derived from this to store their
     data.
     This class contains functions to manipulate a full mesh.
    */
    DMK_ALIGN class DMK_API DMKMeshComponent : public DMKResource {
    public:
        DMKMeshComponent() {}
        virtual ~DMKMeshComponent() {}
    };
}

#endif // !_DYNAMIK_MESH_COMPONENT_H
