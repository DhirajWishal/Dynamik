// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Inputs/InputCenter.h"
#include "Core/ErrorHandler/Logger.h"
#include "Core/Types/Utilities.h"
#include "Core/Types/DataTypes.h"

namespace DMK
{
	namespace Inputs
	{
		void InputCenter::AddKeyInputSupplier(KeyInputSupplier* pKeyInputSupplier)
		{
			// Check if the supplier is valid.
			if (!pKeyInputSupplier)
			{
				Logger::LogError(TEXT("Invalid key input supplier pointer."));
				return;
			}

			// Check if the supplier is already stored.
			if (pInputSuppliers[pKeyInputSupplier->GetName()])
			{
				Logger::LogError(TEXT("Key input supplier is already available."));
				return;
			}

			// Call the on initialize method.
			pKeyInputSupplier->OnInitializeSupplier();

			// Add the key input supplier pointer.
			pInputSuppliers[pKeyInputSupplier->GetName()] = pKeyInputSupplier;
		}

		void InputCenter::AddMouseInputSupplier(MouseInputSupplier* pMouseInputSupplier)
		{
			// Check if the supplier is valid.
			if (!pMouseInputSupplier)
			{
				Logger::LogError(TEXT("Invalid mouse input supplier pointer."));
				return;
			}

			// Check if the supplier is already stored.
			if (pInputSuppliers[pMouseInputSupplier->GetName()])
			{
				Logger::LogError(TEXT("Mouse input supplier is already available."));
				return;
			}

			// Call the on initialize method.
			pMouseInputSupplier->OnInitializeSupplier();

			// Add the mouse input supplier pointer.
			pInputSuppliers[pMouseInputSupplier->GetName()] = pMouseInputSupplier;
		}

		void InputCenter::Update()
		{
			// Update the suppliers.
			for (auto itr = pInputSuppliers.begin(); itr != pInputSuppliers.end(); itr++)
				itr->second->OnUpdateSupplier();
		}

		InputSupplier* InputCenter::GetSupplier(const String& sName) const
		{
			auto pSupplier = pInputSuppliers.at(sName);

			// Check and warn if the supplier is not available.
			if (!pSupplier)
				Logger::LogError(TEXT("Requested supplier is not submitted/ available!"));

			return pSupplier;
		}
	}
}