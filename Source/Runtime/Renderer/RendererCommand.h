// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_COMMANDS_H
#define _DYNAMIK_RENDERER_COMMANDS_H

#include "Managers/Thread/ThreadCommand.h"
#include "Core/Types/DataTypes.h"
#include "Window/WindowHandle.h"
#include "Components/ContextTypeDefs.h"
#include "Components/CoreTypeDefs.h"
#include "GameLibrary/LevelComponent.h"

namespace Dynamik
{
	/* Renderer Instructions */
	enum class DMK_API RendererInstruction {
		RENDERER_INSTRUCTION_INITIALIZE,
		RENDERER_INSTRUCTION_CREATE_CONTEXT,
		RENDERER_INSTRUCTION_INITIALIZE_CAMERA,
		RENDERER_INSTRUCTION_INITIALIZE_GAME_WORLD,
		RENDERER_INSTRUCTION_INITIALIZE_ENVIRONMENT_MAP,
		RENDERER_INSTRUCTION_INITIALIZE_ENTITY,
		RENDERER_INSTRUCTION_INITIALIZE_FINALS,
		RENDERER_INSTRUCTION_SUBMIT_OBJECTS,

		RENDERER_INSTRUCTION_DRAW_INITIALIZE,
		RENDERER_INSTRUCTION_DRAW_UPDATE,
		RENDERER_INSTRUCTION_DRAW_SUBMIT,

		RENDERER_INSTRUCTION_TERMINATE_FRAME,
		RENDERER_INSTRUCTION_TERMINATE_OBJECTS,
		RENDERER_INSTRUCTION_TERMINATE,

		RENDERER_INSTRUCTION_UPDATE_OBJECTS,

		RENDERER_INSTRUCTION_SET_SAMPLES,
		RENDERER_INSTRUCTION_SET_WINDOW_HANDLE,

		RENDERER_RESIZE_FRAME_BUFFER
	};

	/*
	 Renderer Command object for the Dynamik Engine
	*/
	class DMK_API DMKRendererCommand : public DMKThreadSystemCommand {
	public:
		DMKRendererCommand() {}
		DMKRendererCommand(RendererInstruction ins) : instruction(ins) {}
		virtual ~DMKRendererCommand() {}

		RendererInstruction instruction = RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE;
	};

	/* Samples command */
	class DMK_API RendererSetSamplesCommand : public DMKRendererCommand {
	public:
		RendererSetSamplesCommand() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_SET_SAMPLES) {}
		~RendererSetSamplesCommand() {}

		DMKSampleCount samples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;
	};

	/* Window handle command */
	class DMK_API RendererSetWindowHandleCommand : public DMKRendererCommand {
	public:
		RendererSetWindowHandleCommand() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_SET_WINDOW_HANDLE) {}
		~RendererSetWindowHandleCommand() {}

		DMKWindowHandle* windowHandle = nullptr;
	};

	/* Render context command */
	class DMK_API RendererCreateContextCommand : public DMKRendererCommand {
	public:
		RendererCreateContextCommand() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_CREATE_CONTEXT) {}
		~RendererCreateContextCommand() {}

		DMKViewport viewport;
		DMKRenderContextType contextType;
	};

	/* Initialize Camera */
	class DMK_API RendererInitializeCamera : public DMKRendererCommand {
	public:
		RendererInitializeCamera() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_CAMERA) {}
		~RendererInitializeCamera() {}

		DMKCameraModule* pCameraModule = nullptr;
	};

	/* Initialize Game World */
	class DMK_API RendererInitializeGameWorld : public DMKRendererCommand {
	public:
		RendererInitializeGameWorld() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_GAME_WORLD) {}
		~RendererInitializeGameWorld() {}

		DMKGameWorld* pGameWorld = nullptr;
	};

	/* Initialize Environment Map */
	class DMK_API RendererInitializeEnvironmentMap : public DMKRendererCommand {
	public: 
		RendererInitializeEnvironmentMap() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENVIRONMENT_MAP) {}
		~RendererInitializeEnvironmentMap() {}

		DMKEnvironmentMap* pEnvironmentMap = nullptr;
	};

	/* Add Entity */
	class DMK_API RendererAddEntity : public DMKRendererCommand {
	public:
		RendererAddEntity() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENTITY) {}
		~RendererAddEntity() {}

		DMKGameEntity* entity = nullptr;
	};

	/* Resize Frame Buffer */
	class DMK_API RendererResizeFrameBuffer : public DMKRendererCommand {
	public:
		RendererResizeFrameBuffer() : DMKRendererCommand(RendererInstruction::RENDERER_RESIZE_FRAME_BUFFER) {}
		~RendererResizeFrameBuffer() {}

		DMKExtent2D windowExtent;
	};
}

#endif // !_DYNAMIK_RENDERER_COMMANDS_H
