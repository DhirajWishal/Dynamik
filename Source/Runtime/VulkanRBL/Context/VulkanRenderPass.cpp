// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "VulkanRenderPass.h"

#include "../VulkanUtilities.h"

namespace Dynamik
{
	namespace Backend
	{
		/* Internal structure to contain all the references in a single subpass */
		struct SubpassAttachmenReferences {
			ARRAY<VkAttachmentReference> colorAttachmentRefs;
			ARRAY<VkAttachmentReference> depthAttachmentRefs;
			ARRAY<VkAttachmentReference> resolveAttachments;
			ARRAY<VkAttachmentReference> inputAttachments;
		};

		void VulkanRenderPass::initialize(RCoreObject* pCoreObject, ARRAY<RSubPasses> aSubPasses, ARRAY<RSubpassDependency> dependencies, RSwapChain* pSwapChain, DMKFormat overrideFormat)
		{
			subPasses = aSubPasses;

			ARRAY<VkAttachmentDescription> _attachmenDescriptions;
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
				switch (_subpass)
				{
				case Dynamik::RSubPasses::SUBPASSES_SWAPCHAIN:
				{
					VkAttachmentDescription colorAttachmentResolve = {};
					colorAttachmentResolve.flags = VK_NULL_HANDLE;

					if (pSwapChain)
						colorAttachmentResolve.format = VulkanUtilities::getVulkanFormat(pSwapChain->format);
					else
						colorAttachmentResolve.format = VulkanUtilities::getVulkanFormat(overrideFormat);
					
					colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
					colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					_attachmenDescriptions.pushBack(colorAttachmentResolve);

					attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					attachmentReferences.resolveAttachments.pushBack(attachmentReference);
				}
				break;

				case Dynamik::RSubPasses::SUBPASSES_DEPTH:
				{
					VkAttachmentDescription depthAttachment = {};
					depthAttachment.flags = VK_NULL_HANDLE;
					depthAttachment.format = VulkanUtilities::findDepthFormat(Inherit<VulkanCoreObject>(pCoreObject)->device);
					depthAttachment.samples = (VkSampleCountFlagBits)pCoreObject->sampleCount;
					depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					_attachmenDescriptions.pushBack(depthAttachment);

					attachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					attachmentReferences.depthAttachmentRefs.pushBack(attachmentReference);
				}
				break;

				case Dynamik::RSubPasses::SUBPASSES_COLOR:
				{
					VkAttachmentDescription description;
					description.flags = VK_NULL_HANDLE;

					if (pSwapChain)
						description.format = VulkanUtilities::getVulkanFormat(pSwapChain->format);
					else
						description.format = VulkanUtilities::getVulkanFormat(overrideFormat);

					description.samples = (VkSampleCountFlagBits)pCoreObject->sampleCount;
					description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					_attachmenDescriptions.pushBack(description);

					attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					attachmentReferences.colorAttachmentRefs.pushBack(attachmentReference);
					subpass.colorAttachmentCount++;
				}
				break;

				case Dynamik::RSubPasses::SUBPASSES_OVERLAY:
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
			ARRAY<VkSubpassDependency> subpassDependencies;
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

				subpassDependencies.pushBack(subpassDependency);
			}

			VkRenderPassCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.attachmentCount = Cast<UI32>(_attachmenDescriptions.size());
			createInfo.pAttachments = _attachmenDescriptions.data();
			createInfo.subpassCount = 1;
			createInfo.pSubpasses = &subpass;
			createInfo.dependencyCount = subpassDependencies.size();
			createInfo.pDependencies = subpassDependencies.data();

			DMK_VULKAN_ASSERT(vkCreateRenderPass(Inherit<VulkanCoreObject>(pCoreObject)->device, &createInfo, nullptr, &renderPass), "Failed to create the Render Pass!");
		}

		void VulkanRenderPass::terminate(RCoreObject* pCoreObject)
		{
			vkDestroyRenderPass(Inherit<VulkanCoreObject>(pCoreObject)->device, renderPass, nullptr);
		}

		VulkanRenderPass::operator VkRenderPass() const
		{
			return this->renderPass;
		}
	}
}