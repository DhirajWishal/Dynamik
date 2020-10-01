// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanRenderPass.h"

#include "../VulkanUtilities.h"

namespace Backend
{
	/* Internal structure to contain all the references in a single subpass */
	struct SubpassAttachmenReferences {
		std::vector<VkAttachmentReference> colorAttachmentRefs;
		std::vector<VkAttachmentReference> depthAttachmentRefs;
		std::vector<VkAttachmentReference> resolveAttachments;
		std::vector<VkAttachmentReference> inputAttachments;
	};

	void VulkanRenderPass::initialize(RCoreObject* pCoreObject, std::vector<RSubpassAttachment> aSubPasses, std::vector<RSubpassDependency> dependencies, RSwapChain* pSwapChain, DMKFormat overrideFormat)
	{
		subPasses = aSubPasses;

		std::vector<VkAttachmentDescription> _attachmenDescriptions;
		SubpassAttachmenReferences attachmentReferences;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 0;
		subpass.inputAttachmentCount = 0;
		subpass.preserveAttachmentCount = 0;
		VkAttachmentReference attachmentReference = {};
		attachmentReference.attachment = 0;

		for (auto _subpass : aSubPasses)
		{
			VkAttachmentDescription description = {};
			description.flags = VK_NULL_HANDLE;
			description.format = VulkanUtilities::getVulkanFormat(_subpass.format);
			description.samples = Cast<VkSampleCountFlagBits>(_subpass.samples);
			description.loadOp = Cast<VkAttachmentLoadOp>(_subpass.loadOp);
			description.storeOp = Cast<VkAttachmentStoreOp>(_subpass.storeOp);
			description.stencilLoadOp = Cast<VkAttachmentLoadOp>(_subpass.stencilLoadOp);
			description.stencilStoreOp = Cast<VkAttachmentStoreOp>(_subpass.stencilStoreOp);
			description.initialLayout = VulkanUtilities::getVulkanLayout(_subpass.initialLayout);
			description.finalLayout = VulkanUtilities::getVulkanLayout(_subpass.finalLayout);

			switch (_subpass.subpass)
			{
			case RSubPasses::SUBPASSES_UNDEFINED:
				DMK_ERROR("Undefined subpass!");
				break;
			case RSubPasses::SUBPASSES_SWAPCHAIN:
			{
				_attachmenDescriptions.push_back(description);

				attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				attachmentReferences.resolveAttachments.push_back(attachmentReference);
			}
			break;

			case RSubPasses::SUBPASSES_DEPTH:
			{
				_attachmenDescriptions.push_back(description);

				attachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
				attachmentReferences.depthAttachmentRefs.push_back(attachmentReference);
			}
			break;

			case RSubPasses::SUBPASSES_COLOR:
			{
				_attachmenDescriptions.push_back(description);

				attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
				attachmentReferences.colorAttachmentRefs.push_back(attachmentReference);
				subpass.colorAttachmentCount++;
			}
			break;

			case RSubPasses::SUBPASSES_OVERLAY:
			{
			}
			break;

			default:
				DMK_ERROR_BOX("Invalid Render Pass attachment description!");
				break;
			}

			attachmentReference.attachment++;
		}

		subpass.pColorAttachments = attachmentReferences.colorAttachmentRefs.data();
		subpass.pDepthStencilAttachment = attachmentReferences.depthAttachmentRefs.data();
		subpass.pInputAttachments = attachmentReferences.inputAttachments.data();
		subpass.pResolveAttachments = attachmentReferences.resolveAttachments.data();
		subpass.pPreserveAttachments = VK_NULL_HANDLE;

		/* Subpass Dependencies */
		std::vector<VkSubpassDependency> subpassDependencies;
		VkSubpassDependency subpassDependency = {};
		for (auto dependency : dependencies)
		{
			subpassDependency.srcSubpass = dependency.srcSubpassIndex;
			subpassDependency.dstSubpass = dependency.dstSubpassIndex;
			subpassDependency.srcStageMask = dependency.srcPipelineStage;
			subpassDependency.dstStageMask = dependency.dstPipelineStage;
			subpassDependency.srcAccessMask = dependency.srcMemoryAccessType;
			subpassDependency.dstAccessMask = dependency.dstMemoryAccessType;
			subpassDependency.dependencyFlags = dependency.pipelineDependency;

			subpassDependencies.push_back(subpassDependency);
		}

		VkRenderPassCreateInfo createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		createInfo.pNext = VK_NULL_HANDLE;
		createInfo.flags = VK_NULL_HANDLE;
		createInfo.attachmentCount = Cast<UI32>(_attachmenDescriptions.size());
		createInfo.pAttachments = _attachmenDescriptions.data();
		createInfo.subpassCount = 1;
		createInfo.pSubpasses = &subpass;
		createInfo.dependencyCount = Cast<UI32>(subpassDependencies.size());
		createInfo.pDependencies = subpassDependencies.data();

		DMK_VULKAN_ASSERT(vkCreateRenderPass(pCoreObject->getAs<VulkanCoreObject>()->device, &createInfo, nullptr, &renderPass), "Failed to create the Render Pass!");
	}

	void VulkanRenderPass::terminate(RCoreObject* pCoreObject)
	{
		vkDestroyRenderPass(pCoreObject->getAs<VulkanCoreObject>()->device, renderPass, nullptr);
	}

	VulkanRenderPass::operator VkRenderPass() const
	{
		return this->renderPass;
	}
}
