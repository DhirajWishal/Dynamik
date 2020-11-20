// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

namespace DMK
{
	/**
	 * This contains the base type of the vector.
	 *
	 * @tparam Type: Primitive type of the vector.
	 */
	template<class Type>
	struct VectorTraits {};

	/**
	 * Vector base class for the DMK Math types.
	 * This class contains all the common methods and operators all the other vectors contain.
	 *
	 * @tparam Type: Vector Type.
	 */
	template<class Type>
	class Vector {
	public:
		typedef typename VectorTraits<Type>::type value_type;

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return The vector.
		 */
		inline Type& operator()() { return *static_cast<Type*>(this); }

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return The const vector.
		 */
		inline const Type& operator()() const { return *static_cast<const Type*>(this); }

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other vector.
		 * @return The incremented vector.
		 */
		inline Type& operator+=(const Type& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other primitive vector data.
		 * @return The incremented vector.
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
		 * @return The incremented vector.
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
		 * @return The incremented vector.
		 */
		inline Type& operator++()
		{
			(*this)() += value_type(1);
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator-=(const Type& rhs)
		{
			(*this)() = (*this)() - rhs;
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator-=(const value_type& rhs)
		{
			(*this)() = (*this)() - Type(rhs);
			return (*this)();
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return The decremented vector.
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
		 * @return The decremented vector.
		 */
		inline Type& operator--()
		{
			(*this)() -= value_type(1);
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator*=(const Type& rhs)
		{
			(*this)() = (*this)() * rhs;
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator*=(const value_type& rhs)
		{
			(*this)() = (*this)() * Type(rhs);
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator/=(const Type& rhs)
		{
			(*this)() = (*this)() / rhs;
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return The decremented vector.
		 */
		inline Type& operator/=(const value_type& rhs)
		{
			(*this)() = (*this)() / Type(rhs);
			return (*this)();
		}

		/**
		 * Default constuctor.
		 */
		inline Vector() {}

		/**
		 * Default destructor.
		 */
		inline ~Vector() {}

		/**
		 * Construct the vector using another vector.
		 *
		 * @param : The other vector.
		 */
		inline Vector(const Vector&) {}

		/**
		 * Return this vector.
		 *
		 * @param :
		 * @return This vector.
		 */
		inline Vector& operator=(const  Vector&) { return *this; }

		static Type ZeroAll;
	};

	/**
	 * Addition operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The added vector.
	 */
	template <class Type>
	inline Vector<Type> operator+(const Vector<Type>& lhs,
		const typename VectorTraits<Type>::type& rhs)
	{
		return lhs() + Type(rhs);
	}

	/**
	 * Addition operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The added vector.
	 */
	template <class Type>
	inline Vector<Type> operator+(const typename VectorTraits<Type>::type& lhs,
		const Vector<Type>& rhs)
	{
		return Type(lhs) + rhs();
	}

	/**
	 * Subtract operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The subracted vector.
	 */
	template <class Type>
	inline Vector<Type> operator-(const Vector<Type>& lhs,
		const typename VectorTraits<Type>::type& rhs)
	{
		return lhs() - Type(rhs);
	}

	/**
	 * Subtract operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The subracted vector.
	 */
	template <class Type>
	inline Vector<Type> operator-(const typename VectorTraits<Type>::type& lhs,
		const Vector<Type>& rhs)
	{
		return Type(lhs) - rhs();
	}

	/**
	 * Multiply operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The multiplied vector.
	 */
	template <class Type>
	inline Vector<Type> operator*(const Vector<Type>& lhs,
		const typename VectorTraits<Type>::type& rhs)
	{
		return lhs() * Type(rhs);
	}

	/**
	 * Multiply operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The multiplied vector.
	 */
	template <class Type>
	inline Vector<Type> operator*(const typename VectorTraits<Type>::type& lhs,
		const Vector<Type>& rhs)
	{
		return Type(lhs) * rhs();
	}

	/**
	 * Divide operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The divided vector.
	 */
	template <class Type>
	inline Vector<Type> operator/(const Vector<Type>& lhs,
		const typename VectorTraits<Type>::type& rhs)
	{
		return lhs() / Type(rhs);
	}

	/**
	 * Divide operator of the vector.
	 *
	 * @tparam Type: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return The divided vector.
	 */
	template <class Type>
	inline Vector<Type> operator/(const typename VectorTraits<Type>::type& lhs,
		const Vector<Type>& rhs)
	{
		return Type(lhs) / rhs();
	}

	/**
	 * Zero all the values in the vector.
	 *
	 * @tparam Type: The type of the vector.
	 */
	template<class Type>
	Type Vector<Type>::ZeroAll = Type(0.0f);
}
