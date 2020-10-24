// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_CORE_MATHS_VECTOR_H
#define _DYNAMIK_CORE_MATHS_VECTOR_H

namespace DMK
{
	/**
	 * This contains the base type of the vector.
	 *
	 * @tparam TYPE: Primitive type of the vector.
	 */
	template<class TYPE>
	struct VectorTraits {};

	/**
	 * Vector base class for the DMK Math types.
	 * This class contains all the common methods and operators all the other vectors contain.
	 *
	 * @tparam TYPE: Vector Type.
	 */
	template<class TYPE>
	class Vector {
	public:
		typedef typename VectorTraits<TYPE>::type value_type;

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return: The vector.
		 */
		inline TYPE& operator()() { return *static_cast<TYPE*>(this); }

		/**
		 * Dereference operator to return the primitive type data.
		 *
		 * @return: The const vector.
		 */
		inline const TYPE& operator()() const { return *static_cast<const TYPE*>(this); }

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other vector.
		 * @return: The incremented vector.
		 */
		inline TYPE& operator+=(const TYPE& rhs)
		{
			(*this)() = (*this)() + rhs;
			return (*this)();
		}

		/**
		 * Increment operator.
		 *
		 * @param rhs: The other primitive vector data.
		 * @return: The incremented vector.
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
		 * @return: The incremented vector.
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
		 * @return: The incremented vector.
		 */
		inline TYPE& operator++()
		{
			(*this)() += value_type(1);
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator-=(const TYPE& rhs)
		{
			(*this)() = (*this)() - rhs;
			return (*this)();
		}

		/**
		 * The decrement operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator-=(const value_type& rhs)
		{
			(*this)() = (*this)() - TYPE(rhs);
			return (*this)();
		}

		/**
		 * Decrement operator (by one).
		 *
		 * @param :
		 * @return: The decremented vector.
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
		 * @return: The decremented vector.
		 */
		inline TYPE& operator--()
		{
			(*this)() -= value_type(1);
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator*=(const TYPE& rhs)
		{
			(*this)() = (*this)() * rhs;
			return (*this)();
		}

		/**
		 * The multiplication operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator*=(const value_type& rhs)
		{
			(*this)() = (*this)() * TYPE(rhs);
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator/=(const TYPE& rhs)
		{
			(*this)() = (*this)() / rhs;
			return (*this)();
		}

		/**
		 * The division operator.
		 *
		 * @param rhs: The other vector to be decremented by.
		 * @return: The decremented vector.
		 */
		inline TYPE& operator/=(const value_type& rhs)
		{
			(*this)() = (*this)() / TYPE(rhs);
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
		 * @return: This vector.
		 */
		inline Vector& operator=(const  Vector&) { return *this; }

		static TYPE ZeroAll;
	};

	/**
	 * Addition operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The added vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator+(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() + TYPE(rhs);
	}

	/**
	 * Addition operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The added vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator+(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) + rhs();
	}

	/**
	 * Subtract operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The subracted vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator-(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() - TYPE(rhs);
	}

	/**
	 * Subtract operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The subracted vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator-(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) - rhs();
	}

	/**
	 * Multiply operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The multiplied vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator*(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() * TYPE(rhs);
	}

	/**
	 * Multiply operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The multiplied vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator*(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) * rhs();
	}

	/**
	 * Divide operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The divided vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator/(const Vector<TYPE>& lhs,
		const typename VectorTraits<TYPE>::type& rhs)
	{
		return lhs() / TYPE(rhs);
	}

	/**
	 * Divide operator of the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 * @param lhs: LHS argument.
	 * @param rhs: RHS argument.
	 * @return: The divided vector.
	 */
	template <class TYPE>
	inline Vector<TYPE> operator/(const typename VectorTraits<TYPE>::type& lhs,
		const Vector<TYPE>& rhs)
	{
		return TYPE(lhs) / rhs();
	}

	/**
	 * Zero all the values in the vector.
	 *
	 * @tparam TYPE: The type of the vector.
	 */
	template<class TYPE>
	TYPE Vector<TYPE>::ZeroAll = TYPE(0.0f);
}

#endif // !_DYNAMIK_CORE_MATH_VECTOR_H
