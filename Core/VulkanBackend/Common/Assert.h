// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_BACKEND_ASSERT_H
#define _DYNAMIK_VULKAN_BACKEND_ASSERT_H

#include "ErrorHandler/Logger.h"

/**
 * Assert if the vulkan result is not equal to VK_SUCCESS.
 * 
 * @param exp: The expression.
 * @param msg: Message to be displayed if the assertion failed. 
 */
#define DMK_VULKAN_ASSERT(exp, msg) if(exp != VK_SUCCESS) ::DMK::ErrorHandler::Logger::LogError(TEXT(msg))

#endif // !_DYNAMIK_VULKAN_BACKEND_ASSERT_H
