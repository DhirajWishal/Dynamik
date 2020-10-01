// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "TriggerEntity2D.h"

void DMKTriggerEntity2D::addInstanceTrigger2D(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale)
{
	triggerInstances.push_back(DMKTriggerEntity2DInstance(name, position, rotation, scale, this, Cast<UI32>(triggerInstances.size())));
}
