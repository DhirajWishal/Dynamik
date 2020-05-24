#include "dmkafx.h"
#include "Vector2F.h"

namespace Dynamik
{
	Vector2F::Vector2F(std::initializer_list<F32> list) : x(0.0f), y(0.0f)
	{
		F32* _addr = &x;
		_addr = (F32*)list.begin();
	}

	Vector2F Vector2F::operator=(const std::initializer_list<F32>& list)
	{
		F32* _addr = &this->x;
		_addr = (F32*)list.begin();

		return *this;
	}

	F32& Vector2F::operator[](UI32 index) const 
	{
		return ((F32*)this)[index];
	}

	Vector2F operator+(const Vector2F& lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2F operator-(const Vector2F& lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2F operator*(const Vector2F& lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	Vector2F operator/(const Vector2F& lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	B1 operator==(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	B1 operator!=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y);
	}

	B1 operator<(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x < rhs.x) || (lhs.y < rhs.y);
	}

	B1 operator<=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x <= rhs.x) || (lhs.y <= rhs.y);
	}

	B1 operator>(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x > rhs.x) || (lhs.y > rhs.y);
	}

	B1 operator>=(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x >= rhs.x) || (lhs.y >= rhs.y);
	}

	B1 operator&&(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x && rhs.x) && (lhs.y && rhs.y);
	}

	B1 operator||(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x || rhs.x) || (lhs.y || rhs.y);
	}

	B1 operator^(const Vector2F& lhs, const Vector2F& rhs)
	{
		return (lhs.x || rhs.x) && (lhs.y || rhs.y);
	}

	B1 operator~(const Vector2F& rhs)
	{
		return (rhs.x > 0) && (rhs.y > 0);
	}

	B1 operator!(const Vector2F& rhs)
	{
		return (rhs.x != 0) && (rhs.y != 0);
	}
}