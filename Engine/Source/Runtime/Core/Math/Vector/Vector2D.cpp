#include "dmkafx.h"
#include "Vector2D.h"

namespace Dynamik
{
	Vector2D::Vector2D(std::initializer_list<D64> list) : x(0.0f), y(0.0f)
	{
		D64* _addr = &x;
		_addr = (D64*)list.begin();
	}

	Vector2D Vector2D::operator=(const std::initializer_list<D64>& list)
	{
		D64* _addr = &this->x;
		_addr = (D64*)list.begin();

		return *this;
	}

	D64& Vector2D::operator[](UI32 index) const
	{
		return ((D64*)this)[index];
	}

	Vector2D operator+(const Vector2D& lhs, const Vector2D& rhs)
	{
		return Vector2D(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
	{
		return Vector2D(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	Vector2D operator*(const Vector2D& lhs, const Vector2D& rhs)
	{
		return Vector2D(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	Vector2D operator/(const Vector2D& lhs, const Vector2D& rhs)
	{
		return Vector2D(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	B1 operator==(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	B1 operator!=(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x != rhs.x) || (lhs.y != rhs.y);
	}

	B1 operator<(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x < rhs.x) || (lhs.y < rhs.y);
	}

	B1 operator<=(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x <= rhs.x) || (lhs.y <= rhs.y);
	}

	B1 operator>(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x > rhs.x) || (lhs.y > rhs.y);
	}

	B1 operator>=(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x >= rhs.x) || (lhs.y >= rhs.y);
	}

	B1 operator&&(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x && rhs.x) && (lhs.y && rhs.y);
	}

	B1 operator||(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x || rhs.x) || (lhs.y || rhs.y);
	}

	B1 operator^(const Vector2D& lhs, const Vector2D& rhs)
	{
		return (lhs.x || rhs.x) && (lhs.y || rhs.y);
	}

	B1 operator~(const Vector2D& rhs)
	{
		return (rhs.x > 0) && (rhs.y > 0);
	}

	B1 operator!(const Vector2D& rhs)
	{
		return (rhs.x != 0) && (rhs.y != 0);
	}
}