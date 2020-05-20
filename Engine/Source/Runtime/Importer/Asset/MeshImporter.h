#pragma once
#ifndef _DYNAMIK_MESH_IMPORTER_H
#define _DYNAMIK_MESH_IMPORTER_H

/*
 Author:    Dhiraj Wishal
 Date:      20/05/2020
*/
#include "Object/Utility.h"
#include "Object/Resource/MeshComponent.h"

namespace Dynamik 
{
    /*
     Mesh Importer for the Dynamik Engine
     This importer is used to import meshes (including animated meshes) to the Dynamik Engine.
     For now we are using the library Assimp.
    */
    class DMK_API DMKMeshImporter : public DMKUtility {
    public:
        DMKMeshImporter() {}
        ~DMKMeshImporter() {}

        /* Load a mesh component */
        POINTER<DMKMeshComponent> loadMesh(const STRING& path, const DMKVertexBufferDescriptor& vertexBufferDescriptor);

        /* Unload a loaded mesh component */
        void unloadMesh(const POINTER<DMKMeshComponent>& mesh);
    };
}

#endif // !_DYNAMIK_MESH_IMPORTER_H.
