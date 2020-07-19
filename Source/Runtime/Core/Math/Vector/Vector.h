// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VECTOR_BASE_H
#define _DYNAMIK_VECTOR_BASE_H

#include "Core/Macros/Global.h"
#include "Core/Types/Array.h"

namespace Dynamik
{
	/* Vector type traits */
	template <class TYPE>
	struct DMK_API VectorTraits;

	/*
	 Dynamik Math Vector Base class.
	*/
	template <class TYPE>
	class DMK_API Vector
	{
	public:
		typedef typename VectorTraits<TYPE>::type value_type;

		inline TYPE& operator()() { return *static_cast<TYPE*>(this); }
		inline const TYPE& operator()() const { return *static_cast<const TYPE*>(this); }

		inline TYPE& operator+=(const TYPE& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		inline TYPE& operator+=(const value_type& rhs)
		{
			(*this)() = (*this)() + TYPE(rhs);
			return (*this)();
		}

		inline TYPE operator++(int)
		{
			TYPE tmp = (*this)();
			(*this) += value_type(1);
			return tmp;
		}

		inline TYPE& operator++()
		{
			(*this)() += value_type(1);
			return (*this)();
		}

		inline TYPE& operator-=(const TYPE& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		inline TYPE& operator-=(const value_type& rhs)
		{
			(*this)() = (*this)() + TYPE(rhs);
			return (*this)();
		}

		inline TYPE operator--(int)
		{
			TYPE tmp = (*this)();
			(*this) -= value_type(1);
			return tmp;
		}

		inline TYPE& operator--()
		{
			(*this)() -= value_type(1);
			return (*this)();
		}

		inline Vector() {}
		inline ~Vector() {}

		inline Vector(const Vector&) {}
		inline Vector& operator=(const  Vector&) { return *this; }
	};

	/* Global operators for the derived classes */
	template <class TYPE>
	inline Vector<TYPE> operator+(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() + TYPE(rhs);
	}

	template <class TYPE>
	inline Vector<TYPE> operator+(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) + rhs();
	}

	template <class TYPE>
	inline Vector<TYPE> operator-(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() - TYPE(rhs);
	}

	template <class TYPE>
	inline Vector<TYPE> operator-(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) - rhs();
	}

	template <class TYPE>
	inline Vector<TYPE> operator*(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() * TYPE(rhs);
	}

	template <class TYPE>
	inline Vector<TYPE> operator*(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) * rhs();
	}

	template <class TYPE>
	inline Vector<TYPE> operator/(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() / TYPE(rhs);
	}

	template <class TYPE>
	inline Vector<TYPE> operator/(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) / rhs();
	}
}

#endif // !_DYNAMIK_VECTOR_BASE_H
