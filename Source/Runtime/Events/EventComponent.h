// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_EVENT_COMPONENT_H
#define _DYNAMIK_EVENT_COMPONENT_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace Dynamik
{
	/* Dynamik Event Type */
	enum DMK_API DMKEventType {
		DMK_EVENT_TYPE_FREE = BIT_SHIFT(0),
		DMK_EVENT_TYPE_PRESS = BIT_SHIFT(1),
		DMK_EVENT_TYPE_RELEASE = BIT_SHIFT(2),
		DMK_EVENT_TYPE_REPEAT = BIT_SHIFT(3),
	};

	/* Dynamik Event Category */
	enum class DMK_API DMKEventCategory {
		DMK_EVENT_CATEGORY_KEY,
		DMK_EVENT_CATEGORY_APPLICATION,
		DMK_EVENT_CATEGORY_GAMEPAD,
		DMK_EVENT_CATEGORY_GESTURE,
		DMK_EVENT_CATEGORY_AXIS,
		DMK_EVENT_CATEGORY_FLOAT,
		DMK_EVENT_CATEGORY_BUTTON,
	};

	/*
	 Dynamik Event Component
	 This structure holds information related to one single event.
	*/
	struct DMK_API DMKEventComponent {
		DMKEventComponent() {}
		DMKEventComponent(DMKEventCategory cat) : category(cat) {}
		virtual ~DMKEventComponent() {}

		DMK_FORCEINLINE void activate(F32 val, DMKEventType ty) { value = val, type = ty; }
		DMK_FORCEINLINE void reset() { type = DMKEventType::DMK_EVENT_TYPE_FREE; }
		DMK_FORCEINLINE void setName(const STRING& sName) { name = sName; }

		DMK_FORCEINLINE B1 isFree() const { return type == DMKEventType::DMK_EVENT_TYPE_FREE || type == DMKEventType::DMK_EVENT_TYPE_RELEASE; }
		DMK_FORCEINLINE B1 isPressed() const { return type == DMKEventType::DMK_EVENT_TYPE_PRESS; }
		DMK_FORCEINLINE B1 isReleased() const { return type == DMKEventType::DMK_EVENT_TYPE_RELEASE; }
		DMK_FORCEINLINE B1 isOnRepeat() const { return type == DMKEventType::DMK_EVENT_TYPE_REPEAT; }

		DMK_FORCEINLINE B1 isCategoryKey() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_KEY; }
		DMK_FORCEINLINE B1 isCategoryApplication() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_APPLICATION; }
		DMK_FORCEINLINE B1 isCategoryGamepad() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_GAMEPAD; }
		DMK_FORCEINLINE B1 isCategoryGesture() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_GESTURE; }
		DMK_FORCEINLINE B1 isCategoryAxis() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_AXIS; }
		DMK_FORCEINLINE B1 isCategoryFloat() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_FLOAT; }
		DMK_FORCEINLINE B1 isCategoryButton() const { return category == DMKEventCategory::DMK_EVENT_CATEGORY_BUTTON; }

		DMK_FORCEINLINE operator F32() const { return value; }
		DMK_FORCEINLINE operator STRING() const { return name; }

		STRING name = DMK_TEXT("");
		DMKEventCategory category = DMKEventCategory::DMK_EVENT_CATEGORY_KEY;
		DMKEventType type = DMKEventType::DMK_EVENT_TYPE_FREE;
		F32 value = 0.0f;
	};

	/*
	 Dynamik Key Event Component
	*/
	struct DMK_API DMKKeyEventComponent : public DMKEventComponent {
		DMKKeyEventComponent() : DMKEventComponent(DMKEventCategory::DMK_EVENT_CATEGORY_KEY) {}
		DMKKeyEventComponent(UI32 code) : scanCode(code), DMKEventComponent(DMKEventCategory::DMK_EVENT_CATEGORY_KEY) {}
		~DMKKeyEventComponent() {}

		DMK_FORCEINLINE void setScanCode(UI32 code) { scanCode = code; }

		B1 operator==(const UI32& code) const { return scanCode == code; }

		UI32 scanCode = 0;
	};

	/*
	 Dynamik Button Event Component
	*/
	struct DMK_API DMKButtonEventComponent : DMKEventComponent {
		DMKButtonEventComponent() : DMKEventComponent(DMKEventCategory::DMK_EVENT_CATEGORY_BUTTON) {}
		DMKButtonEventComponent(UI32 ID) : buttonID(ID), DMKEventComponent(DMKEventCategory::DMK_EVENT_CATEGORY_BUTTON) {}
		~DMKButtonEventComponent() {}

		DMK_FORCEINLINE void setButtonID(UI32 ID) { buttonID = ID; }

		UI32 buttonID = 0;
	};
}

#endif // !_DYNAMIK_EVENT_COMPONENT_H
