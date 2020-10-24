// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_MATRIX_H
#define _DYNAMIK_CORE_MATHS_MATRIX_H

namespace DMK
{
	/**
	 * This contains the base type of the matrix.
	 *
	 * @tparam TYPE: Primitive type of the matrix.
	 */
	template<class TYPE>
	struct MatrixTraits;

	/**
	 * Matrix data type for the Engine Dev Kit.
	 * This class contains all the common methods and operators all the other matrixes contain.
	 *
	 * @tparam TYPE: Matrix type.
	 */
	template<class TYPE>
	class Matrix
	{
	public:
		typedef typename MatrixTraits<TYPE>::type value_type;

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return: The matrix.
		 */
		inline TYPE& operator()() { return *static_cast<TYPE*>(this); }

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return: The const matrix.
		 */
		inline const TYPE& operator()() const { return *static_cast<const TYPE*>(this); }

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other matrix.
		 * @return: The incremented matrix.
		 */
		inline TYPE& operator+=(const TYPE& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other primitive matrix data.
		 * @return: The incremented matrix.
		 */
		inline TYPE& operator+=(const value_type& rhs)
		{
			(*this)() = (*this)() + TYPE(rhs);
			return (*this)();
		}

		/**
		 * Increment operator (by one).
		 *
		 * @param :
		 * @return: The incremented matrix.
		 */
		inline TYPE operator++(int)
		{
			TYPE tmp = (*this)();
			(*this) += value_type(1);
			return tmp;
		}

		/**
		 * Increment operator (by one).
		 *
		 * @param :
		 * @return: The incremented matrix.
		 */
		inline TYPE& operator++()
		{
			(*this)() += value_type(1);
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator-=(const TYPE& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator-=(const value_type& rhs)
		{
			(*this)() = (*this)() + TYPE(rhs);
			return (*this)();
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return: The decremented matrix.
		 */
		inline TYPE operator--(int)
		{
			TYPE tmp = (*this)();
			(*this) -= value_type(1);
			return tmp;
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator--()
		{
			(*this)() -= value_type(1);
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator*=(const TYPE& rhs)
		{
			(*this)() = (*this)() * rhs;
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator*=(const value_type& rhs)
		{
			(*this)() = (*this)() * TYPE(rhs);
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator/=(const TYPE& rhs)
		{
			(*this)() = (*this)() / rhs;
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return: The decremented matrix.
		 */
		inline TYPE& operator/=(const value_type& rhs)
		{
			(*this)() = (*this)() / TYPE(rhs);
			return (*this)();
		}

		/**
		 * Default constuctor.
		 */
		inline Matrix() {}

		/**
		 * Default destructor.
		 */
		inline ~Matrix() {}

		/**
		 * Construct the matrix using another matrix.
		 *
		 * @param : The other matrix.
		 */
		inline Matrix(const Matrix&) {}

		/**
		 * Return this matrix.
		 *
		 * @param :
		 * @return: This matrix.
		 */
		inline Matrix& operator=(const  Matrix&) { return *this; }

		static TYPE Identity;
	};

	/**
	 * Addition operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The added matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator+(const Matrix<TYPE>& lhs,
		const typename MatrixTraits<TYPE>::type& rhs)
	{
		return lhs() + TYPE(rhs);
	}

	/**
	 * Addition operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The added matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator+(const typename MatrixTraits<TYPE>::type& lhs,
		const Matrix<TYPE>& rhs)
	{
		return TYPE(lhs) + rhs();
	}

	/**
	 * Subtract operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The subracted matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator-(const Matrix<TYPE>& lhs,
		const typename MatrixTraits<TYPE>::type& rhs)
	{
		return lhs() - TYPE(rhs);
	}

	/**
	 * Subtract operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The subracted matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator-(const typename MatrixTraits<TYPE>::type& lhs,
		const Matrix<TYPE>& rhs)
	{
		return TYPE(lhs) - rhs();
	}

	/**
	 * Multiply operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The multiplied matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator*(const Matrix<TYPE>& lhs,
		const typename MatrixTraits<TYPE>::type& rhs)
	{
		return lhs() * TYPE(rhs);
	}

	/**
	 * Multiply operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The multiplied matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator*(const typename MatrixTraits<TYPE>::type& lhs,
		const Matrix<TYPE>& rhs)
	{
		return TYPE(lhs) * rhs();
	}

	/**
	 * Divide operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The divided matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator/(const Matrix<TYPE>& lhs,
		const typename MatrixTraits<TYPE>::type& rhs)
	{
		return lhs() / TYPE(rhs);
	}

	/**
	 * Divide operator of the matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The divided matrix.
	 */
	template <class TYPE>
	inline Matrix<TYPE> operator/(const typename MatrixTraits<TYPE>::type& lhs,
		const Matrix<TYPE>& rhs)
	{
		return TYPE(lhs) / rhs();
	}

	/**
	 * Initialize the matrix as an identity matrix.
	 *
	 * @tparam TYPE: The type of the matrix.
	 */
	template<class TYPE>
	TYPE Matrix<TYPE>::Identity = TYPE(1.0f);
}

#endif // !_DYNAMIK_CORE_MATHS_MATRIX_H
