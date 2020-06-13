// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_MACROS_H
#define _DYNAMIK_VULKAN_MACROS_H

/*
 Author:    Dhiraj Wishal
 Date:      26/05/2020

 This file contains all the necessry macros for the Vulkan RBL.
*/
#include <vulkan/vulkan.h>
#include "Error/ErrorManager.h"

#define DMK_VULKAN_ASSERT(exp, msg) if(exp != VK_SUCCESS) DMK_ERROR_BOX(msg)

#endif // !_DYNAMIK_VULKAN_MACROS_H
