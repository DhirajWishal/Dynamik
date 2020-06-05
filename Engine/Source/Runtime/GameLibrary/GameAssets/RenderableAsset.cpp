#include "dmkafx.h"
#include "RenderableAsset.h"

#include "Importer/Asset/MeshImporter.h"

namespace Dynamik
{
	void DMKRenderableAsset::initialize()
	{
	}

	void DMKRenderableAsset::onUpdate(const DMKEventBuffer& eventBuffer)
	{
		for (auto mesh : meshComponents)
		{

		}
	}

	void DMKRenderableAsset::addToMeshStore(const DMKMeshComponent& component)
	{
		meshComponents.pushBack(component);
	}

	void DMKRenderableAsset::addToMeshStore(const ARRAY<DMKMeshComponent>& components)
	{
		meshComponents.insert(components);
	}
	
	ARRAY<DMKMeshComponent> DMKRenderableAsset::getMeshStore()
	{
		return meshComponents;
	}
}
