#pragma once
#ifndef _DYNAMIK_RENDER_ASSET_H
#define _DYNAMIK_RENDER_ASSET_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/

#include "GameLibrary/GameAsset.h"

namespace Dynamik
{
    /*
     Dynamik Render Asset class
     This class does not provide any functionality (other than get and set) but used as a data container for
     different RBLs to store all the necessary data that is required to initialize, update, render and terminate
     a renderable object/ asset.
    */
    class DMK_API DMKRenderAsset {
    public:
        DMKRenderAsset() {}
        DMKRenderAsset(const POINTER<DMKGameAsset>& asset) : myAsset(asset) {}
        virtual ~DMKRenderAsset() {}

        void setAsset(const POINTER<DMKGameAsset>& asset) { myAsset = asset; }
        POINTER<DMKGameAsset> getAsset() { return myAsset; }

    protected:
        POINTER<DMKGameAsset> myAsset;
    };
}

#endif // !_DYNAMIK_RENDER_ASSET_H
