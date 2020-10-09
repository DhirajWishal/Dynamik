// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_MATERIAL_H
#define _DYNAMIK_MATERIAL_H

#include "Core/Types/ComplexTypes.h"
#include "Texture.h"

/*
 Dynamik Material Properties
 This object stores all the property values of a given material.
*/
class DMK_API DMKMaterialProperties {

	/* Material property structure */
	struct DMK_API MProperty {
		UI64 byteSize = 0;
		UI64 offset = 0;
	};

public:
	DMKMaterialProperties() {}
	~DMKMaterialProperties() {}

	/*
	 Add a property to the property list.
	 Property offsets are calculated internally.

	 @param name: The name of the property.
	 @param byteSize: The size of the property in bytes.
	*/
	void addProperty(const STRING& name, UI64 byteSize);

	/*
	 Initialize all the properties.
	 This method will allocate the property types in heap. Prior to this, properties must be added.
	*/
	void initialize();

	/*
	 Set data to a property.
	 This method sets data to a particular property in the property list. An additional offset can be added if
	 the property contains an array of data.
	 If the size argument is zero (which is the default), the data will be copied to the whole property (including
	 if the property contains an array).

	 @param name: The name of the property.
	 @param data: The data to be set.
	 @param size: The size of the data. Default is 0.
	 @param offset: The offset of the property in memory. Default is 0.
	*/
	void setData(const STRING& name, const VPTR data, UI64 size = 0, UI64 offset = 0);

	/*
	 Sets data to the whole property list.
	 The data block must not be less than the property sizes stored in the object.

	 @param data: The data to be set.
	*/
	void set(const VPTR data);

	/*
	 Get the stored property byte size using its name.

	 @param name: The name of the property.
	*/
	UI64 getPropertySize(const STRING& name);

	/*
	 Get the allocation offset of the property using its name.

	 @param name: The name of the property.
	*/
	UI64 getPropertyOffset(const STRING& name);

	/*
	 Get the total byte size of the object.
	*/
	const UI64 size() const;

	/*
	 Get the data store pointer.
	*/
	VPTR data() const;

	/*
	 Deallocates the property memory block.
	*/
	void clear();

private:
	std::unordered_map<STRING, MProperty> propertyMap;
	UI64 allocationSize = 0;
	VPTR pDataStore = nullptr;
};

/*
 Material Texture Type
 Defines a texture usage in the material system.
*/
enum class DMK_API MaterialTextureType {
	MATERIAL_TEXTURE_TYPE_DEFAULT,
	MATERIAL_TEXTURE_TYPE_DIFFUSE,
	MATERIAL_TEXTURE_TYPE_EMISSIVE,
	MATERIAL_TEXTURE_TYPE_NORMAL,
	MATERIAL_TEXTURE_TYPE_OPACITY,
	MATERIAL_TEXTURE_TYPE_SPECULAR,
	MATERIAL_TEXTURE_TYPE_GLOSS,
};

/*
 Dynamik Material Object
 This structure contains all the necessary information required to define a material.
*/
class DMK_API DMKMaterial {
	/* Material Texture Container Structure */
	struct DMK_API MTextureContainer {
		MaterialTextureType type = MaterialTextureType::MATERIAL_TEXTURE_TYPE_DEFAULT;
		DMKTexture* pTexture = nullptr;
	};

public:
	DMKMaterial() = default;
	DMKMaterial(STRING name, DMKColorComponent surface, DMKColorComponent subSurface, F32 roughness, F32 metalic)
		: name(name), surfaceColor(surface), subSurfaceColor(subSurface), roughness(roughness), metallicness(metalic) {}
	~DMKMaterial() = default;

	/*
	 Add a texture to the material.

	 @param pTexture: Dynamik texture.
	 @param textureType: Material texture type.
	*/
	void addTexture(DMKTexture* pTexture, MaterialTextureType textureType);

	/* Material Name */
	STRING name = TEXT("");

	/* Surface Color */
	DMKColorComponent surfaceColor;

	/* Sub Surface Color */
	DMKColorComponent subSurfaceColor;

	/* Roughness */
	F32 roughness = 0.0f;

	/* Metallicness */
	F32 metallicness = 0.0f;

	/* Specular */
	F32 specular = 0.0f;

	/* Textures */
	ARRAY<MTextureContainer> textureContainers;

	DMKMaterialProperties properties = {};

public:		/* Utility Functions */
	static DMKMaterial createMetalGold();
	static DMKMaterial createMetalCopper();
	static DMKMaterial createMetalChromium();
	static DMKMaterial createMetalNickel();
	static DMKMaterial createMetalTitanium();
	static DMKMaterial createMetalCobalt();
	static DMKMaterial createMetalPlatinum();

	static DMKMaterial createMetalWhite();
	static DMKMaterial createMetalRed();
	static DMKMaterial createMetalBlue();
	static DMKMaterial createMetalBlack();

	static DMKMaterial createDefaultTexture(const STRING& path, DMKTextureType type);

public:		/* Push Block Utilities */
	/*
	 This block is submitted to the shaders via constants.
	*/
	struct DMK_API MaterialPushBlock {
		MaterialPushBlock() = default;
		MaterialPushBlock(DMKColorComponent surface, DMKColorComponent subSurface, F32 roughness, F32 metalic, F32 specular)
			: surfaceColor(surface), subSurfaceColor(subSurface), roughness(roughness), metallicness(metalic), specular(specular) {}
		~MaterialPushBlock() = default;

		DMKColorComponent surfaceColor;
		DMKColorComponent subSurfaceColor;
		F32 roughness = 0;
		F32 metallicness = 0;
		F32 specular = 0;
	};

	/*
	 Generate a push block using the current material.
	*/
	MaterialPushBlock generatePushBlock();
};

#endif // !_DYNAMIK_MATERIAL_H
