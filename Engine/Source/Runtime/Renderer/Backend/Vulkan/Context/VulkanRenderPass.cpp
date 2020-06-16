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

		void VulkanRenderPass::initialize(POINTER<RCoreObject> pCoreObject, ARRAY<RSubPasses> aSubPasses, POINTER<RSwapChain> pSwapChain)
		{
			subPasses = aSubPasses;

			ARRAY<VkAttachmentDescription> _attachmenDescriptions;
			SubpassAttachmenReferences attachmentReferences;

			VkSubpassDescription subpass = {};
			subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
			subpass.colorAttachmentCount = 0;
			subpass.inputAttachmentCount = 0;
			subpass.preserveAttachmentCount = 0;

			for (auto _subpass : aSubPasses)
			{
				VulkanRenerPassAtachmentDescription _description;

				switch (_subpass)
				{
				case Dynamik::RSubPasses::SUBPASSES_SWAPCHAIN:
					/* Initialize sub passes */
					_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
					_description.format = (DMKFormat)InheritCast<VulkanSwapChain>(pSwapChain).format;
					_description.msaaSamples = pCoreObject->sampleCount;

					break;
				case Dynamik::RSubPasses::SUBPASSES_DEPTH:
					/* Initialize sub passes */
					_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH;
					_description.format = (DMKFormat)VulkanUtilities::findDepthFormat(Inherit<VulkanCoreObject>(pCoreObject)->device);
					_description.msaaSamples = pCoreObject->sampleCount;

					break;
				case Dynamik::RSubPasses::SUBPASSES_COLOR:
					/* Initialize sub passes */
					_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR;
					_description.format = (DMKFormat)InheritCast<VulkanSwapChain>(pSwapChain).format;
					_description.msaaSamples = DMKSampleCount::DMK_SAMPLE_COUNT_1_BIT;

					break;
				case Dynamik::RSubPasses::SUBPASSES_OVERLAY:
					/* Initialize sub passes */
					_description.attachment = RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN;
					_description.format = (DMKFormat)InheritCast<VulkanSwapChain>(pSwapChain).format;
					_description.msaaSamples = pCoreObject->sampleCount;

					break;
				default:
					break;
				}

				switch (_description.attachment)
				{
				case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN:
				{
					VkAttachmentDescription description;
					description.flags = VK_NULL_HANDLE;
					description.format = VulkanUtilities::getVulkanFormat(_description.format);
					description.samples = (VkSampleCountFlagBits)_description.msaaSamples;
					description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					_attachmenDescriptions.pushBack(description);

					VkAttachmentReference attachmentReference = {};
					attachmentReference.attachment = 1;
					attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

					attachmentReferences.colorAttachmentRefs.pushBack(attachmentReference);
					subpass.colorAttachmentCount++;
				}
				break;

				case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH:
				{
					VkAttachmentDescription depthAttachment = {};
					depthAttachment.flags = VK_NULL_HANDLE;
					depthAttachment.format = VulkanUtilities::findDepthFormat(Inherit<VulkanCoreObject>(pCoreObject)->device);
					depthAttachment.samples = (VkSampleCountFlagBits)_description.msaaSamples;
					depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
					depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					_attachmenDescriptions.pushBack(depthAttachment);

					VkAttachmentReference depthAttachmentRef = {};
					depthAttachmentRef.attachment = 1;
					depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
					attachmentReferences.depthAttachmentRefs.pushBack(depthAttachmentRef);
				}
				break;

				case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR:
				{
					VkAttachmentDescription colorAttachmentResolve = {};
					colorAttachmentResolve.flags = VK_NULL_HANDLE;
					colorAttachmentResolve.format = VulkanUtilities::getVulkanFormat(_description.format);
					colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
					colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
					colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
					colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
					colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
					colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
					_attachmenDescriptions.pushBack(colorAttachmentResolve);

					VkAttachmentReference colorAttachmentResolveRef = {};
					colorAttachmentResolveRef.attachment = 1;
					colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
					attachmentReferences.resolveAttachments.pushBack(colorAttachmentResolveRef);
				}
				break;

				case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_OVERLAY:
				{
				}
				break;

				default:
					DMK_ERROR_BOX("Invalid Render Pass attachment description!");
					break;
				}
			}

			subpass.pColorAttachments = attachmentReferences.colorAttachmentRefs.data();
			subpass.pDepthStencilAttachment = attachmentReferences.depthAttachmentRefs.data();
			subpass.pInputAttachments = attachmentReferences.inputAttachments.data();
			subpass.pResolveAttachments = attachmentReferences.resolveAttachments.data();
			subpass.pPreserveAttachments = VK_NULL_HANDLE;

			VkSubpassDependency dependency = {};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;	/* TODO */
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;	/* TODO */
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			VkRenderPassCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			createInfo.pNext = VK_NULL_HANDLE;
			createInfo.flags = VK_NULL_HANDLE;
			createInfo.attachmentCount = _attachmenDescriptions.size();
			createInfo.pAttachments = _attachmenDescriptions.data();
			createInfo.subpassCount = 1;
			createInfo.pSubpasses = &subpass;
			createInfo.dependencyCount = 1;		/* TODO */
			createInfo.pDependencies = &dependency;		/* TODO */

			DMK_VULKAN_ASSERT(vkCreateRenderPass(Inherit<VulkanCoreObject>(pCoreObject)->device, &createInfo, nullptr, &renderPass), "Failed to create the Render Pass!");
		}

		void VulkanRenderPass::terminate(POINTER<RCoreObject> pCoreObject)
		{
			vkDestroyRenderPass(Inherit<VulkanCoreObject>(pCoreObject)->device, renderPass, nullptr);
		}

		VulkanRenderPass::operator VkRenderPass() const
		{
			return this->renderPass;
		}
	}
}