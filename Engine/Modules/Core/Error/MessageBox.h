// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_ERROR_MESSAGE_BOX_H
#define _DYNAMIK_ERROR_MESSAGE_BOX_H

/*
 Error message box for the Dynamik Engine.
 This object is platform specific.
*/

#include <vector>
#include "ErrorDefines.h"

/*
 This class is used to issue a message box to the user. This may range from information, to error.
 This is a utility object for the Dynamik Engine.
*/
class DMK_API DMKMessageBox {
public:
	DMKMessageBox(STRING title, STRING message, DMKMessageBoxType ty);
	~DMKMessageBox();

	UserOption issueBox(UI32 defaultButton = 0);

private:
	STRING title = "";
	STRING message = "";
	DMKMessageBoxType type = DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_INFO;
};

#endif // !_DYNAMIK_ERROR_MESSAGE_BOX_H
