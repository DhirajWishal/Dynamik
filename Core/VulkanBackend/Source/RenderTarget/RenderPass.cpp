// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "VulkanBackend/RenderTarget/RenderPass.h"
#include "VulkanBackend/Common/VulkanDevice.h"
#include "Core/ErrorHandler/Logger.h"

namespace DMK
{
	namespace VulkanBackend
	{
		RenderPassHandle VulkanDevice::CreateRenderPass(const std::vector<GraphicsCore::RenderTargetAttachmentHandle>& mAttachments, std::vector<VkSubpassDependency> vDependencies)
		{
			// Create the render pass object.
			RenderPass vRenderPass = {};

			// Initialize the render pass.
			vRenderPass.Initialize(*this, mAttachments, vDependencies);

			// Add the render pass to the vector and return its handle.
			vRenderPasses.insert(vRenderPasses.end(), std::move(vRenderPass));
			return vRenderPasses.size() - 1;
		}

		void VulkanDevice::DestroyRenderPass(const RenderPassHandle& mHandle)
		{
			// Terminate the required render pass.
			(vRenderPasses.data() + mHandle)->Terminate(*this);

			// Remove it from the vector.
			vRenderPasses.erase(vRenderPasses.begin() + mHandle);
		}

		void VulkanDevice::DestroyAllRenderPasses()
		{
			// Iterate through and terminate all the render passes.
			for (auto itr = vRenderPasses.begin(); itr != vRenderPasses.end(); itr++)
				itr->Terminate(*this);

			// Clear the vector.
			vRenderPasses.clear();
		}

		RenderPass* VulkanDevice::GetRenderPass(RenderPassHandle mHandle) const
		{
			return const_cast<RenderPass*>(vRenderPasses.data() + mHandle);
		}

		/**
		 * Subpass Attachment References.
		 */
		struct SubpassAttachmenReferences {
			std::vector<VkAttachmentReference> vColorAttachmentRefs;
			std::vector<VkAttachmentReference> vDepthAttachmentRefs;
			std::vector<VkAttachmentReference> vResolveAttachments;
			std::vector<VkAttachmentReference> vInputAttachments;
		};

		void RenderPass::Initialize(const VulkanDevice& vDevice, std::vector<GraphicsCore::RenderTargetAttachmentHandle> mAttachments, std::vector<VkSubpassDependency> vDependencies)
		{
			std::vector<VkAttachmentDescription> vDescriptions;
			SubpassAttachmenReferences vSubpassAttRefs = {};

			VkAttachmentReference vAttRef = {};
			vAttRef.attachment = 0;
			vAttRef.layout = VK_IMAGE_LAYOUT_UNDEFINED;

			for (auto itr = mAttachments.begin(); itr != mAttachments.end(); itr++)
			{
				switch (itr->mType)
				{
				case DMK::GraphicsCore::RenderTargetAttachmentType::SWAP_CHAIN:
				{
					auto ptr = vDevice.vSwapChains.data() + itr->mHandle;
					vDescriptions.insert(vDescriptions.end(), ptr->GetAttachmentDescription());
					vAttRef.layout = ptr->GetAttachmentLayout();

					vSubpassAttRefs.vResolveAttachments.insert(vSubpassAttRefs.vResolveAttachments.end(), vAttRef);

					break;
				}
				case DMK::GraphicsCore::RenderTargetAttachmentType::COLOR_BUFFER:
				{
					auto ptr = vDevice.vColorBuffers.data() + itr->mHandle;
					vDescriptions.insert(vDescriptions.end(), ptr->GetAttachmentDescription());
					vAttRef.layout = ptr->GetAttachmentLayout();

					vSubpassAttRefs.vDepthAttachmentRefs.insert(vSubpassAttRefs.vDepthAttachmentRefs.end(), vAttRef);

					break;
				}
				case DMK::GraphicsCore::RenderTargetAttachmentType::DEPTH_BUFFER:
				{
					auto ptr = vDevice.vDepthBuffers.data() + itr->mHandle;
					vDescriptions.insert(vDescriptions.end(), ptr->GetAttachmentDescription());
					vAttRef.layout = ptr->GetAttachmentLayout();

					vSubpassAttRefs.vColorAttachmentRefs.insert(vSubpassAttRefs.vColorAttachmentRefs.end(), vAttRef);

					break;
				}
				default:
					Logger::LogError(TEXT("Invalid Render Target Attachment Type!"));
					break;
				}

				vAttRef.attachment++;
			}

			VkSubpassDescription vSubpass = {};
			vSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			vSubpass.colorAttachmentCount = static_cast<UI32>(vSubpassAttRefs.vColorAttachmentRefs.size());
			vSubpass.pColorAttachments = vSubpassAttRefs.vColorAttachmentRefs.data();
			vSubpass.inputAttachmentCount = static_cast<UI32>(vSubpassAttRefs.vInputAttachments.size());
			vSubpass.pInputAttachments = vSubpassAttRefs.vInputAttachments.data();
			vSubpass.pDepthStencilAttachment = vSubpassAttRefs.vDepthAttachmentRefs.data();
			vSubpass.pResolveAttachments = vSubpassAttRefs.vResolveAttachments.data();
			vSubpass.preserveAttachmentCount = 0;
			vSubpass.pPreserveAttachments = VK_NULL_HANDLE;

			VkRenderPassCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.attachmentCount = static_cast<UI32>(vDescriptions.size());
			createInfo.pAttachments = vDescriptions.data();
			createInfo.subpassCount = 1;
			createInfo.pSubpasses = &vSubpass;
			createInfo.dependencyCount = static_cast<UI32>(vDependencies.size());
			createInfo.pDependencies = vDependencies.data();

			DMK_VK_ASSERT(vkCreateRenderPass(vDevice, &createInfo, nullptr, &vRenderPass), "Failed to create the Vulkan Render Pass!");
		}

		void RenderPass::Terminate(const VulkanDevice& vDevice)
		{
			vkDestroyRenderPass(vDevice, vRenderPass, nullptr);
		}
	}
}