// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_PANEL_FACTORY_H
#define _DYNAMIK_PANEL_FACTORY_H

#include "Panel2D.h"

/* SINGLETON 
 Dynamik Panel Factory.
 This object creates new panels required by the UI system.
*/
class DMK_API DMKPanelFactory {
	DMKPanelFactory();
	~DMKPanelFactory();

	static DMKPanelFactory instance;
public:

};

#endif // !_DYNAMIK_PANEL_FACTORY_H
