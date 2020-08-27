// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_MACROS_H
#define _DYNAMIK_VULKAN_MACROS_H

/*
 This file contains all the necessry macros for the Vulkan RBL.
*/
#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.h>
#include "Core/Error/ErrorManager.h"

#define DMK_VULKAN_ASSERT(exp, msg) if(exp != VK_SUCCESS) DMK_ERROR_BOX(msg)

#endif // !_DYNAMIK_VULKAN_MACROS_H
