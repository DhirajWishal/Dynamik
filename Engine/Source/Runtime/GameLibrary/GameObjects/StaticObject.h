#pragma once
#ifndef _DYNAMIK_STATIC_OBJECT_H
#define _DYNAMIK_STATIC_OBJECT_H

/*
 Dynamik Static Object for the Dynamik Game Library.

 Author:    Dhiraj Wishal
 Date:      15/05/2020
*/

#include "../GameAsset.h"

namespace Dynamik
{
	/*
	 Static Object for the Dynamik Engine.
	 These objects are the objects which the user cant directly interact with (eg: Rock, Tree, House, etc)
	 but the object can be manipulated by other objects.

	 Users are allowed to drag - drop objects or asset index files to the window which the object is bound.
	 If a bare object is placed, a debug texture will be mapped to it which the user is later required to
	 fill all the necesary data with. This will result in a new .dai (Dynamik Asset Index) file creation
	 on the path which the object file was located. By default these objects are handled as static objects
	 and later can be changed to any other object type.
	 Dropping an asset index file will result in proper initialization and proper handle of the object. The
	 object type must be stated in the .dai file or else it too will be initialized as a static object.
	*/
	class DMK_API DMKStaticObject : public DMKGameAsset {
	public:
		DMKStaticObject() : DMKGameAsset(DMKGameAssetType::DMK_GAME_ASSET_TYPE_STATIC) {}
		virtual ~DMKStaticObject() {}
	};
}

#endif // !_DYNAMIK_STATIC_OBJECT_H
