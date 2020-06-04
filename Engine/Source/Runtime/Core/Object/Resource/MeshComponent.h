#pragma once
#ifndef _DYNAMIK_MESH_COMPONENT_H
#define _DYNAMIK_MESH_COMPONENT_H

/*
 Dynamik Mesh Component.
 This component contains all the necessary variables to store all the available mesh data of an imported
 mesh.
 This also contains all the functionalities to manipulate a mesh object.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/
#include "Primitives.h"

namespace Dynamik
{
	/*
	 Mesh Component super class for the Dynamik Engine.
	 This class itself does not store any mesh data. Mesh components are derived from this to store their
	 data.
	 This class contains functions to manipulate a full mesh.
	*/
	class DMK_API DMKMeshComponent {
	public:
		DMKMeshComponent() {}
		DMKMeshComponent(const DMKVertexBufferDescriptor& descriptor, const DMKDataType& type)
			: vertexDescriptor(descriptor), indexBufferType(type) {}
		virtual ~DMKMeshComponent() {}

		/* TODO:
		 static DMKMeshComponent& createMesh(VertexData);
		*/

		/* Get the total byte size of the vertex buffer object */
		UI32 getVertexBufferObjectByteSize();

		/* Get the total byte size of the index buffer object */
		UI32 getIndexBufferObjectByteSize();

		/*
		 Pack all vertex data into a location.

		 @warn: The pre allocated memory location must be allocated to fit the whole vertex buffer object.
				To ensure this, use getVertexBufferObjectByteSize() to allocate the buffer percisely.
		*/
		void packData(VPTR location);

		ARRAY<DMKVertexObject> rawVertexBufferObject;
		ARRAY<DMKUniformBufferObject> uniformBUfferObjects;
		ARRAY<UI32> indexBufferObject;

		DMKVertexBufferDescriptor vertexDescriptor;
		DMKDataType indexBufferType = DMKDataType::DMK_DATA_TYPE_UI32;
	};
}

#endif // !_DYNAMIK_MESH_COMPONENT_H
