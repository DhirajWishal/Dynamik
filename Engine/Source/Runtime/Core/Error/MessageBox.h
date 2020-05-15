#pragma once
#ifndef _DYNAMIK_ERROR_MESSAGE_BOX_H
#define _DYNAMIK_ERROR_MESSAGE_BOX_H

/*
 Error message box for the Dynamik Engine.
 This object is platform specific.

 Author:    Dhiraj Wishal
 Date:      15/5/2020
*/

#include "Object/Utility.h"
#include "../Types/Array.h"
#include "ErrorDefines.h"

namespace Dynamik
{
    /*
     This class is used to issue a message box to the user. This may range from information, to error.
     This is a utility object for the Dynamik Engine.
    */
    DMK_ALIGN class DMK_API DMKMessageBox : public DMKUtility {
    public:
        DMKMessageBox(STRING title, STRING message, DMKMessageBoxType ty);
        ~DMKMessageBox();

        UserOption issueBox(UI32 defaultButton = 0);

    private:
        STRING title = "";
        STRING message = "";
        DMKMessageBoxType type = DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_INFO;
    };
}

#endif // !_DYNAMIK_ERROR_MESSAGE_BOX_H
