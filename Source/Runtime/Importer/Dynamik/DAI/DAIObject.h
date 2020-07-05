// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_DAI_OBJECT_H
#define _DYNAMIK_DAI_OBJECT_H

#include "ComponentSystem/Components/RenderableComponents/MeshComponent.h"
#include <fstream>

namespace Dynamik
{
    /*
     Dynamik Asset Index object
     Dynamik Engine indexes all of its assets by the DAI file. Since the engine handles object based on its type,
     DAI files help the engine identify what the imported object really is. Mostly this is used for assets which
     has its own shaders and other resources. For basic assets (a simple model with textures) its best advised
     to use the DMKAsset files.

     There are various data stored in this file. These elements are:
     * Models/ Meshes (eg: M model.obj)
     * Textures (eg: I texture.jpg)
     * Shaders
        - Vertex shader (eg: V vert.spv)
        - Tessellation shader (eg: T tess.spv)
        - Geometry shader (eg: G geom.spv)
        - Fragment shader (eg: F frag.spv)
     * Object Type (eg: > STATIC)

     ---------- DAI FILE RULES ----------
     * All the elements (M, I, V, T, G, F, >) must be in the start of each line (at index 0)
     * All the element data must be stored one space away from the element (V model.fbx)
    */
    class DMK_API DAIObject {
    public:
        DAIObject() {}
        DAIObject(const STRING& path) : myPath(path) {}
        ~DAIObject() { myFile.close(); }

        void load();

        ARRAY<STRING> meshes;
        ARRAY<STRING> textures;
        ARRAY<STRING> vertexShaders;
        ARRAY<STRING> tessellationShaders;
        ARRAY<STRING> geometryShaders;
        ARRAY<STRING> fragmentShaders;
        DMKMeshComponentUsage meshType;

    private:
        inline void _loadContent();
        inline DMKMeshComponentUsage _resolveObjectType(const STRING& type);

        STRING myPath = DMK_TEXT("");
        STRING myBasePath = DMK_TEXT("");
        std::fstream myFile;
    };
}

#endif // !_DYNAMIK_DAI_OBJECT_H
