// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_RENDERER_COMMANDS_H
#define _DYNAMIK_RENDERER_COMMANDS_H

#include "Core/Types/DataTypes.h"
#include "Window/WindowHandle.h"
#include "Components/ContextTypeDefs.h"
#include "Components/CoreTypeDefs.h"
#include "GameLibrary/GameModule.h"

#include "GameLibrary/Entities/AnimatedModelEntity.h"

#include "Clients/ImGuiBackendHandle.h"

	/* Renderer Instructions */
enum class DMK_API RendererInstruction {
	RENDERER_INSTRUCTION_INITIALIZE,
	RENDERER_INSTRUCTION_CREATE_CONTEXT,
	RENDERER_INSTRUCTION_INITIALIZE_ENVIRONMENT_MAP,
	RENDERER_INSTRUCTION_INITIALIZE_ENTITY,
	RENDERER_INSTRUCTION_INITIALIZE_ENTITIES,
	RENDERER_INSTRUCTION_INITIALIZE_FINALS,
	RENDERER_INSTRUCTION_SUBMIT_OBJECTS,

	RENDERER_INSTRUCTION_DRAW_INITIALIZE,
	RENDERER_INSTRUCTION_DRAW_UPDATE,						/* Updates all the entities */
	RENDERER_INSTRUCTION_DRAW_UPDATE_ENVIRONMENT,
	RENDERER_INSTRUCTION_DRAW_UPDATE_ENTITIES,
	RENDERER_INSTRUCTION_DRAW_UPDATE_BOUNDING_BOXES,
	RENDERER_INSTRUCTION_DRAW_SUBMIT,

	RENDERER_INSTRUCTION_TERMINATE_FRAME,
	RENDERER_INSTRUCTION_TERMINATE_OBJECTS,
	RENDERER_INSTRUCTION_TERMINATE,

	RENDERER_INSTRUCTION_UPDATE_OBJECTS,

	RENDERER_INSTRUCTION_SET_SAMPLES,
	RENDERER_INSTRUCTION_SET_WINDOW_HANDLE,

	RENDERER_RESIZE_FRAME_BUFFER,

	RENDERER_SET_IM_GUI_CONTEXT,
	RENDERER_CREATE_IM_GUI_CLIENT,
	RENDERER_UPDATE_IM_GUI
};

/*
 Renderer Command object for the Dynamik Engine
*/
class DMK_API DMKRendererCommand {
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

/* Initialize Environment Map */
class DMK_API RendererInitializeEnvironmentEntity : public DMKRendererCommand {
public:
	RendererInitializeEnvironmentEntity() : DMKRendererCommand(RendererInstruction::RENDERER_INSTRUCTION_INITIALIZE_ENVIRONMENT_MAP) {}
	~RendererInitializeEnvironmentEntity() {}

	DMKEnvironmentEntity* pEnvironmentEntity = nullptr;
	UI32* pProgressMeter = nullptr;
};

/* Submit static entity */
class DMK_API RendererSubmitStaticEntity : public DMKRendererCommand {
public:
	RendererSubmitStaticEntity() {}
	~RendererSubmitStaticEntity() {}

	DMKStaticModelEntity* pEntity = nullptr;
	UI32* pProgressMeter = nullptr;
};

/* Submit animated entity */
class DMK_API RendererSubmitAnimatedEntity : public DMKRendererCommand {
public:
	RendererSubmitAnimatedEntity() {}
	~RendererSubmitAnimatedEntity() {}

	DMKAnimatedModelEntity* pEntity = nullptr;
	UI32* pProgressMeter = nullptr;
};

/* Remove a static model from memory. */
class DMK_API RendererRemoveStaticModelEntity {
public:
	RendererRemoveStaticModelEntity() {}
	~RendererRemoveStaticModelEntity() {}

	DMKStaticModelEntity* pStaticModelEntity = nullptr;
};

/* Resize Frame Buffer */
class DMK_API RendererResizeFrameBuffer : public DMKRendererCommand {
public:
	RendererResizeFrameBuffer() : DMKRendererCommand(RendererInstruction::RENDERER_RESIZE_FRAME_BUFFER) {}
	~RendererResizeFrameBuffer() {}

	DMKExtent2D windowExtent;
};

/* Set the im gui context */
class DMK_API RendererSetImGuiContext : public DMKRendererCommand {
public:
	RendererSetImGuiContext() : DMKRendererCommand(RendererInstruction::RENDERER_SET_IM_GUI_CONTEXT) {}
	~RendererSetImGuiContext() {}

	ImGuiContext* pContext = nullptr;
};

/* Create Im Gui Client */
class DMK_API RendererCreateImGuiClient : public DMKRendererCommand {
public:
	RendererCreateImGuiClient() : DMKRendererCommand(RendererInstruction::RENDERER_CREATE_IM_GUI_CLIENT) {}
	~RendererCreateImGuiClient() {}

	/* This pointer stores the return address of the Im Gui client */
	DMKImGuiBackendHandle** pReturnAddressSpace = nullptr;
};

#endif // !_DYNAMIK_RENDERER_COMMANDS_H
