// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_STATIC_MODEL_ENTITY_H
#define _DYNAMIK_STATIC_MODEL_ENTITY_H

#include "Core/Math/Quaternion.h"
#include "Core/Math/Vector/Vector3F.h"
#include "Core/Objects/Resources/MeshObject.h"

/* Dynamik Resource Request */
enum class DMKResourceRequest {
	DMK_RESOURCE_REQUEST_BRDF_TABLE,
	DMK_RESOURCE_REQUEST_IRRADIANCE_CUBE,
	DMK_RESOURCE_REQUEST_PRE_FILTERED_CUBE,
};

/*
 Dynamik Static Model Entity
 This entity contains all the information for a static model. Basically this entity contains an array of mesh
 objects and is allowed to contain multiple instances.
*/
class DMK_API DMKStaticModelEntity {
public:
	DMKStaticModelEntity() {}
	virtual ~DMKStaticModelEntity() {}

	/*
	 On initialize static entity method.
	 This method is called once the entity is submitted to the renderer.
	*/
	virtual void onInitializeStaticEntity() {}

	/*
	 On update static entity method.
	 This method is called by the rendering engine.
	*/
	virtual void onUpdateStaticEntity() {}

	/*
	 On terminate static entity method. 
	 This method is called when the entity is being removed from the renderer. 
	*/
	virtual void onTerminateStaticEntity() {}

public:
	/*
	 Add an instance to the static model.

	 @param name: The name of the instance.
	 @param position: The position of the instance.
	 @param rotation: The rotation of the instance.
	 @param scale: The scale of the instance.
	*/
	void addInstance(const STRING& name, const Vector3F& position, const Quaternion& rotation, const Vector3F& scale) {}

	/*
	 Add a mesh object to the model.

	 @param meshObject: The mesh object to be added.
	*/
	void addMeshObject(const DMKMeshObject& meshObject);

	/*
	 Set the mesh objects of the model.

	 @param meshObjects: The mesh objects to be set.
	*/
	void setMeshObjects(ARRAY<DMKMeshObject> meshObjects);

	/*
	 Get the pointer to a mesh object using its index.

	 @param index: The index of the mesh object to be accessed.
	*/
	DMKMeshObject* getMeshObject(I64 index);

	/*
	 Get the pointer to the mesh objects.
	*/
	ARRAY<DMKMeshObject>* getMeshObjects();

	/* The mesh objects. */
	ARRAY<DMKMeshObject> meshObjects;

public:
	/*
	 Add a shader module.

	 @param sModule: The shader module.
	*/
	void addShaderModule(const DMKShaderModule& sModule);

	/*
	 Set the shader modules.

	 @param sModules: The shader modules to be set.
	*/
	void setShaderModules(ARRAY<DMKShaderModule> sModules);

	/*
	 Get a shader module stored in this object.

	 @param index: The index of the shader module.
	*/
	DMKShaderModule* getShaderModule(I32 index);

	/*
	 Get all the shaders stored in the object.
	*/
	ARRAY<DMKShaderModule> getShaders();

	/* The shader modules. */
	ARRAY<DMKShaderModule> shaders;

public:
	/*
	 Add a resource request to the object.

	 @param request: The request to be added.
	*/
	void addResourceRequest(const DMKResourceRequest& request);

	/*
	 Set the resource requests of the object.

	 @param requests: The requests to be set.
	*/
	void setResourceRequests(ARRAY<DMKResourceRequest> requests);

	/*
	 Get a resource request from the array.

	 @param index: The index of the request.
	*/
	DMKResourceRequest getResourceRequest(I64 index);

	/*
	 Get all the resource requests stored.
	*/
	ARRAY<DMKResourceRequest> getResourceRequests() const;

	/* Resource Requests */
	ARRAY<DMKResourceRequest> resourceRequests;

public:
	/*
	 Clear all the data in the static model (only from the mesh objects).
	*/
	void clearStaticModel();

	/* Render Data ID */
	UI64 renderDataID = 0;

	B1 isInitializedStaticModel = false;
};

#endif // !_DYNAMIK_STATIC_MODEL_ENTITY_H
