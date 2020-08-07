#include "dmkafx.h"
#include "DebugComponent.h"

namespace Dynamik
{
    void DMKDebugComponent::setUniformBuffer(const DMKUniformBuffer& buffer)
    {
        uniformBuffer = buffer;
    }

    DMKUniformBuffer& DMKDebugComponent::getUniformBuffer()
    {
        return uniformBuffer;
    }

    void DMKDebugComponent::setVertexBuffer(const DMKVertexBuffer& buffer)
    {
        vertexBuffer = buffer;
    }

    DMKVertexBuffer& DMKDebugComponent::getVertexBuffer()
    {
        return vertexBuffer;
    }

    void DMKDebugComponent::setIndexBuffer(const ARRAY<UI32>& buffer)
    {
        indexBuffer = buffer;
    }

    DMKIndexBuffer& DMKDebugComponent::getIndexBuffer()
    {
        return indexBuffer;
    }

    void DMKDebugComponent::addMaterial(const DMKMaterial& material)
    {
        materials.pushBack(material);
    }

    void DMKDebugComponent::setMaterials(const ARRAY<DMKMaterial>& materials)
    {
        this->materials = materials;
    }

    DMKMaterial& DMKDebugComponent::getMaterial(const UI64& index)
    {
        return materials[index];
    }

    ARRAY<DMKMaterial>& DMKDebugComponent::getMaterials()
    {
        return materials;
    }
    void DMKDebugComponent::addShader(const DMKShaderModule& module)
    {
        shaders.pushBack(module);
    }

    void DMKDebugComponent::setShaders(const ARRAY<DMKShaderModule>& modules)
    {
        shaders = modules;
    }

    DMKShaderModule& DMKDebugComponent::getShader(const UI64& index)
    {
        return shaders[index];
    }

    ARRAY<DMKShaderModule>& DMKDebugComponent::getShaders()
    {
        return shaders;
    }
}
