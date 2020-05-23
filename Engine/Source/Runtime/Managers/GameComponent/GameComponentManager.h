#pragma once
#ifndef _DYNAMIK_GAME_COMPONENT_MANAGER_H
#define _DYNAMIK_GAME_COMPONENT_MANAGER_H

/*
 Author:    Dhiraj Wishal
 Date:      23/05/2020
*/
#include "Object/System.h"
#include "Types/Array.h"
#include "GameLibrary/LevelComponent.h"

namespace Dynamik
{
    class DMK_API DMKGameComponentManager : public DMKSystem {
    public:
        DMKGameComponentManager() {}
        ~DMKGameComponentManager() {}

        void addLevel(POINTER<DMKLevelComponent> levelComponent);

        void loadLevel(UI32 levelIndex);
        void unloadLevel(UI32 levelIndex);

    private:
        ARRAY<POINTER<DMKLevelComponent>> myLevelStore;
        UI32 myCurrentLevel = 0;
    };
}

#endif // !_DYNAMIK_GAME_COMPONENT_MANAGER_H
