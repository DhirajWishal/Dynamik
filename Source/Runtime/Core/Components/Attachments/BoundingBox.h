// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_BOUNDING_BOX_ATTACHMENT_H
#define _DYNAMIK_BOUNDING_BOX_ATTACHMENT_H

#include "ComponentAttachment.h"
#include "Core/Math/MathTypes.h"
#include "Core/Math/Quaternion.h"
#include "Core/Types/ComplexTypes.h"
#include "Core/Objects/Resources/VertexBuffer.h"

namespace Dynamik
{
	/*
	 Dynamik Bounding Box Type
	 This defines the shape of the bounding box and how well it will cover the mesh volume.
	*/
	enum class DMK_API DMKBoundingBoxType {
		DMK_BOUNDING_BOX_TYPE_SPHERE,
		DMK_BOUNDING_BOX_TYPE_ELLIPSOID,
		DMK_BOUNDING_BOX_TYPE_CYLINDER,
		DMK_BOUNDING_BOX_TYPE_AXIS_ALIGNED,
		DMK_BOUNDING_BOX_TYPE_ORIENTATION_ALIGNED,
		DMK_BOUNDING_BOX_TYPE_K_DOP,
		DMK_BOUNDING_BOX_TYPE_SPHERE_PACKING,
		DMK_BOUNDING_BOX_TYPE_SWEEP_SPHERE,
		DMK_BOUNDING_BOX_TYPE_SPHERICAL_SHELL,
		DMK_BOUNDING_BOX_TYPE_CONVEX_HULL,
	};

	/*
	 Dynamik Bounding Box Attachment
	 This object is used to define if a bounding box is added to a renderable component.
	*/
	class DMK_API DMKBoundingBoxAttachment : public DMKComponentAttachment {
	public:
		DMKBoundingBoxAttachment() :
			type(DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_ORIENTATION_ALIGNED), shouldDisplay(true),
			rotation(Quaternion::Default), idleColor(1.0f), selectColor(1.0f), position(0.0f),
			minimumBounds(-1.0f), maximumBounds(1.0f), scale(2.0f),
			DMKComponentAttachment(DMKComponentAttachmentType::DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX) {}
		~DMKBoundingBoxAttachment() {}

		/*
		 Set the visibility of the bounding box.
		 If true, the bounding box will be visible.

		 @param bVisibility: Visibility boolean.
		*/
		void setVisibility(const B1& bVisibility);

		/*
		 Set the type of the bounding box.

		 @param type: The required type.
		*/
		void setType(DMKBoundingBoxType type);

		/*
		 Get the current bounding box type.
		*/
		DMKBoundingBoxType getType() const;

		/*
		 Set the rotation of the bounding box.
		 This is only required if the type is OBB or is rotation oriented.

		 @param rotation: Rotation of the BB.
		*/
		void setRotation(Quaternion rotation);

		/*
		 Get the rotation of the current BB.
		*/
		Quaternion getRotation() const;

		/*
		 Set the idle color of the current BB.
		 This color is present when the user has not selected the current box. Default is white.

		 @param idleColor: The required color.
		*/
		void setIdleColor(DMKColorComponent idleColor);

		/*
		 Get the idle color of the current BB.
		*/
		DMKColorComponent getIdleColor() const;

		/*
		 Set the select color of the current BB.
		 This color is present when the user has selected the current BB.

		 @param selectColor: The required color.
		*/
		void setSelectColor(DMKColorComponent selectColor);

		/*
		 Get the select color of the current BB.
		*/
		DMKColorComponent getSelectColor() const;

		/*
		 Set the position of the BB.

		 @param position: The position of the BB.
		*/
		void setPosition(Vector3F position);

		/*
		 Get the position of the BB.
		*/
		Vector3F getPosition() const;

		/*
		 Set the minimum bounds of the current BB.

		 @param minimumBounds: The required minimum bounds.
		*/
		void setMinimumBounds(Vector3F minimumBounds);

		/*
		 Get the minimum bounds of the current BB.
		*/
		Vector3F getMinimumBounds() const;

		/*
		 Set the maximum bounds of the current BB.

		 @param maximumBounds: The required maximum bounds.
		*/
		void setMaximumBounds(Vector3F maximumBounds);

		/*
		 Get the maximum bounds of the current BB.
		*/
		Vector3F getMaximumBounds() const;

		/*
		 Set the scale of the current BB.

		 @param scale: The scale to be set.
		*/
		void setScale(Vector3F scale);

		/*
		 Get the scale of the current BB.
		*/
		Vector3F getScale() const;

		/*
		 Update the bounding box.
		*/
		virtual void update() override final;

	public:
		DMKVertexBuffer vertexBuffer;
		ARRAY<UI32> indexBuffer;

		/*
		 Initialize the mesh.
		*/
		virtual void initialize() override final;

	public:
		Quaternion rotation = Quaternion::Default;		/* Used only by OBB */
		DMKColorComponent idleColor;					/* When the bounding box is in idle */
		DMKColorComponent selectColor;					/* When the user has selected the bounding box */
		Vector3F position;
		Vector3F minimumBounds = Vector3F::ZeroAll;
		Vector3F maximumBounds = Vector3F::ZeroAll;
		Vector3F scale = Vector3F::ZeroAll;

		DMKBoundingBoxType type = DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_ORIENTATION_ALIGNED;

	private:
		B1 shouldDisplay = true;
		B1 isSelected = false;

		struct TUniformObject {
			TUniformObject() {}
			TUniformObject(Matrix4F mat) : matrix(mat) {}
			TUniformObject(DMKColorComponent col) : color(col) {}
			TUniformObject(Matrix4F mat, DMKColorComponent col) : matrix(mat), color(col) {}
			~TUniformObject() {}

			Matrix4F matrix;
			DMKColorComponent color;
		};
	};
}

#endif // !_DYNAMIK_BOUNDING_BOX_ATTACHMENT_H
