// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INPUTS_MOUSE_INPUT_SUPPLIER_H
#define _DYNAMIK_INPUTS_MOUSE_INPUT_SUPPLIER_H

#include "InputSupplier.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Button Input Type enum.
		 * The button is activated using 3 types,
		 * - Press (When the user presses a button)
		 * - Release (When the user unclicks the button)
		 * - Repeat (When the user keeps on pressing the buttom)
		 */
		enum class ButtonInputType : UI32 {
			BUTTON_INPUT_Type_PRESS,
			BUTTON_INPUT_Type_RELEASE,
			BUTTON_INPUT_Type_REPEAT,
		};

		/**
		 * Button structure to hold the button information of the input.
		 */
		struct Button {
			/**
			 * Default constructor.
			 */
			Button() = default;

			/**
			 * Construct the button using its scan code.
			 *
			 * @param scanCode: The scan code of the button.
			 */
			Button(UI32 scanCode) : scanCode(scanCode) {}

			UI32 scanCode = 0;	// Scan code of the button.
			ButtonInputType eInputType = ButtonInputType::BUTTON_INPUT_Type_RELEASE;	// Input type/ activation of the button.
		};

		/**
		 * Scroll structure to hold the information about the mouse scroll.
		 */
		struct Scroll {
			/**
			 * Default constructor.
			 */
			Scroll() = default;

			/**
			 * Set the scroll value.
			 *
			 * @param value: The value to be set.
			 */
			void SetValue(float value) { this->value = value; }

			/**
			 * Get the scroll value.
			 *
			 * @return: Float value.
			 */
			float GetValue() const { return value; }

			float value = 0.0f;	// Scroll value. 
		};

		/**
		 * Position structure to store the mouse cursor position.
		 */
		struct Position {
			/**
			 * Default constructor.
			 */
			Position() = default;

			/**
			 * Set the position of the mouse cursor.
			 *
			 * @param xOffset: The location of the cursor in screen coordinates (x axis).
			 * @param yOffset: The location of the cursor in screen coordinates (y axis).
			 */
			void SetPosition(float xOffset, float yOffset) { this->xOffset = xOffset, this->yOffset = yOffset; }

			/**
			 * Get the position of the cursor.
			 *
			 * @return: std::pair<float, float> structure containing the position.
			 */
			std::pair<float, float> GetPosition() const { return { xOffset, yOffset }; }

			float xOffset = 0.0f, yOffset = 0.0f;	// Location in screen coordinates.
		};

		/**
		 * Mouse Input Supplier for the Dynamik Enigne.
		 * This supplier provides mouse inputs to the engine.
		 */
		class MouseInputSupplier : public InputSupplier {
		public:
			/**
			 * Default constructor.
			 */
			MouseInputSupplier() : InputSupplier("MouseInputSupplier") {}

			/**
			 * Default destructor.
			 */
			virtual ~MouseInputSupplier() {}

			/* All supported mouse inputs. */
		public:
			Button ButtonLeft = {};
			Button ButtonRight = {};
			Button ButtonModdle = {};
			Button Button0 = {};
			Button Button1 = {};

			Scroll Scroller = {};

			Position CursorPosition = {};
		};
	}
}

#endif // !_DYNAMIK_INPUTS_MOUSE_INPUT_SUPPLIER_H
