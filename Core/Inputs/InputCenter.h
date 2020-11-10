// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INPUT_CENTER_H
#define _DYNAMIK_INPUT_CENTER_H

#include "Suppliers/KeyInputSupplier.h"
#include "Suppliers/MouseInputSupplier.h"

#include <vector>

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Centralized object which handles inputs for the Dynamik Engine.
		 */
		class InputCenter {
		public:
			/**
			 * Default constructor.
			 */
			InputCenter() {}

			/**
			 * Default destructor.
			 */
			~InputCenter() {}

			/**
			 * Add a key input supplier to the input center.
			 *
			 * @param pKeyInputSupplier: The pointer to the key input supplier.
			 */
			void AddKeyInputSupplier(KeyInputSupplier* pKeyInputSupplier);

			/**
			 * Add a mouse input supplier to the input center.
			 *
			 * @param pMouseInputSupplier: The pointer to the mouse input supplier.
			 */
			void AddMouseInputSupplier(MouseInputSupplier* pMouseInputSupplier);

			/**
			 * Update all the input suppliers of the center.
			 */
			void Update();

			/**
			 * Get a supplier using its name.
			 *
			 * @param sName: The name of the supplier.
			 * @return The pointer of the supplier.
			 */
			InputSupplier* GetSupplier(const String& sName) const;

		private:
			std::unordered_map<String, InputSupplier*> pInputSuppliers;	// Container of input supplier pointers.
		};
	}
}

#endif // !_DYNAMIK_INPUT_CENTER_H
