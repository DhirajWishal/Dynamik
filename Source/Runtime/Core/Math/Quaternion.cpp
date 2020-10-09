// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Quaternion.h"

Quaternion Quaternion::operator=(const Vector4F& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
	return *this;
}

Vector3F Quaternion::toVector3F() const
{
	return Vector3F(x, y, z);
}

Vector4F Quaternion::toVector4F() const
{
	return Vector4F(x, y, z, w);
}

Quaternion Quaternion::Default = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
