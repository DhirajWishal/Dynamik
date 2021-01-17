// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace DMK
{
	/**
	 * This contains the base type of the matrix.
	 *
	 * @tparam Type: Primitive type of the matrix.
	 */
	template<class Type>
	struct MatrixTraits;

	/**
	 * Matrix data type for the Engine Dev Kit.
	 * This class contains all the common methods and operators all the other matrixes contain.
	 *
	 * @tparam Type: Matrix type.
	 */
	template<class Type>
	class Matrix
	{
	public:
		typedef typename MatrixTraits<Type>::type value_type;

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return The matrix.
		 */
		inline Type& operator()() { return *static_cast<Type*>(this); }

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return The const matrix.
		 */
		inline const Type& operator()() const { return *static_cast<const Type*>(this); }

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other matrix.
		 * @return The incremented matrix.
		 */
		inline Type& operator+=(const Type& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other primitive matrix data.
		 * @return The incremented matrix.
		 */
		inline Type& operator+=(const value_type& rhs)
		{
			(*this)() = (*this)() + Type(rhs);
			return (*this)();
		}

		/**
		 * Increment operator (by one).
		 *
		 * @param :
		 * @return The incremented matrix.
		 */
		inline Type operator++(int)
		{
			Type tmp = (*this)();
			(*this) += value_type(1);
			return tmp;
		}

		/**
		 * Increment operator (by one).
		 *
		 * @param :
		 * @return The incremented matrix.
		 */
		inline Type& operator++()
		{
			(*this)() += value_type(1);
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator-=(const Type& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator-=(const value_type& rhs)
		{
			(*this)() = (*this)() + Type(rhs);
			return (*this)();
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return The decremented matrix.
		 */
		inline Type operator--(int)
		{
			Type tmp = (*this)();
			(*this) -= value_type(1);
			return tmp;
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return The decremented matrix.
		 */
		inline Type& operator--()
		{
			(*this)() -= value_type(1);
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator*=(const Type& rhs)
		{
			(*this)() = (*this)() * rhs;
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator*=(const value_type& rhs)
		{
			(*this)() = (*this)() * Type(rhs);
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator/=(const Type& rhs)
		{
			(*this)() = (*this)() / rhs;
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other matrix to be decremented by.
		 * @return The decremented matrix.
		 */
		inline Type& operator/=(const value_type& rhs)
		{
			(*this)() = (*this)() / Type(rhs);
			return (*this)();
		}

		inline Matrix() {}
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
		 * @return This matrix.
		 */
		inline Matrix& operator=(const  Matrix&) { return *this; }

		static Type Identity;
	};

	/**
	 * Addition operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The added matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator+(const Matrix<Type>& lhs,
		const typename MatrixTraits<Type>::type& rhs)
	{
		return lhs() + Type(rhs);
	}

	/**
	 * Addition operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The added matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator+(const typename MatrixTraits<Type>::type& lhs,
		const Matrix<Type>& rhs)
	{
		return Type(lhs) + rhs();
	}

	/**
	 * Subtract operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The subracted matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator-(const Matrix<Type>& lhs,
		const typename MatrixTraits<Type>::type& rhs)
	{
		return lhs() - Type(rhs);
	}

	/**
	 * Subtract operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The subracted matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator-(const typename MatrixTraits<Type>::type& lhs,
		const Matrix<Type>& rhs)
	{
		return Type(lhs) - rhs();
	}

	/**
	 * Multiply operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The multiplied matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator*(const Matrix<Type>& lhs,
		const typename MatrixTraits<Type>::type& rhs)
	{
		return lhs() * Type(rhs);
	}

	/**
	 * Multiply operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The multiplied matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator*(const typename MatrixTraits<Type>::type& lhs,
		const Matrix<Type>& rhs)
	{
		return Type(lhs) * rhs();
	}

	/**
	 * Divide operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The divided matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator/(const Matrix<Type>& lhs,
		const typename MatrixTraits<Type>::type& rhs)
	{
		return lhs() / Type(rhs);
	}

	/**
	 * Divide operator of the matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The divided matrix.
	 */
	template <class Type>
	inline Matrix<Type> operator/(const typename MatrixTraits<Type>::type& lhs,
		const Matrix<Type>& rhs)
	{
		return Type(lhs) / rhs();
	}

	/**
	 * Initialize the matrix as an identity matrix.
	 *
	 * @tparam Type: The type of the matrix.
	 */
	template<class Type>
	Type Matrix<Type>::Identity = Type(1.0f);
}
