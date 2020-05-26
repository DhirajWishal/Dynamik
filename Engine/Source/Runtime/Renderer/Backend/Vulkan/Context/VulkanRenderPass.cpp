#include "dmkafx.h"
#include "VulkanRenderPass.h"

#include "../Common/VulkanUtilities.h"

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

		void VulkanRenderPass::initialize(const VulkanDevice& vDevice, ARRAY<VulkanRenderPassSubpass> subPasses)
		{
			ARRAY<VkAttachmentDescription> _attachmenDescriptions;
			ARRAY<VkSubpassDescription> _subpasses;
			ARRAY<SubpassAttachmenReferences> references;

			UI32 subpassIndex = 0;
			for (auto _subpass : subPasses)
			{
				VkSubpassDescription subpass = {};
				subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
				subpass.colorAttachmentCount = 0;


				UI32 attachmentCount = 0;
				for (auto _attachment : _subpass.attachments)
				{
					VkAttachmentDescription description;

					switch (_attachment.attachment)
					{
					case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_SWAPCHAIN:
					{
						description.format = VulkanUtilities::getVulkanFormat(_attachment.format);
						description.samples = (VkSampleCountFlagBits)_attachment.msaaSamples;
						description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
						description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
						description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
						_attachmenDescriptions.pushBack(description);

						VkAttachmentReference attachmentReference = {};
						attachmentReference.attachment = attachmentCount;
						attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

						references[subpassIndex].colorAttachmentRefs.pushBack(attachmentReference);
						subpass.colorAttachmentCount++;
					}
					break;

					case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_DEPTH:
					{
						VkAttachmentDescription depthAttachment = {};
						depthAttachment.format = VulkanUtilities::findDepthFormat(vDevice);
						depthAttachment.samples = (VkSampleCountFlagBits)_attachment.msaaSamples;
						depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
						depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
						_attachmenDescriptions.pushBack(depthAttachment);

						VkAttachmentReference depthAttachmentRef = {};
						depthAttachmentRef.attachment = attachmentCount;
						depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
						references[subpassIndex].depthAttachmentRefs.pushBack(depthAttachmentRef);
					}
					break;

					case Dynamik::RenderPassAttachment::RENDER_PASS_ATTACHMENTS_COLOR:
					{
						VkAttachmentDescription colorAttachmentResolve = {};
						colorAttachmentResolve.format = VulkanUtilities::getVulkanFormat(_attachment.format);
						colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
						colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
						colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
						colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
						colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
						_attachmenDescriptions.pushBack(colorAttachmentResolve);

						VkAttachmentReference colorAttachmentResolveRef = {};
						colorAttachmentResolveRef.attachment = attachmentCount;
						colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
						references[subpassIndex].resolveAttachments.pushBack(colorAttachmentResolveRef);
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

					attachmentCount++;
				}

				subpass.colorAttachmentCount = references[subpassIndex].colorAttachmentRefs.size();
				subpass.pColorAttachments = references[subpassIndex].colorAttachmentRefs.data();
				subpass.pDepthStencilAttachment = references[subpassIndex].depthAttachmentRefs.data();
				subpass.preserveAttachmentCount = references[subpassIndex].resolveAttachments.size();
				subpass.pResolveAttachments = references[subpassIndex].resolveAttachments.data();
				subpass.inputAttachmentCount = references[subpassIndex].inputAttachments.size();
				subpass.pInputAttachments = references[subpassIndex].inputAttachments.data();
				_subpasses.pushBack(subpass);

				subpassIndex++;
			}

			VkSubpassDependency dependency = {};
			dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			dependency.dstSubpass = 0;	/* TODO */
			dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.srcAccessMask = 0;	/* TODO */
			dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
			dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

			VkRenderPassCreateInfo createInfo;
			createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			createInfo.attachmentCount = _attachmenDescriptions.size();
			createInfo.pAttachments = _attachmenDescriptions.data();
			createInfo.subpassCount = _subpasses.size();
			createInfo.pSubpasses = _subpasses.data();
			createInfo.dependencyCount = 1;		/* TODO */
			createInfo.pDependencies = &dependency;		/* TODO */

			DMK_VULKAN_ASSERT(vkCreateRenderPass(vDevice, &createInfo, nullptr, &renderPass), "Failed to create the Render Pass!");
		}

		void VulkanRenderPass::terminate(const VulkanDevice& vDevice)
		{
			vkDestroyRenderPass(vDevice, renderPass, nullptr);
		}

		VulkanRenderPass::operator VkRenderPass() const
		{
			return this->renderPass;
		}
	}
}