// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Level1.h"
#include "Player.h"
#include "DefaultWorld.h"
#include "Core/Math/MathFunctions.h"
#include "Core/Types/StaticArray.h"
#include "SkySphere.h"
#include "Entities/CerberusModel.h"
using namespace Dynamik;

void Level1::onLoad()
{
	playerObject = createUserPlayer<Player>();

	playerObject->cameraModule = StaticAllocator<DMKCameraModule>::allocate();
	playerObject->setPosition({ 0.0f, 0.0f, 0.0f });
	playerObject->setCameraPosition({ 0.0f, 0.0f, 0.0f });
	playerObject->setCameraAndWorldUp(VEC3(0.0f, -1.0f, 0.0f), VEC3(0.0f, -1.0f, 0.0f));
	playerObject->getCameraModule()->setExposure(1.0f);
	playerObject->getCameraModule()->setGamma(1.0f);

	/* Create Basic World */
	createUserGameWorld<DefaultWorld>();
	pCurrentGameWorld->setCamera(playerObject->getCameraModule());

	movementBias = 0.1f;
}

void Level1::onUpdate(const DMKEventPool* pEventPool)
{
	static B1 refresh = false;

	if (DMKEventPool::MouseButtonLeft.isPressed())
	{
		playerObject->processMouseControl(DMKEventPool::getMousePosition(), 0.1f, refresh, true);
		refresh = false;

		auto ray = playerObject->getCameraModule()->generateRay(DMKEventPool::getMousePosition());

		if (shouldRenderRay)
		{
			//copyDataToDebug(ray);
			shouldRenderRay = false;
		}

		//for (auto entity : pCurrentGameWorld->entities)
		//	for (UI64 index = 0; index < entity->getComponentArray<DMKBoundingBoxAttachment>()->size(); index++)
		//		entity->getComponent<DMKBoundingBoxAttachment>(index)->checkRayIntercept(ray);
	}
	if (DMKEventPool::MouseButtonLeft.isReleased())
		refresh = true;

	if (DMKEventPool::MouseButtonRight.isPressed())
		shouldRenderRay = true;

	if (DMKEventPool::KeyUp.isPressed() || DMKEventPool::KeyUp.isOnRepeat())
		playerObject->addUpVector(movementBias);

	if (DMKEventPool::KeyDown.isPressed() || DMKEventPool::KeyDown.isOnRepeat())
		playerObject->addDownVector(movementBias);

	if (DMKEventPool::KeyRight.isPressed() || DMKEventPool::KeyRight.isOnRepeat())
	{
		Inherit<SkySphere>(pCurrentGameWorld->pEnvironmentMap)->fsUBO.exposure += 0.1f;
		//Inherit<CerberusModel>(pCurrentGameWorld->entities[0])->camParamFS.exposure += 0.1f;
	}

	if (DMKEventPool::KeyLeft.isPressed() || DMKEventPool::KeyLeft.isOnRepeat())
	{
		Inherit<SkySphere>(pCurrentGameWorld->pEnvironmentMap)->fsUBO.exposure -= 0.1f;
		//Inherit<CerberusModel>(pCurrentGameWorld->entities[0])->camParamFS.exposure -= 0.1f;
	}

	if (DMKEventPool::KeyI.isPressed() || DMKEventPool::KeyI.isOnRepeat())
	{
		Inherit<SkySphere>(pCurrentGameWorld->pEnvironmentMap)->fsUBO.gamma += 0.1f;
		//Inherit<CerberusModel>(pCurrentGameWorld->entities[0])->camParamFS.gamma += 0.1f;
	}

	if (DMKEventPool::KeyO.isPressed() || DMKEventPool::KeyO.isOnRepeat())
	{
		Inherit<SkySphere>(pCurrentGameWorld->pEnvironmentMap)->fsUBO.gamma -= 0.1f;
		//Inherit<CerberusModel>(pCurrentGameWorld->entities[0])->camParamFS.gamma -= 0.1f;
	}

	playerObject->updateCamera();
}

void Level1::setupPlayerControls(DMKPlayerController* pController)
{
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_FORWARD, TEXT("KeyW"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_BACKWARD, TEXT("KeyS"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_LEFT, TEXT("KeyA"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
	pController->bindMovementControl(DMKMovementControlInstruction::DMK_MOVEMENT_CONTROL_INSTRUCTION_MOVE_RIGHT, TEXT("KeyD"), this, (DMKEventType)(DMK_EVENT_TYPE_REPEAT | DMK_EVENT_TYPE_PRESS));
}

void Level1::onPlayerMoveForward()
{
	playerObject->addForwardVector(movementBias);
}

void Level1::onPlayerMoveBackward()
{
	playerObject->addBackwardVector(movementBias);
}

void Level1::onPlayerMoveLeft()
{
	playerObject->addRightVector(movementBias);
}

void Level1::onPlayerMoveRight()
{
	playerObject->addLeftVector(movementBias);
}

DMKDebugComponent Level1::initializeRayLine()
{
	DMKDebugComponent rayLine;

	/* Initialize Shaders */
	rayLine.addShader(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + TEXT("/Runtime/Assets/Shaders/RayLine/vert.spv"), DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));
	rayLine.addShader(DMKShaderFactory::createModule(DMKFileSystem::getWorkingDirectory() + TEXT("/Runtime/Assets/Shaders/RayLine/frag.spv"), DMKShaderLocation::DMK_SHADER_LOCATION_FRAGMENT, DMKShaderCodeType::DMK_SHADER_CODE_TYPE_SPIRV));

	/* Initialize Vertex Buffer */
	DMKVertexLayout layout;
	DMKVertexAttribute attribute;
	attribute.attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
	attribute.dataCount = 1;
	attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
	layout.attributes.pushBack(attribute);
	rayLine.vertexBuffer.setLayout(layout);

	rayLine.vertexBuffer.initialize(2);

	struct VertexT {
		Vector3F position = Vector3F(1.0f);
	};

	StaticArray<VertexT, 2> vertexData;
	rayLine.vertexBuffer.setData(vertexData.data());

	/* Initialize Index Buffer */
	rayLine.setIndexBuffer({ 0, 1 });

	return rayLine;
}

void Level1::copyDataToDebug(DMKCameraRay ray)
{
	auto component = pCurrentGameWorld->entities.front()->getComponent<DMKDebugComponent>();
	if (component)
		component->getVertexBuffer().setData(&ray);
}
