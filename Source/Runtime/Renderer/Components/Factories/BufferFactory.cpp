#include "dmkafx.h"
#include "BufferFactory.h"

#include "Renderer/Backend/Vulkan/Primitives/VulkanBuffer.h"

namespace Dynamik
{
    using namespace Backend;

    void DMKBufferFactory::setDefaults(DMKRenderingAPI api, RCoreObject* pCoreObject)
    {
        myRenderingAPI = api;
        myCoreObject = pCoreObject;
    }

    RBuffer* DMKBufferFactory::createVertexBuffer(UI64 uSize, RResourceMemoryType memoryType)
    {
        switch (myRenderingAPI)
        {
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
        {
            auto _ptr = StaticAllocator<VulkanBuffer>::allocate();
            _ptr->initialize(myCoreObject, RBufferType::BUFFER_TYPE_VERTEX, uSize, memoryType);
            return _ptr;
        }
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
            break;
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
            break;
        default:
            break;
        }

        return nullptr;
    }

    RBuffer* DMKBufferFactory::createIndexBuffer(UI64 uSize, RResourceMemoryType memoryType)
    {
        switch (myRenderingAPI)
        {
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
        {
            auto _ptr = StaticAllocator<VulkanBuffer>::allocate();
            _ptr->initialize(myCoreObject, RBufferType::BUFFER_TYPE_INDEX, uSize, memoryType);
            return _ptr;
        }
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
            break;
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
            break;
        default:
            break;
        }

        return nullptr;
    }

    RBuffer* DMKBufferFactory::createUniformBuffer(UI64 uSize, RResourceMemoryType memoryType)
    {
        switch (myRenderingAPI)
        {
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
        {
            auto _ptr = StaticAllocator<VulkanBuffer>::allocate();
            _ptr->initialize(myCoreObject, RBufferType::BUFFER_TYPE_UNIFORM, uSize, memoryType);
            return _ptr;
        }
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
            break;
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
            break;
        default:
            break;
        }

        return nullptr;
    }

    RBuffer* DMKBufferFactory::createStaggingBuffer(UI64 uSize, RResourceMemoryType memoryType)
    {
        switch (myRenderingAPI)
        {
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_VULKAN:
        {
            auto _ptr = StaticAllocator<VulkanBuffer>::allocate();
            _ptr->initialize(myCoreObject, RBufferType::BUFFER_TYPE_STAGGING, uSize, memoryType);
            return _ptr;
        }
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_DIRECTX:
            break;
        case Dynamik::DMKRenderingAPI::DMK_RENDERING_API_OPENGL:
            break;
        default:
            break;
        }

        return nullptr;
    }
}
