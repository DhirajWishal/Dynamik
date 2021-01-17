// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "Core/Types/Utilities.h"

#include <codecvt>

namespace DMK
{
	std::string WStringToString(const std::wstring& string)
	{
		std::wstring_convert<std::codecvt_utf8<wchar>, wchar> convert;
		return convert.to_bytes(string);
	}

	std::wstring StringToWString(const std::string& string)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar>, wchar> convert;
		return convert.from_bytes(string);
	}
}