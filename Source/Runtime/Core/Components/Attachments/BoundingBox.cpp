// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "BoundingBox.h"

#include "Core/Math/MathFunctions.h"

#include "../RenderableComponent.h"

namespace Dynamik
{
	DMK_FORCEINLINE DMKVertexBuffer generateBoundingBoxVertex(Vector3F minimum, Vector3F maximum, DMKColorComponent idleColor)
	{
		DMKVertexBuffer buffer;

#define MIN_X minimum.x
#define MIN_Y minimum.y
#define MIN_Z minimum.z

#define MAX_X maximum.x
#define MAX_Y maximum.y
#define MAX_Z maximum.z

		struct VertexBB
		{
			VertexBB() {}
			VertexBB(Vector3F position, DMKColorComponent color) : position(position), color(color) {}
			~VertexBB() {}

			Vector3F position = Vector3F(0.0f);
			DMKColorComponent color = DMKColorComponent(0.0f);
		};

		ARRAY<VertexBB> vertexList;
		/* The box */
		vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MAX_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MIN_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MIN_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MAX_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MAX_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MIN_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MIN_Z }, idleColor));
		vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MAX_Z }, idleColor));

		/* Coordinates */
		vertexList.pushBack(VertexBB({ (MIN_X + MAX_X) / 2, (MIN_Y + MAX_Y) / 2, (MIN_Z + MAX_Z) / 2 }, { 1.0f, 0.0f, 0.0f, 1.0f }));		/* X axis start */
		vertexList.pushBack(VertexBB({ MAX_X, (MIN_Y + MAX_Y) / 2, (MIN_Z + MAX_Z) / 2 }, { 1.0f, 0.0f, 0.0f, 1.0f }));						/* X axis end */
		vertexList.pushBack(VertexBB({ (MIN_X + MAX_X) / 2, (MIN_Y + MAX_Y) / 2, (MIN_Z + MAX_Z) / 2 }, { 0.0f, 1.0f, 0.0f, 1.0f }));		/* Y axis start */
		vertexList.pushBack(VertexBB({ (MIN_X + MAX_X) / 2, MAX_Y, (MIN_Z + MAX_Z) / 2 }, { 0.0f, 1.0f, 0.0f, 1.0f }));						/* Y axis end */
		vertexList.pushBack(VertexBB({ (MIN_X + MAX_X) / 2, (MIN_Y + MAX_Y) / 2, (MIN_Z + MAX_Z) / 2 }, { 0.0f, 0.0f, 1.0f, 1.0f }));		/* Z axis start */
		vertexList.pushBack(VertexBB({ (MIN_X + MAX_X) / 2 ,(MIN_Y + MAX_Y) / 2, MAX_Z }, { 0.0f, 0.0f, 1.0f, 1.0f }));						/* Z axis end */

		buffer.setLayout(DMKVertexLayout::createBoundingBox());
		buffer.initialize(vertexList.size());
		buffer.setData(vertexList.data());

		return buffer;
	}

	DMK_FORCEINLINE ARRAY<UI32> generateBoundingBoxIndex()
	{
		return {
			0, 1, 1, 2, 2, 3, 3, 0,
			3, 4, 4, 5, 5, 2, 5, 6,
			6, 1, 6, 7, 7, 0, 7, 4,

			8, 9,
			10, 11,
			12, 13
		};
	}

	DMKBoundingBoxAttachment::DMKBoundingBoxAttachment(
		DMKComponent* pComponent,
		Quaternion rotation,
		DMKColorComponent idleColor,
		DMKColorComponent selectColor,
		Vector3F minimumBounds,
		Vector3F maximumBounds,
		Vector3F scale
	) :
		type(DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_ORIENTATION_ALIGNED),
		rotation(rotation),
		idleColor(idleColor),
		selectColor(selectColor),
		minimumBounds(minimumBounds),
		maximumBounds(maximumBounds),
		scale(scale),
		DMKComponentAttachment(
			pComponent,
			DMKComponentAttachmentType::DMK_COMPONENT_ATTACHMENT_TYPE_BOUNDING_BOX
		),
		shouldDisplay(true)
	{
		if (!pComponent)
		{
			DMK_ERROR("pComponent must not be equal to nullptr!");
			return;
		}

		vertexBuffer = generateBoundingBoxVertex(minimumBounds, maximumBounds, idleColor);
		indexBuffer = generateBoundingBoxIndex();

		TUniformObject _uniform(
			DMathLib::translate(Matrix4F::Identity, getPosition()) *
			DMathLib::toRotationalMatrix(rotation) *
			DMathLib::scale(Matrix4F::Identity, scale),
			idleColor);

		/* Initialize Uniform Buffer */
		DMKUniformDescription description;
		description.destinationBinding = 0;
		description.shaderLocation = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		description.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;

		DMKUniformAttribute attribute;
		attribute.dataCount = 1;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		description.attributes.pushBack(attribute);

		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC4;
		description.attributes.pushBack(attribute);

		uniformBufferObject.initialize(description);
		uniformBufferObject.setData(&_uniform);
	}

	void DMKBoundingBoxAttachment::setVisibility(const B1& bVisibility)
	{
		shouldDisplay = bVisibility;
	}

	void DMKBoundingBoxAttachment::setType(DMKBoundingBoxType type)
	{
		this->type = type;
	}

	DMKBoundingBoxType DMKBoundingBoxAttachment::getType() const
	{
		return type;
	}

	void DMKBoundingBoxAttachment::setRotation(Quaternion rotation)
	{
		this->rotation = rotation;
	}

	Quaternion DMKBoundingBoxAttachment::getRotation() const
	{
		return rotation;
	}

	void DMKBoundingBoxAttachment::setIdleColor(DMKColorComponent idleColor)
	{
		this->idleColor = idleColor;
	}

	DMKColorComponent DMKBoundingBoxAttachment::getIdleColor() const
	{
		return idleColor;
	}

	void DMKBoundingBoxAttachment::setSelectColor(DMKColorComponent selectColor)
	{
		this->selectColor = selectColor;
	}

	DMKColorComponent DMKBoundingBoxAttachment::getSelectColor() const
	{
		return selectColor;
	}

	Vector3F DMKBoundingBoxAttachment::getPosition() const
	{
		return Inherit<DMKRenderableComponent>(pParentComponent)->position;
	}

	void DMKBoundingBoxAttachment::setMinimumBounds(Vector3F minimumBounds)
	{
		this->minimumBounds = minimumBounds;
	}

	Vector3F DMKBoundingBoxAttachment::getMinimumBounds() const
	{
		return minimumBounds;
	}

	void DMKBoundingBoxAttachment::setMaximumBounds(Vector3F maximumBounds)
	{
		this->maximumBounds = maximumBounds;
	}

	Vector3F DMKBoundingBoxAttachment::getMaximumBounds() const
	{
		return maximumBounds;
	}

	void DMKBoundingBoxAttachment::setScale(Vector3F scale)
	{
		this->scale = scale;
	}

	Vector3F DMKBoundingBoxAttachment::getScale() const
	{
		return scale;
	}

	void DMKBoundingBoxAttachment::update()
	{
		if (!shouldDisplay)
		{
			uniformBufferObject.setZero();
			return;
		}

		TUniformObject _uniform;
		_uniform.matrix =
			DMathLib::translate(Matrix4F::Identity, getPosition()) *
			DMathLib::toRotationalMatrix(rotation) *
			DMathLib::scale(Matrix4F::Identity, scale);
		_uniform.color = idleColor;

		if (isSelected)
			_uniform.color = selectColor;

		uniformBufferObject.setData(&_uniform);
	}

	void DMKBoundingBoxAttachment::initialize()
	{
		if (!pParentComponent)
		{
			DMK_ERROR("pComponent must not be equal to nullptr!");
			return;
		}

		vertexBuffer = generateBoundingBoxVertex(minimumBounds, maximumBounds, idleColor);
		indexBuffer = generateBoundingBoxIndex();

		TUniformObject _uniform(
			DMathLib::translate(Matrix4F::Identity, getPosition()) *
			DMathLib::toRotationalMatrix(rotation) *
			DMathLib::scale(Matrix4F::Identity, scale),
			idleColor);

		/* Initialize Uniform Buffer */
		DMKUniformDescription description;
		description.destinationBinding = 0;
		description.shaderLocation = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
		description.type = DMKUniformType::DMK_UNIFORM_TYPE_UNIFORM_BUFFER;

		DMKUniformAttribute attribute;
		attribute.dataCount = 1;
		attribute.dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
		description.attributes.pushBack(attribute);

		attribute.dataType = DMKDataType::DMK_DATA_TYPE_VEC4;
		description.attributes.pushBack(attribute);

		uniformBufferObject.initialize(description);
		uniformBufferObject.setData(&_uniform);
	}

	B1 DMKBoundingBoxAttachment::checkRayIntercept(DMKCameraRay ray)
	{
		switch (type)
		{
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_SPHERE:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_ELLIPSOID:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_CYLINDER:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_AXIS_ALIGNED:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_ORIENTATION_ALIGNED:
			return _checkOBBIntercept(ray);
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_K_DOP:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_SPHERE_PACKING:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_SWEEP_SPHERE:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_SPHERICAL_SHELL:
			break;
		case Dynamik::DMKBoundingBoxType::DMK_BOUNDING_BOX_TYPE_CONVEX_HULL:
			break;
		default:
			DMK_ERROR("Intercept does not support this type of bounding boxes!");
			break;
		}

		return B1();
	}

	B1 DMKBoundingBoxAttachment::_checkOBBIntercept(DMKCameraRay ray)
	{
		shouldDisplay = false;

		TUniformObject _uniform;
		DMKMemoryFunctions::copyData(&_uniform, uniformBufferObject.data(), uniformBufferObject.byteSize());

		Vector3F worldPos = Vector3F(_uniform.matrix[3].x, _uniform.matrix[3].y, _uniform.matrix[3].z);
		Vector3F delta = worldPos - ray.origin;

		F32 tMax = 1000000.0f, tMin = 0.0f;

		/* Calculate X Axis */
		{
			Vector3F axis = Vector3F(_uniform.matrix[0].x, _uniform.matrix[0].y, _uniform.matrix[0].z);
			F32 e = DMathLib::dot(axis, delta);
			F32 f = DMathLib::dot(ray.direction, axis);

			if (fabs(f) > 0.001f) {

				F32 t1 = (e + (minimumBounds.x)) / f;
				F32 t2 = (e + (maximumBounds.x)) / f;

				if (t1 > t2) { F32 w = t1; t1 = t2; t2 = w; }
				if (t2 < tMax) tMax = t2;
				if (t1 > tMin) tMin = t1;

				if (tMax < tMin)
					return false;
			}
			else
			{
				if (-e + minimumBounds.x > 0.0f || -e + maximumBounds.x < 0.0f)
					return false;
			}
		}

		/* Calculate Y Axis */
		{
			Vector3F axis = Vector3F(_uniform.matrix[1].x, _uniform.matrix[1].y, _uniform.matrix[1].z);
			F32 e = DMathLib::dot(axis, delta);
			F32 f = DMathLib::dot(ray.direction, axis);

			if (fabs(f) > 0.001f) {

				F32 t1 = (e + (minimumBounds.y)) / f;
				F32 t2 = (e + (maximumBounds.y)) / f;

				if (t1 > t2) { F32 w = t1; t1 = t2; t2 = w; }
				if (t2 < tMax) tMax = t2;
				if (t1 > tMin) tMin = t1;

				if (tMax < tMin)
					return false;
			}
			else
			{
				if (-e + minimumBounds.y > 0.0f || -e + maximumBounds.y < 0.0f)
					return false;
			}
		}

		/* Calculate Z Axis */
		{
			Vector3F axis = Vector3F(_uniform.matrix[2].x, _uniform.matrix[2].y, _uniform.matrix[2].z);
			F32 e = DMathLib::dot(axis, delta);
			F32 f = DMathLib::dot(ray.direction, axis);

			if (fabs(f) > 0.001f) {

				F32 t1 = (e + (minimumBounds.z)) / f;
				F32 t2 = (e + (maximumBounds.z)) / f;

				if (t1 > t2) { F32 w = t1; t1 = t2; t2 = w; }
				if (t2 < tMax) tMax = t2;
				if (t1 > tMin) tMin = t1;

				if (tMax < tMin)
					return false;
			}
			else
			{
				if (-e + minimumBounds.z > 0.0f || -e + maximumBounds.z < 0.0f)
					return false;
			}
		}

		if (tMin != 0.0f)
			return false;

		shouldDisplay = true;
		return shouldDisplay;
	}
}
