#include "dmkafx.h"
#include "Vector2D.h"

namespace Dynamik
{
	Vector2D::Vector2D(std::initializer_list<D64> list) 
	{
		if ((list.size() > 2) || (list.size() < 2))
			DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

		MemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(D64));
	}

	Vector2D Vector2D::operator=(const std::initializer_list<D64>& list)
	{
		if ((list.size() > 2) || (list.size() < 2))
			DMK_ERROR_BOX("The size of the provided list does not match the current Vector size!");

		MemoryFunctions::moveData(this, (VPTR)list.begin(), list.size() * sizeof(D64));

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