// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_MACROS_H
#define _DYNAMIK_VULKAN_BACKEND_MACROS_H

#include "Core/ErrorHandler/Logger.h"

/**
 * Vulkan Assert macro.
 * This checks if the return of an expression is equal to VK_SUCCESS.
 *
 * @param exp: The expression.
 * @msg: The message to be logged if failed.
 */
#define DMK_VK_ASSERT(exp, msg)	if (exp != VK_SUCCESS)	::DMK::Logger::LogError(TEXT(msg))

#endif // !_DYNAMIK_VULKAN_BACKEND_MACROS_H
