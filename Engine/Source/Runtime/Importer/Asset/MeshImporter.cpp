#include "dmkafx.h"
#include "MeshImporter.h"

#include "Object/Resource/Primitives.h"

namespace Dynamik
{
	POINTER<DMKMeshComponent> DMKMeshImporter::loadMesh(const STRING& path, const DMKVertexBufferDescriptor& vertexBufferDescriptor)
	{
		return POINTER<DMKMeshComponent>();
	}

	void DMKMeshImporter::unloadMesh(const POINTER<DMKMeshComponent>& mesh)
	{
	}
}