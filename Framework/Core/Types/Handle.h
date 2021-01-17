// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "DataTypes.h"

#define DMK_DEFINE_UI64_HANDLE(name)	enum class name : UI64 { INVALID = 0Ui64 }

namespace DMK
{
	/**
	 * Create a new handle.
	 * 
	 * @tparam Handle: The handle type.
	 * @param handle: The handle data to be set.
	 * @return The created handle.
	 */
	template<class Handle>
	constexpr Handle CreateHandle(UI64 handle) { return static_cast<Handle>(handle); }

	/**
	 * Get data from the handle.
	 * 
	 * @tparam Handle: The handle type.
	 * @param handle: The handle to get the data from.
	 * @return The handle data as UI64.
	 */
	template<class Handle>
	constexpr UI64 GetHandle(const Handle& handle) { return static_cast<UI64>(handle); }

	/**
	 * Check if the handle is valid.
	 * 
	 * @tparam Handle: The handle type.
	 * @param handle: The handle to be checked.
	 * @return Boolean value.
	 */
	template<class Handle>
	bool IsValidHandle(const Handle& handle) { return handle != Handle::INVALID; }
}