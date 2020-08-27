// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ERROR_DEFINES_H
#define _DYNAMIK_ERROR_DEFINES_H

/*
 This file contains all the error definitions and enums.
*/
#include "Core/Macros/Global.h"

/* All the message box types */
enum class DMK_API DMKMessageBoxType {
	DMK_MESSAGE_BOX_TYPE_INFO,
	DMK_MESSAGE_BOX_TYPE_WARN,
	DMK_MESSAGE_BOX_TYPE_QUESTION,
	DMK_MESSAGE_BOX_TYPE_ERROR,
};

/* All the supported user options */
enum class DMK_API UserOption {
	USER_OPTION_OK,
	USER_OPTION_RETRY,
	USER_OPTION_CANCEL,
	USER_OPTION_CONTINUE,
};

#endif // !_DYNAMIK_ERROR_DEFINES_H
