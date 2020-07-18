// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MathFunctions.h"

#include <cmath>

namespace Dynamik
{
	I32 DMKMathFunctions::abs(I32 value)
	{
		I32 const y = value >> (sizeof(I32) * 8 - 1);
		return (value ^ y) - y;
	}

	B1 DMKMathFunctions::isNaN(F32 value)
	{
		//return std::isnan(value);
		return B1();
	}

	B1 DMKMathFunctions::isNaN(I32 value)
	{
		//return std::isnan(value);
		return B1();
	}

	B1 DMKMathFunctions::isFinite(F32 value)
	{
		//return std::isfinite(value);
		return B1();
	}

	B1 DMKMathFunctions::isFinite(I32 value)
	{
		//return std::isfinite(value);
		return B1();
	}

	B1 DMKMathFunctions::isInfinite(F32 value)
	{
		//return std::isinf(value);
		return B1();
	}

	B1 DMKMathFunctions::isInfinite(I32 value)
	{
		//return std::isinf(value);
		return B1();
	}

	DMK_FORCEINLINE F32 DMKMathFunctions::addAll(Vector4F const vector)
	{
		return vector[0] + vector[1] + vector[2] + vector[3];
	}

	F32 DMKMathFunctions::sin(F32 radians)
	{
		return std::sinf(radians);
	}

	F32 DMKMathFunctions::cos(F32 radians)
	{
		return std::cosf(radians);
	}

	F32 DMKMathFunctions::tan(F32 radians)
	{
		return std::tanf(radians);
	}

	F32 DMKMathFunctions::dot(Vector3F lhs, Vector3F rhs)
	{
		Vector3F _tmp(lhs * rhs);
		return _tmp.x + _tmp.y + _tmp.z;
	}

	F32 DMKMathFunctions::dot(Vector4F lhs, Vector4F rhs)
	{
		Vector4F _tmp(lhs * rhs);
		return (_tmp.x + _tmp.y) + (_tmp.z + _tmp.w);
	}

	F32 DMKMathFunctions::degrees(F32 const radians)
	{
		return radians * 57.295779513082320876798154814105f;
	}

	F32 DMKMathFunctions::radians(F32 const degrees)
	{
		return degrees * 0.01745329251994329576923690768489f;
	}

	Vector3F DMKMathFunctions::cross(Vector3F lhs, Vector3F rhs)
	{
		return (Vector3F(lhs.y, lhs.z, lhs.x) * Vector3F(rhs.z, rhs.x, rhs.y)) -
			(Vector3F(rhs.y, rhs.z, rhs.x) * Vector3F(lhs.z, lhs.x, lhs.y));
	}

	Vector3F DMKMathFunctions::normalize(Vector3F rhs)
	{
		return rhs * (1.0f / std::sqrt(dot(rhs, rhs)));
	}

	Vector4F DMKMathFunctions::normalize(Vector4F rhs)
	{
		return rhs * (1.0f / std::sqrt(dot(rhs, rhs)));
	}

	Matrix4F DMKMathFunctions::multiply(Matrix4F const& lhs, Matrix4F const& rhs)
	{
		return Matrix4F(
			(lhs[0] * rhs[0][0]) + (lhs[1] * rhs[0][1]) + (lhs[2] * rhs[0][2]) + (lhs[3] * rhs[0][3]),
			(lhs[0] * rhs[1][0]) + (lhs[1] * rhs[1][1]) + (lhs[2] * rhs[1][2]) + (lhs[3] * rhs[1][3]),
			(lhs[0] * rhs[2][0]) + (lhs[1] * rhs[2][1]) + (lhs[2] * rhs[2][2]) + (lhs[3] * rhs[2][3]),
			(lhs[0] * rhs[3][0]) + (lhs[1] * rhs[3][1]) + (lhs[2] * rhs[3][2]) + (lhs[3] * rhs[3][3]));
	}

	Vector4F DMKMathFunctions::multiply(Matrix4F const& lhs, Vector4F const& rhs)
	{
		return
			((lhs[0] * Vector4F(rhs[0])) +
				(lhs[1] * Vector4F(rhs[1]))) +
			((lhs[2] * Vector4F(rhs[2])) +
				(lhs[3] * Vector4F(rhs[3])));
	}

	Matrix4F DMKMathFunctions::lookAt(Vector3F const eye, Vector3F const center, Vector3F const up)
	{
		auto const f = normalize(center - eye);
		auto const s = normalize(cross(f, up));
		auto const u = cross(s, f);

		Matrix4F newMatrix(1.0f);
		newMatrix[0][0] = s.x;
		newMatrix[1][0] = s.y;
		newMatrix[2][0] = s.z;
		newMatrix[3][0] = -dot(s, eye);

		newMatrix[0][1] = u.x;
		newMatrix[1][1] = u.y;
		newMatrix[2][1] = u.z;
		newMatrix[3][1] = -dot(u, eye);

		newMatrix[0][2] = -f.x;
		newMatrix[1][2] = -f.y;
		newMatrix[2][2] = -f.z;
		newMatrix[3][2] = dot(f, eye);

		return newMatrix;
	}

	Matrix4F DMKMathFunctions::perspective(F32 FOV, F32 aspect, F32 near, F32 far, B1 flipYAxis)
	{
		F32 const halfTan = DMathLib::tan(FOV / 2.0f);

		Matrix4F newMatrix(0.0f);
		newMatrix[0][0] = 1.0f / (aspect * halfTan);
		newMatrix[1][1] = 1.0f / (halfTan);
		newMatrix[2][2] = far / (near - far);
		newMatrix[2][3] = -1.0f;
		newMatrix[3][2] = -(far * near) / (far - near);

		if (flipYAxis)
			newMatrix[1][1] *= -1.0f;

		return newMatrix;
	}

	Matrix4F DMKMathFunctions::translate(Matrix4F mat, Vector3F const vec)
	{
		mat[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
		return mat;
	}

	Matrix4F DMKMathFunctions::scale(Matrix4F mat, Vector3F const vec)
	{
		Matrix4F matrix = Matrix4F::Identity;
		matrix[0] = mat[0] * vec[0];
		matrix[1] = mat[1] * vec[1];
		matrix[2] = mat[2] * vec[2];
		matrix[3] = mat[3];

		return matrix;
	}

	Matrix4F DMKMathFunctions::rotate(Matrix4F const mat, F32 const angel, Vector3F const vec)
	{
		F32 const c = cos(angel);
		F32 const s = sin(angel);

		auto axis = normalize(vec);
		auto temp = axis * (1.0f - c);

		Matrix4F newMatrix(0.0f);
		newMatrix[0] =
			(mat[0] * (c + temp[0] * axis[0])) +
			(mat[1] * (temp[0] * axis[1] + s * axis[2])) +
			(mat[2] * (temp[0] * axis[2] - s * axis[1]));
		newMatrix[1] =
			(mat[0] * (temp[1] * axis[0] - s * axis[2])) +
			(mat[1] * (c + temp[1] * axis[1])) +
			(mat[2] * (temp[1] * axis[2] + s * axis[0]));
		newMatrix[2] =
			(mat[0] * (temp[2] * axis[0] + s * axis[1])) +
			(mat[1] * (temp[2] * axis[1] - s * axis[0])) +
			(mat[2] * (c + temp[2] * axis[2]));
		newMatrix[3] = mat[3];

		return newMatrix;
	}

	Matrix4F DMKMathFunctions::inverse(Matrix4F const& m)
	{
		Vector4F Fac0(
			m[2][2] * m[3][3] - m[3][2] * m[2][3],
			m[2][2] * m[3][3] - m[3][2] * m[2][3],
			m[1][2] * m[3][3] - m[3][2] * m[1][3], 
			m[1][2] * m[2][3] - m[2][2] * m[1][3]);

		Vector4F Fac1(
			m[2][1] * m[3][3] - m[3][1] * m[2][3],
			m[2][1] * m[3][3] - m[3][1] * m[2][3],
			m[1][1] * m[3][3] - m[3][1] * m[1][3],
			m[1][1] * m[2][3] - m[2][1] * m[1][3]);

		Vector4F Fac2(
			m[2][1] * m[3][2] - m[3][1] * m[2][2],
			m[2][1] * m[3][2] - m[3][1] * m[2][2],
			m[1][1] * m[3][2] - m[3][1] * m[1][2],
			m[1][1] * m[2][2] - m[2][1] * m[1][2]);

		Vector4F Fac3(
			m[2][0] * m[3][3] - m[3][0] * m[2][3],
			m[2][0] * m[3][3] - m[3][0] * m[2][3],
			m[1][0] * m[3][3] - m[3][0] * m[1][3],
			m[1][0] * m[2][3] - m[2][0] * m[1][3]);

		Vector4F Fac4(
			m[2][0] * m[3][2] - m[3][0] * m[2][2],
			m[2][0] * m[3][2] - m[3][0] * m[2][2],
			m[1][0] * m[3][2] - m[3][0] * m[1][2],
			m[1][0] * m[2][2] - m[2][0] * m[1][2]);

		Vector4F Fac5(
			m[2][0] * m[3][1] - m[3][0] * m[2][1],
			m[2][0] * m[3][1] - m[3][0] * m[2][1],
			m[1][0] * m[3][1] - m[3][0] * m[1][1],
			m[1][0] * m[2][1] - m[2][0] * m[1][1]);

		Vector4F Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		Vector4F Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		Vector4F Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		Vector4F Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		Vector4F Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		Vector4F Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		Vector4F Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		Vector4F Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		Vector4F SignA(+1, -1, +1, -1);
		Vector4F SignB(-1, +1, -1, +1);
		Matrix4F Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		Vector4F Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		Vector4F Dot0(m[0] * Row0);
		F32 Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		F32 OneOverDeterminant = static_cast<F32>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}

	Quaternion DMKMathFunctions::interpolate(Quaternion const& start, Quaternion const& end, const F32& blend)
	{
		F32 blendI = 1.0f - blend;

		if (dot(start.toVector4F(), end.toVector4F()) < 0)
			return normalize((start.toVector4F() * blendI) + (end.toVector4F() * (-1.0f * blendI)));
		else
			return normalize((start.toVector4F() * blendI) + (end.toVector4F() * blendI));
	}

	Vector3F DMKMathFunctions::interpolate(Vector3F const& start, Vector3F const& end, const F32& progression)
	{
		return (start + (end - start)) * progression;
	}

	Matrix4F DMKMathFunctions::toRotationalMatrix(Quaternion const& quat)
	{
		F32 xy = quat.x * quat.y;
		F32 xz = quat.x * quat.z;
		F32 xw = quat.x * quat.w;
		F32 yz = quat.y * quat.z;
		F32 yw = quat.y * quat.w;
		F32 zw = quat.z * quat.w;
		F32 xSquared = quat.x * quat.x;
		F32 ySquared = quat.y * quat.y;
		F32 zSquared = quat.z * quat.z;

		Matrix4F matrix = Matrix4F(0.0f);
		matrix[0][0] = 1 - 2 * (ySquared + zSquared);
		matrix[0][1] = 2 * (xy - zw);
		matrix[0][2] = 2 * (xz + yw);
		matrix[1][0] = 2 * (xy + zw);
		matrix[1][1] = 1 - 2 * (xSquared + zSquared);
		matrix[1][2] = 2 * (yz - xw);
		matrix[2][0] = 2 * (xz - yw);
		matrix[2][1] = 2 * (yz + xw);
		matrix[2][2] = 1 - 2 * (xSquared + ySquared);
		matrix[3][3] = 1;

		return matrix;
	}
}