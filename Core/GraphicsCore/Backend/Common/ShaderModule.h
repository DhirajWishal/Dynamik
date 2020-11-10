// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_SHADER_MODULE_H
#define _DYNAMIK_GRAPHICS_SHADER_MODULE_H

#include "Core/Types/DataTypes.h"
#include <vector>

namespace DMK
{
	namespace GraphicsCore
	{
		class GDevice;

		/**
		 * Shader location enum.
		 */
		enum class ShaderLocation {
			SHADER_LOCATION_VERTEX,
			SHADER_LOCATION_TESSELLATION,
			SHADER_LOCATION_GEOMETRY,
			SHADER_LOCATION_FRAGMENT,

			SHADER_LOCATION_COMPUTE,
		};

		/**
		 * Shader Module for the Dynamik Engine.
		 * This object is created once a shader code is submitted to the graphics device.
		 */
		class ShaderModule {
			friend GDevice;	// Set the GDevice as a friend class.

		public:
			/**
			 * Default constructor.
			 */
			ShaderModule() {}

			/**
			 * Default destructor.
			 */
			~ShaderModule() {}

			/**
			 * Initialize the shader module.
			 *
			 * @param pAsset: The asset path.
			 * @param location: The shader location in the graphics pipeline.
			 */
			void Initialize(const wchar_t* pAsset, ShaderLocation location);

			/**
			 * Terminate the shader module.
			 */
			void Terminate();

			/**
			 * Set the backend data pointer.
			 *
			 * @param pBackendData: The backend data pointer.
			 */
			void SetBackendData(void* pBackendData) { this->pBackendData = pBackendData; }

			/**
			 * Get the backend data pointer.
			 *
			 * @return void pointer containing the backend data.
			 */
			void* GetBackendData() const { return pBackendData; }

		private:
			void (*InitializeShaderModule)(void* pBackendData, const std::vector<UI32>& shaderCode) = nullptr;	// Initializer function pointer.
			void (*TerminateShaderModule)(void* pBackendData) = nullptr;	// Terminate function pointer.
			void* pBackendData = nullptr;	// Backend data pointer.

			ShaderLocation location = ShaderLocation::SHADER_LOCATION_VERTEX;	// Shader location enum.
		};

		/**
		 * Once a shader code is created, its ID is returned. This ID can be used to access the shader at any time.
		 */
		typedef UI64 ShaderModuleID;
	}
}

#endif // !_DYNAMIK_GRAPHICS_SHADER_MODULE_H
