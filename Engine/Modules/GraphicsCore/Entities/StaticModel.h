// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GRAPHICS_CORE_STATIC_MODEL_H
#define _DYNAMIK_GRAPHICS_CORE_STATIC_MODEL_H

#include "GraphicsCore/Objects/Primitives.h"

namespace DMK
{
	class DMK_API StaticModel;

	/**
	 * Static Model Controller for the Dynamik Engine.
	 * This object us used to initialize, update and terminate a static model.
	 */
	class DMK_API StaticModelController {
	public:
		/**
		 * Default constructor.
		 */
		StaticModelController() {}

		/**
		 * Default destructor.
		 */
		virtual ~StaticModelController() {}

		/**
		 * Set a static model for the controller which it works on.
		 *
		 * @param pStaticModel: The static model to be set.
		 */
		void SetModel(StaticModel* pStaticModel) { this->pStaticModel = pStaticModel; }

		/**
		 * Get the stored static model pointer.
		 */
		StaticModel* GetStaticModel() const { return pStaticModel; }

		/**
		 * Initialize the static model controller method.
		 */
		virtual void Initialize() {}

	protected:
		StaticModel* pStaticModel = nullptr;
	};

	/**
	 * Static Model Entity for the Dynamik Engine.
	 * This object stores the final data of a static model after unitializing.
	 */
	class DMK_API StaticModel {
	public:
		/**
		 * Default constructor.
		 */
		StaticModel() {}

		/**
		 * Default destructor.
		 */
		~StaticModel() {}

		/**
		 * Set a static model controller for the static model.
		 *
		 * @param pController: The pointer of the controller.
		 */
		void SetController(StaticModelController* pController) { this->pController = pController; }

		/**
		 * Get the stored controller.
		 */
		StaticModelController* GetController() const { return pController; }

	private:
		StaticModelController* pController = nullptr;
	};
}

#endif // !_DYNAMIK_GRAPHICS_CORE_STATIC_MODEL_H
