// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "BoundingBox.h"

#include "Core/Math/MathFunctions.h"

#include "../RenderableComponent.h"

#include <cmath>

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
			VertexBB(Vector3F position) : position(position) {}
			~VertexBB() {}

			Vector3F position = Vector3F(0.0f);
		};

		ARRAY<VertexBB> vertexList;
		vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MAX_Z }));
		vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MIN_Z }));
		vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MIN_Z }));
		vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MAX_Z }));
		vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MAX_Z }));
		vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MIN_Z }));
		vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MIN_Z }));
		vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MAX_Z }));

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
			6, 1, 6, 7, 7, 0, 7, 4
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
		shouldDisplay(false)
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

	char HitBoundingBox(F32* minB, F32* maxB, F32* origin, F32* dir, F32* coord);

	B1 DMKBoundingBoxAttachment::_checkOBBIntercept(DMKCameraRay ray)
	{
		return HitBoundingBox((F32*)&minimumBounds, (F32*)&maximumBounds, (F32*)&ray.origin, (F32*)&ray.direction, (F32*)&getPosition());
	}

#define NUMDIM	3
#define RIGHT	0
#define LEFT	1
#define MIDDLE	2

	char HitBoundingBox(F32* minB, F32* maxB, F32* origin, F32* dir, F32* coord)
	{
		char inside = true;
		char quadrant[NUMDIM];
		register int i;
		int whichPlane;
		F32 maxT[NUMDIM];
		F32 candidatePlane[NUMDIM];

		/* Find candidate planes; this loop can be avoided if
		rays cast all from the eye(assume perpsective view) */
		for (i = 0; i < NUMDIM; i++)
			if (origin[i] < minB[i]) {
				quadrant[i] = LEFT;
				candidatePlane[i] = minB[i];
				inside = false;
			}
			else if (origin[i] > maxB[i]) {
				quadrant[i] = RIGHT;
				candidatePlane[i] = maxB[i];
				inside = false;
			}
			else {
				quadrant[i] = MIDDLE;
			}

		/* Ray origin inside bounding box */
		if (inside) {
			coord = origin;
			return (true);
		}


		/* Calculate T distances to candidate planes */
		for (i = 0; i < NUMDIM; i++)
			if (quadrant[i] != MIDDLE && dir[i] != 0.)
				maxT[i] = (candidatePlane[i] - origin[i]) / dir[i];
			else
				maxT[i] = -1.;

		/* Get largest of the maxT's for final choice of intersection */
		whichPlane = 0;
		for (i = 1; i < NUMDIM; i++)
			if (maxT[whichPlane] < maxT[i])
				whichPlane = i;

		/* Check final candidate actually inside box */
		if (maxT[whichPlane] < 0.) return (false);
		for (i = 0; i < NUMDIM; i++)
			if (whichPlane != i) {
				coord[i] = origin[i] + maxT[whichPlane] * dir[i];
				if (coord[i] < minB[i] || coord[i] > maxB[i])
					return (false);
			}
			else {
				coord[i] = candidatePlane[i];
			}
		return (true);				/* ray hits box */
	}
}
