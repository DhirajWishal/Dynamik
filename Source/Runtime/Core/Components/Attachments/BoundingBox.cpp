// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "BoundingBox.h"

#include "Core/Math/MathFunctions.h"

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
            VertexBB(Vector3F position, Vector3F color) : position(position), color(color) {}
            ~VertexBB() {}

            Vector3F position = Vector3F(0.0f);
            Vector3F color = Vector3F(1.0f);
        };

        ARRAY<VertexBB> vertexList;
        vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MAX_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MIN_X, MAX_Y, MIN_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MIN_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MAX_X, MAX_Y, MAX_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MAX_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MAX_X, MIN_Y, MIN_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MIN_Z }, { idleColor.r, idleColor.g, idleColor.b }));
        vertexList.pushBack(VertexBB({ MIN_X, MIN_Y, MAX_Z }, { idleColor.r, idleColor.g, idleColor.b }));

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

    void DMKBoundingBoxAttachment::setMatrix(const Matrix4F& mat)
    {
        myMatrix = mat;
    }

    Matrix4F DMKBoundingBoxAttachment::getMatrix() const
    {
        if (shouldDisplay)
            return myMatrix;

        return Matrix4F(0.0f);
    }
    
    void DMKBoundingBoxAttachment::initialize()
    {
        vertexBuffer = generateBoundingBoxVertex(minimumBounds, maximumBounds, idleColor);
        indexBuffer = generateBoundingBoxIndex();
    }
}
