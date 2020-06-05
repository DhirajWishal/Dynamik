#pragma once
#ifndef _APPLICATION_MOON_H
#define _APPLICATION_MOON_H

/*
 Author:	Dhiraj Wishal
 Date:		04/06/2020
*/
#include "GameLibrary/GameAssets/RenderableAsset.h"
using namespace Dynamik;

class Moon : public DMKRenderableAsset {
public:
	Moon() {}
	~Moon() {}

	void initialize() override;
};

#endif // !_APPLICATION_MOON_H
