// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _ENGINE_DEV_KIT_INPUT_COMPONENT_H
#define _ENGINE_DEV_KIT_INPUT_COMPONENT_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Input type for the engine.
		 */
		enum class DMK_API InputType {
			INPUT_TYPE_FREE = BIT_SHIFT(0),
			INPUT_TYPE_PRESS = BIT_SHIFT(1),
			INPUT_TYPE_RELEASE = BIT_SHIFT(2),
			INPUT_TYPE_REPEAT = BIT_SHIFT(3),
		};

		/**
		 * Input category for the engine.
		 */
		enum class DMK_API InputCategory {
			INPUT_CATEGORY_KEY,
			INPUT_CATEGORY_APPLICATION,
			INPUT_CATEGORY_GAMEPAD,
			INPUT_CATEGORY_GESTURE,
			INPUT_CATEGORY_AXIS,
			INPUT_CATEGORY_FLOAT,
			INPUT_CATEGORY_BUTTON,
		};

		/**
		 * This structure holds information related to one single event.
		 */
		struct DMK_API InputComponent {
			/**
			 * Default constructor.
			 */
			InputComponent() {}

			/**
			 * Construct the input component using an input category.
			 *
			 * @param cat: The input category.
			 */
			InputComponent(InputCategory cat) : category(cat) {}

			/**
			 * Default virtual destructor.
			 */
			virtual ~InputComponent() {}

			/**
			 * Activate the input component.
			 *
			 * @param val: Value of the activation.
			 * @param ty: Type of the input.
			 */
			DMK_FORCEINLINE void Activate(float val, InputType ty) { value = val, type = ty; }

			/**
			 * Reset the input component.
			 */
			DMK_FORCEINLINE void Reset() { type = InputType::INPUT_TYPE_FREE; }

			/**
			 * Set a name for the input component.
			 *
			 * @param sName: The name to be set.
			 */
			DMK_FORCEINLINE void SetName(const STRING& sName) { name = sName; }

			/**
			 * Check if the input component is free.
			 */
			DMK_FORCEINLINE bool IsFree() const { return type == InputType::INPUT_TYPE_FREE || type == InputType::INPUT_TYPE_RELEASE; }

			/**
			 * Check if the input component contains a pressed input.
			 */
			DMK_FORCEINLINE bool IsPressed() const { return type == InputType::INPUT_TYPE_PRESS; }

			/**
			 * Check if the input component contains a repeated input.
			 */
			DMK_FORCEINLINE bool IsReleased() const { return type == InputType::INPUT_TYPE_RELEASE; }

			/**
			 * Check if the input component contains an on reapeat input.
			 */
			DMK_FORCEINLINE bool IsOnRepeat() const { return type == InputType::INPUT_TYPE_REPEAT; }

			/**
			 * Check if the input category is Key.
			 */
			DMK_FORCEINLINE bool IsCategoryKey() const { return category == InputCategory::INPUT_CATEGORY_KEY; }

			/**
			 * Check if the input category is Application.
			 */
			DMK_FORCEINLINE bool IsCategoryApplication() const { return category == InputCategory::INPUT_CATEGORY_APPLICATION; }

			/**
			 * Check if the input category is Gamepad.
			 */
			DMK_FORCEINLINE bool IsCategoryGamepad() const { return category == InputCategory::INPUT_CATEGORY_GAMEPAD; }

			/**
			 * Check if the input category is Gesture.
			 */
			DMK_FORCEINLINE bool IsCategoryGesture() const { return category == InputCategory::INPUT_CATEGORY_GESTURE; }

			/**
			 * Check if the input category is Axis.
			 */
			DMK_FORCEINLINE bool IsCategoryAxis() const { return category == InputCategory::INPUT_CATEGORY_AXIS; }

			/**
			 * Check if the input category is Float.
			 */
			DMK_FORCEINLINE bool IsCategoryFloat() const { return category == InputCategory::INPUT_CATEGORY_FLOAT; }

			/**
			 * Check if the input category is Button.
			 */
			DMK_FORCEINLINE bool IsCategoryButton() const { return category == InputCategory::INPUT_CATEGORY_BUTTON; }

			/**
			 * Operator to help retrieve the activation value.
			 */
			DMK_FORCEINLINE operator float() const { return value; }

			/**
			 * Operator to help retrieve the name of the input component.
			 */
			DMK_FORCEINLINE operator STRING() const { return name; }

			STRING name = TEXT("");
			InputCategory category = InputCategory::INPUT_CATEGORY_KEY;
			InputType type = InputType::INPUT_TYPE_FREE;
			float value = 0.0f;
		};

		/**
		 * Key input component.
		 */
		struct DMK_API KeyInputComponent : public InputComponent {
			/**
			 * Default constructor.
			 */
			KeyInputComponent() : InputComponent(InputCategory::INPUT_CATEGORY_KEY) {}

			/**
			 * Construct the key input component using the scan code.
			 *
			 * @param code: The scan code of the key.
			 */
			KeyInputComponent(UI32 code) : scanCode(code), InputComponent(InputCategory::INPUT_CATEGORY_KEY) {}

			/**
			 * Default destructor.
			 */
			~KeyInputComponent() {}

			/**
			 * Set the scan code of the key.
			 *
			 * @param code: The scan code of the key.
			 */
			DMK_FORCEINLINE void SetScanCode(UI32 code) { scanCode = code; }

			/**
			 * Is equal to operator.
			 *
			 * @param code: The scan code to be checked.
			 */
			bool operator==(const UI32& code) const { return scanCode == code; }

			UI32 scanCode = 0;
		};

		/**
		 * Button input component.
		 */
		struct DMK_API ButtonInputComponent : public InputComponent {
			/**
			 * Default constructor.
			 */
			ButtonInputComponent() : InputComponent(InputCategory::INPUT_CATEGORY_BUTTON) {}

			/**
			 * Construct the button input component using the button ID.
			 *
			 * @param ID: The button ID.
			 */
			ButtonInputComponent(UI32 ID) : buttonID(ID), InputComponent(InputCategory::INPUT_CATEGORY_BUTTON) {}

			/**
			 * Default destructor.
			 */
			~ButtonInputComponent() {}

			/**
			 * Set the button ID of the button input component.
			 *
			 * @param ID: The button ID.
			 */
			DMK_FORCEINLINE void SetButtonID(UI32 ID) { buttonID = ID; }

			UI32 buttonID = 0;
		};
	}
}

#endif // !_ENGINE_DEV_KIT_INPUT_COMPONENT_H
