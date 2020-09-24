// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_TRIGGER_ENTITY_2D_H
#define _DYNAMIK_TRIGGER_ENTITY_2D_H

#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector/Vector3F.h"

class DMK_API DMKTriggerEntity2D;

/*
 Dynamik Trigger Entity 2D Instance. 
*/
struct DMK_API DMKTriggerEntity2DInstance {
	DMKTriggerEntity2DInstance() {}
	DMKTriggerEntity2DInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F scale, DMKTriggerEntity2D* pParent, UI32 instanceID)
	: instanceName(name), position(position), rotation(rotation), scale(scale), pParent(pParent), instanceID(instanceID) {}

	STRING instanceName = TEXT("");
	Quaternion rotation = Quaternion(0.0f);
	Vector3F position = Vector3F(0.0f);
	Vector3F scale = Vector3F(0.0f);

	DMKTriggerEntity2D* pParent = nullptr;
	UI32 instanceID = 0;
};

/*
 Dynamik Trigger Entity 2D.
 This object handles and acts as an event listener and is updated by the game server. 
*/
class DMK_API DMKTriggerEntity2D {
public:
	DMKTriggerEntity2D() {}
	virtual ~DMKTriggerEntity2D() {}

	/*
	 Add an trigger instance. 

	 @param name: The name of the trigger. 
	 @param position: The position of the trigger. 
	 @param rotation: Rotation of the trigger. 
	 @param scale: The scale of the trigger. 
	*/
	void addInstanceTrigger2D(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale);

	/*
	 On initialize method. 
	*/
	virtual void onInitializeTrigger2D() {}

	/*
	 On update method. 
	*/
	virtual void onUpdateTrigger2D() {}

	/*
	 On terminate method. 
	*/
	virtual void onTerminateTrigger2D() {}

	/*
	 On trigger trigger 2D method. 
	 This method is called if a trigger occurs. 

	 @param triggerInstance: To which instance the trigger was occurred.
	*/
	virtual void onTrigger_Trigger2D(DMKTriggerEntity2DInstance triggerInstance) {}

public:
	/* Trigger instances of this object. */
	ARRAY<DMKTriggerEntity2DInstance> triggerInstances;
};

#endif // !_DYNAMIK_TRIGGER_2D_H
