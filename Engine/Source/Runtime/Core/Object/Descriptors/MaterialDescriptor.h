#pragma once
#ifndef _DYNAMIK_MATERIAL_DESCRIPTOR_H
#define _DYNAMIK_MATERIAL_DESCRIPTOR_H

/*
 Material Descriptor for the Dynamik Engine.

 Author:    Dhiraj Wishal
 Date:      17/05/2020
*/


namespace Dynamik
{
	/*
	 This object defines the basic components tied to the Dynamik Material system.
	*/
	class DMK_API DMKMaterialDescriptor {
	public:
		DMKMaterialDescriptor() {}
		virtual ~DMKMaterialDescriptor() {}
	};
}

#endif // !_DYNAMIK_MATERIAL_DESCRIPTOR_H
