// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MessageBox.h"

#ifdef DMK_PLATFORM_WINDOWS
#include <Windows.h>

#endif

namespace Dynamik
{
	DMKMessageBox::DMKMessageBox(STRING title, STRING message, DMKMessageBoxType ty)
		: title(title), message(message), type(ty)
	{
	}

	DMKMessageBox::~DMKMessageBox()
	{
	}

	UserOption DMKMessageBox::issueBox(UI32 defaultButton)
	{
		auto _flags = 0;

		switch (type)
		{
		case Dynamik::DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_INFO:
			_flags = MB_ICONINFORMATION | MB_OK;
			break;
		case Dynamik::DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_WARN:
			_flags = MB_ICONWARNING | MB_OKCANCEL;
			break;
		case Dynamik::DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_QUESTION:
			_flags = MB_ICONQUESTION | MB_OKCANCEL;
			break;
		case Dynamik::DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_ERROR:
			_flags = MB_ICONERROR | MB_CANCELTRYCONTINUE;
			break;
		default:
			_flags = MB_ICONINFORMATION | MB_OK;
			break;
		}

		switch (defaultButton)
		{
		case 1:
			_flags = _flags | MB_DEFBUTTON1;
			break;
		case 2:
			_flags = _flags | MB_DEFBUTTON2;
			break;
		case 3:
			_flags = _flags | MB_DEFBUTTON3;
			break;
		case 4:
			_flags = _flags | MB_DEFBUTTON4;
			break;
		}

#ifdef DMK_USE_WIDE_CHAR
		switch (MessageBoxW(NULL, (LPWSTR)message.c_str(), (LPWSTR)title.c_str(), _flags))
		{

#else
		switch (MessageBoxA(NULL, (LPSTR)message.c_str(), (LPSTR)title.c_str(), _flags))
		{

#endif
		case IDCANCEL:
			return UserOption::USER_OPTION_CANCEL;
			break;
		case IDTRYAGAIN:
			return UserOption::USER_OPTION_RETRY;
#ifdef DMK_DEBUG
			if (type == DMKMessageBoxType::DMK_MESSAGE_BOX_TYPE_ERROR)
				__debugbreak();

#endif // DMK_DEBUG

			break;
		case IDCONTINUE:
			return UserOption::USER_OPTION_CONTINUE;
			break;
		case IDOK:
			return UserOption::USER_OPTION_OK;
			break;
		}

		return UserOption::USER_OPTION_OK;
	}
}