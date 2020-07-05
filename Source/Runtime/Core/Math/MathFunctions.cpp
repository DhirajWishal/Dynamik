// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "MathFunctions.h"

namespace Dynamik
{
	I32 DMKMathFunctions::abs(I32 value)
	{
		I32 const y = value >> (sizeof(I32) * 8 - 1);
		return (value ^ y) - y;
	}

	DMK_FORCEINLINE F32 DMKMathFunctions::addAll(Vector4F const vector)
	{
		return vector[0] + vector[1] + vector[2] + vector[3];
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

	Matrix4F DMKMathFunctions::multiply(Matrix4F const lhs, Matrix4F const rhs)
	{
		return Matrix4F(
			addAll(lhs[0] * Vector4F(rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0])),
			addAll(lhs[1] * Vector4F(rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0])),
			addAll(lhs[2] * Vector4F(rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0])),
			addAll(lhs[3] * Vector4F(rhs[0][0], rhs[1][0], rhs[2][0], rhs[3][0])),

			addAll(lhs[0] * Vector4F(rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1])),
			addAll(lhs[1] * Vector4F(rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1])),
			addAll(lhs[2] * Vector4F(rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1])),
			addAll(lhs[3] * Vector4F(rhs[0][1], rhs[1][1], rhs[2][1], rhs[3][1])),

			addAll(lhs[0] * Vector4F(rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2])),
			addAll(lhs[1] * Vector4F(rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2])),
			addAll(lhs[2] * Vector4F(rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2])),
			addAll(lhs[3] * Vector4F(rhs[0][2], rhs[1][2], rhs[2][2], rhs[3][2])),

			addAll(lhs[0] * Vector4F(rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3])),
			addAll(lhs[1] * Vector4F(rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3])),
			addAll(lhs[2] * Vector4F(rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3])),
			addAll(lhs[3] * Vector4F(rhs[0][3], rhs[1][3], rhs[2][3], rhs[3][3]))
		);
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
		F32 const halfTan = std::tan(FOV / 2.0f);

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
}