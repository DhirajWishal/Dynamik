#pragma once
#ifndef _DYNAMIK_STATIC_MESH_COMPONENT_H
#define _DYNAMIK_STATIC_MESH_COMPONENT_H

/*
 Static Mesh Component for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../MeshComponent.h"

namespace Dynamik
{
	/*
	 This class contains all the necessary mesh data of a static mesh.
	*/
	class DMK_API DMKStaticMeshComponent : public DMKMeshComponent {
	public:
		DMKStaticMeshComponent() : DMKMeshComponent(DMKMeshComponentType::DMK_MESH_COMPONENT_TYPE_STATIC) {}
		DMKStaticMeshComponent(const DMKVertexBufferDescriptor& descriptor, const DMKDataType& type)
			: DMKMeshComponent(DMKMeshComponentType::DMK_MESH_COMPONENT_TYPE_STATIC, descriptor, type) {}
		~DMKStaticMeshComponent() {}

		static DMKStaticMeshComponent& createStaticMesh(ARRAY<DMKVertexObject> vertexData);
	};
}

#endif // !_DYNAMIK_STATIC_MESH_COMPONENT_H
