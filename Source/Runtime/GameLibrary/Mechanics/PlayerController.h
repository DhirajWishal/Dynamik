// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PLAYER_CONTROLLER_H
#define _DYNAMIK_PLAYER_CONTROLLER_H

#include "../GameMechanics.h"
#include "Events/EventPool.h"

#include <functional>

namespace Dynamik
{
    class DMK_API DMKGameModule;
    class DMK_API DMKPlayerEntity;

    /* Dynamik Movement Control Instruction */
    enum class DMK_API DMKMovementControlInstruction {
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT,

        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_CROUCH,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_JUMP,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RUN,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_PEEK_LEFT,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_PEEK_RIGHT,
        DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_SLIDE,
    };

    /* Dynamik Action Control Instruction */
    enum class DMK_API DMKActionControlInstruction {
        DMK_ACTION_CONTROL_INSTRUCTION_AIM,
        DMK_ACTION_CONTROL_INSTRUCTION_TRIGGER,
        DMK_ACTION_CONTROL_INSTRUCTION_RELOAD,
        DMK_ACTION_CONTROL_INSTRUCTION_LOOK_AT,
        DMK_ACTION_CONTROL_INSTRUCTION_VIEW,
    };

    /* Dynamik Camera Control Instruction */
    enum class DMK_API DMKCameraControlInstruction {
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_FORWARD,
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_BACKWARD,
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_LEFT,
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_RIGHT,
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_UP,
        DMK_CAMERA_CONTROL_INSTRUCTION_MOVE_DOWN,

        DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_X,    /* Yaw */
        DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_Y,    /* Pitch */
        DMK_CAMERA_CONTROL_INSTRUCTION_ROTATE_Z,    /* Roll */
    };

    /*
     Player controller for the Dynamik Engine
     The player camera is controlled by this object.
    */
    class DMK_API DMKPlayerController : public DMKGameMechanics {
        using levelFunc = std::function<void()>;
        using playerFunc = std::function<void()>;

        struct DMK_API FunctionInvokeLevel {
            levelFunc function;
            DMKEventType invokeCondition = DMKEventType::DMK_EVENT_TYPE_FREE;
        };

        struct DMK_API FunctionInvokePlayer {
            playerFunc function;
            DMKEventType invokeCondition = DMKEventType::DMK_EVENT_TYPE_FREE;
        };

    public:
        DMKPlayerController() {}
        ~DMKPlayerController() {}

        void setEventPool(DMKEventPool* pEventPool);

        void executeMovements();
        void executeActions();
        void executeCameraControls();
        void executeAll();

        void reset();

        void bindMovementControl(DMKMovementControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType);
        void bindActionControl(DMKActionControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType);
        void bindCameraControl(DMKCameraControlInstruction instruction, const STRING& sEvent, DMKPlayerEntity* pPlayer, DMKEventType eventType);
    
    private:
        std::unordered_map<STRING, FunctionInvokeLevel> movementControls;
        std::unordered_map<STRING, FunctionInvokeLevel> actionControls;
        std::unordered_map<STRING, FunctionInvokePlayer> cameraControls;

        DMKEventPool* pEventPool = nullptr;
    };
}

#endif // !_DYNAMIK_PLAYER_CONTROLLER_H
