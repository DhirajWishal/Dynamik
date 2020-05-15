#pragma once
#ifndef _DYNAMIK_RESOURCE_PRIMITIVES_H
#define _DYNAMIK_RESOURCE_PRIMITIVES_H

/*
 This file contains all the primitive resources in their virtual form (Vertex, Shader, Uniform).

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "Math/MathTypes.h"
#include "Object/Descriptor.h"

namespace Dynamik
{
    /* Vertex */
    /*
     This Structure contains all the possible vertex data in a mesh. Later when submitting the data, each
     vertex gets packed into a pre allocated space using the vertex attributes.
    */
    DMK_ALIGN struct DMK_API DMKVertexObject {
        VEC3 position;
        VEC3 color;
        VEC3 textureCoord;
        VEC3 normal;
        F32 integrity = 0.0f;   /* For the Dynamik Destruction Engine */
    };

    /* Vertex attribute types */
    enum class DMK_API DMKVertexAttributeType {
        DMK_VERTEX_ATTRIBUTE_TYPE_POSITION,                 /* Position coordinates */
        DMK_VERTEX_ATTRIBUTE_TYPE_COLOR,                    /* Color coordinates */
        DMK_VERTEX_ATTRIBUTE_TYPE_TEXTURE_COORDINATES,      /* Texture coordinates */
        DMK_VERTEX_ATTRIBUTE_TYPE_NORMAL,                   /* Normal vectors */
        DMK_VERTEX_ATTRIBUTE_TYPE_INTEGRITY,                /* Integrity value */
        DMK_VERTEX_ATTRIBUTE_TYPE_CUSTOM                    /* Custom */
    };

    /* Dynamik Vertex Attribute */
    DMK_ALIGN struct DMK_API DMKVertexAttribute {
        DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_VEC3;
        DMKVertexAttributeType attributeType = DMKVertexAttributeType::DMK_VERTEX_ATTRIBUTE_TYPE_POSITION;
    };

    /* This contains all the vertex buffer attributes */
    DMK_ALIGN class DMK_API DMKVertexBufferDescriptor : public DMKDescriptor {
    public:
        DMKVertexBufferDescriptor() {}
        ~DMKVertexBufferDescriptor() {}

        /* Get the size of the vertex using the attributes */
        UI32 getVertexSize();

        ARRAY<DMKVertexAttribute> attributes;
    };

    /* Shader */
    /* Dynamik Shader Locations */
    enum class DMK_API DMKShaderLocation {
        DMK_SHADER_LOCATION_VERTEX,
        DMK_SHADER_LOCATION_TESSELLATION,
        DMK_SHADER_LOCATION_GEOMETRY,
        DMK_SHADER_LOCATION_FRAGMENT
    };

    /* Dynamik Shader Path Container */
    DMK_ALIGN struct DMK_API DMKShaderPath {
        STRING path = DMK_TEXT("");
        DMKShaderLocation location = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
    };

    /* Uniform */
    /* Dynamik Uniform Attribute Types */
    enum class DMK_API DMKUniformAttributeType {
        DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL,
        DMK_UNIFORM_ATTRIBUTE_TYPE_VIEW,
        DMK_UNIFORM_ATTRIBUTE_TYPE_PROJECTION,
        DMK_UNIFORM_ATTRIBUTE_TYPE_CUSTOM
    };

    /* Dynamik Uniform Attribute */
    DMK_ALIGN struct DMK_API DMKUniformAttribute {
        DMKDataType dataType = DMKDataType::DMK_DATA_TYPE_MAT4;
        DMKUniformAttributeType attributeType = DMKUniformAttributeType::DMK_UNIFORM_ATTRIBUTE_TYPE_MODEL;
    };

    /* Dynamik Uniform Buffer Object */
    DMK_ALIGN struct DMK_API DMKUniformBufferObject {
        ARRAY<DMKUniformAttribute> attributes;
        DMKShaderLocation shaderLocation = DMKShaderLocation::DMK_SHADER_LOCATION_VERTEX;
    };

    /* Dynamik Uniform Descriptor */
    DMK_ALIGN class DMK_API DMKUniformBufferDescriptor : public DMKDescriptor {
    public:
        DMKUniformBufferDescriptor() {}
        ~DMKUniformBufferDescriptor() {}

        ARRAY<DMKUniformBufferObject> uniformBufferObjects;
    };
}

#endif // !_DYNAMIK_RESOURCE_PRIMITIVES_H
