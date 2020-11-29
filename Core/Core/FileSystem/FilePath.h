// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "Core/Types/DataTypes.h"
#include <type_traits>

namespace DMK
{
	/**
	 * File path object.
	 * This object holds information about a file path as a char pointer or as a wchar pointer.
	 */
	template<class Type = wchar>
	class FilePath {
		/**
		 * Check if the base type is accepted.
		 */
		static_assert(
			std::is_same<Type, char>::value || std::is_same<Type, wchar>::value,
			"Invalid File Path base type! The object only alows char or wchar_t as the base type."
			);

		using Char = Type;
		using StringT = std::basic_string<Char>;
	public:
		/**
		 * Default constructor.
		 */
		FilePath() = default;

		/**
		 * Construct the object using the file path.
		 *
		 * @param pPath: The path to be stored.
		 */
		FilePath(const Char* pPath) : pString(pPath) {}

		/**
		 * Copy constructor.
		 *
		 * @param fPath: The other file path object.
		 */
		FilePath(const FilePath& fPath) : pString(fPath.pString) {}

		/**
		 * Move constructor.
		 *
		 * @param fPath: The other file path object.
		 */
		FilePath(const FilePath&& fPath) : pString(fPath.pString)
		{
			// Clear the data of the other string.
			fPath.pString = nullptr;
		}

		/**
		 * Default destructor.
		 */
		~FilePath() {}

		/**
		 * Get the extension of the file path if specified.
		 *
		 * @return Char pointer.
		 */
		Char* GetExtension()
		{
			StringT(pString).find_first_of(".");
		}

		/**
		 * Check if the stored string has data or not.
		 *
		 * @return Boolean value.
		 */
		bool HasValue() const { return pString != nullptr; }

		/**
		 * Get the string stored in the object as a std::basic_string<Char> type.
		 *
		 * @return StringT object with the string data.
		 */
		StringT GetAsStringType() const { return StringT(pString); }

	private:
		Char* pString = nullptr;	// The string path.
	};
}