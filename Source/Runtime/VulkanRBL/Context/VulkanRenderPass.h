// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_VULKAN_RENDER_PASS_H
#define _DYNAMIK_VULKAN_RENDER_PASS_H

#include "Renderer/Components/Context/RRenderPass.h"

#include "../Common/VulkanDevice.h"
#include "Renderer/Components/ContextTypeDefs.h"
#include "Renderer/Components/CoreTypeDefs.h"

namespace Backend
{
	/*
	 Vulkan Render Pass object for the Dynamik RBL
	*/
	class DMK_API VulkanRenderPass : public RRenderPass {
	public:
		VulkanRenderPass() {}
		~VulkanRenderPass() {}

		virtual void initialize(RCoreObject* pCoreObject, ARRAY<RSubpassAttachment> aSubPasses, ARRAY<RSubpassDependency> dependencies, RSwapChain* pSwapChain, DMKFormat overrideFormat = DMKFormat::DMK_FORMAT_UNDEFINED) override final;
		virtual void terminate(RCoreObject* pCoreObject) override;

		operator VkRenderPass() const;

		VkRenderPass renderPass = VK_NULL_HANDLE;
	};
}

#endif // !_DYNAMIK_VULKAN_RENDER_PASS_H
