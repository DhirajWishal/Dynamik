// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MESH_IMPORTER_H
#define _DYNAMIK_MESH_IMPORTER_H

#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"

namespace Dynamik 
{
    /*
     Mesh Importer for the Dynamik Engine
     This importer is used to import meshes (including animated meshes) to the Dynamik Engine.
     For now we are using the library Assimp.
    */
    class DMK_API DMKMeshImporter {
        DMKMeshImporter() {}
        ~DMKMeshImporter() {}
    public:
        /* Load a mesh component */
        static ARRAY<DMKMeshComponent> loadMeshes(const STRING& path, const DMKVertexLayout& vertexLayout);

        /* Unload a loaded mesh component */
        static void unloadMesh(const ARRAY<DMKMeshComponent>& meshes);
    };
}

#endif // !_DYNAMIK_MESH_IMPORTER_H.
