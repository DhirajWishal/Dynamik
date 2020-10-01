// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _APPLICATION_CERBERUS_MODEL_ENTITY_H
#define _APPLICATION_CERBERUS_MODEL_ENTITY_H

#include "GameLibrary/Entities/StaticModelEntity.h"
#include "GameLibrary/Camera/CameraModule.h"
#include "Core/Types/StaticArray.h"

class CerberusModel final : public DMKStaticModelEntity {
public:
	CerberusModel() {}
	~CerberusModel() {}

	void setCameraModule(DMKCameraModule* pCameraModule);

	virtual void onInitializeStaticEntity() override final;
	virtual void onUpdateStaticEntity() override final;

	struct UniformVS {
		Matrix4F projection = Matrix4F::Identity;
		Matrix4F model = Matrix4F::Identity;
		Matrix4F view = Matrix4F::Identity;
		Vector3F camPos = Vector3F(0.0f);
	} dataVS;

	struct cameraParamsFS {
		Vector4F light1;
		Vector4F light2;
		Vector4F light3;
		Vector4F light4;
		float exposure = 4.5f;
		float gamma = 2.2f;
	} camParamFS;

	DMKCameraModule* pCameraModule = nullptr;
};

#endif // !_APPLICATION_CERBERUS_MODEL_ENTITY_H
