// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_INPUT_SUPPLIER_H
#define _DYNAMIK_INPUT_SUPPLIER_H

#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Inputs
	{
		/**
		 * Input supplier base class for the Dynamik Enigne.
		 * Inputs for the engine is handled by the input center using input suppliers. Suppliers provide inputs
		 * to the center.
		 */
		class InputSupplier {
		public:
			/**
			 * Default constructor.
			 *
			 * @param sName: The name of the supplier.
			 */
			InputSupplier(const CHR* sName) : pSupplierName(sName) {}

			/**
			 * Default destructor.
			 */
			virtual ~InputSupplier() {}

			/**
			 * Get the supplier name.
			 *
			 * @return: const CHR pointer of the name.
			 */
			const CHR* GetName() const { return pSupplierName; }

			/**
			 * On Initialize method which is used to initialize the supplier. This is called as soon as the supplier
			 * is attached to the input center.
			 */
			virtual void OnInitializeSupplier() = 0;

			/**
			 * On Update method which is used to update the supplier. Usually input polling is done in this.
			 */
			virtual void OnUpdateSupplier() = 0;

			/**
			 * On Terminate method. This is called once the supplier is detached.
			 */
			virtual void OnTerminateSupplier() = 0;

		protected:
			/**
			 * Suppliers contains a unique name which is used to identify them.
			 */
			const CHR* pSupplierName = TEXT("");
		};
	}
}

#endif // !_DYNAMIK_INPUT_SUPPLIER_H
