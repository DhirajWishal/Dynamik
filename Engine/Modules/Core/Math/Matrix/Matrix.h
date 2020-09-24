// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATRIX_H
#define _DYNAMIK_MATRIX_H

#include "Core/Macros/Global.h"
#include "Core/Types/DataTypes.h"

template<class TYPE>
struct MatrixTraits;

/*
 Matrix data type for the Dynamik Engine.
*/
template<class TYPE>
class DMK_API Matrix
{
public:
	typedef typename MatrixTraits<TYPE>::type value_type;

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

	inline TYPE& operator*=(const TYPE& rhs)
	{
		(*this)() = (*this)() * rhs;
		return (*this)();
	}

	inline TYPE& operator*=(const value_type& rhs)
	{
		(*this)() = (*this)() * TYPE(rhs);
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

	inline TYPE& operator/=(const TYPE& rhs)
	{
		(*this)() = (*this)() / rhs;
		return (*this)();
	}

	inline TYPE& operator/=(const value_type& rhs)
	{
		(*this)() = (*this)() / TYPE(rhs);
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

protected:
	inline Matrix() {}
	inline ~Matrix() {}

	inline Matrix(const Matrix&) {}
	inline Matrix& operator=(const  Matrix&) { return *this; }
};

/* Global operators for the derived classes */
template <class TYPE>
inline Matrix<TYPE> operator+(const Matrix<TYPE>& lhs,
	const typename MatrixTraits<TYPE>::type& rhs)
{
	return lhs() + TYPE(rhs);
}

template <class TYPE>
inline Matrix<TYPE> operator+(const typename MatrixTraits<TYPE>::type& lhs,
	const Matrix<TYPE>& rhs)
{
	return TYPE(lhs) + rhs();
}

template <class TYPE>
inline Matrix<TYPE> operator-(const Matrix<TYPE>& lhs,
	const typename MatrixTraits<TYPE>::type& rhs)
{
	return lhs() - TYPE(rhs);
}

template <class TYPE>
inline Matrix<TYPE> operator-(const typename MatrixTraits<TYPE>::type& lhs,
	const Matrix<TYPE>& rhs)
{
	return TYPE(lhs) - rhs();
}

template <class TYPE>
inline Matrix<TYPE> operator*(const Matrix<TYPE>& lhs,
	const typename MatrixTraits<TYPE>::type& rhs)
{
	return lhs() * TYPE(rhs);
}

template <class TYPE>
inline Matrix<TYPE> operator*(const typename MatrixTraits<TYPE>::type& lhs,
	const Matrix<TYPE>& rhs)
{
	return TYPE(lhs) * rhs();
}

template <class TYPE>
inline Matrix<TYPE> operator/(const Matrix<TYPE>& lhs,
	const typename MatrixTraits<TYPE>::type& rhs)
{
	return lhs() / TYPE(rhs);
}

template <class TYPE>
inline Matrix<TYPE> operator/(const typename MatrixTraits<TYPE>::type& lhs,
	const Matrix<TYPE>& rhs)
{
	return TYPE(lhs) / rhs();
}

#endif // !_DYNAMIK_MATRIX_H
