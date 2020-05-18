#pragma once
#ifndef _DYNAMIK_OBJECT_H
#define _DYNAMIK_OBJECT_H

/*
 Dynamik Object component.

 Author:    Dhiraj Wishal
 Date:      14/05/2020
*/

#include "Macros/Assert.h"
#include "Macros/Global.h"
#include "Macros/MemoryMacro.h"
#include "Types/DataTypes.h"
#include "Types/Array.h"

/* Creates the basic content in a singleton */
#define DMK_CLASS_SINGLETON(className)		private:                                                \
												static className instance;							\
                                                                                                    \
											public:													\
												className(const className&) = delete;				\
												className(className&&) = delete;					\
												className& operator=(const className&) = delete;	\
												className& operator=(className&&) = delete;         

/* Implement the singleton instance */
#define DMK_CLASS_SINGLETON_IMPL(className)	className className::instance

/* Creates the basic contents in a functional class */
#define DMK_CLASS_FUNCTIONAL(className) 	private:                                                \
                                                className() {}                                      \
                                                ~className() {}                                     \
                                                                                                    \
                                            public:													\
                                        		className(const className&) = delete;				\
                                        		className(className&&) = delete;					\
                                        		className& operator=(const className&) = delete;	\
                                        		className& operator=(className&&) = delete;  

namespace Dynamik
{
	/*
	 Core object of the Dynamik Engine.
	 All the other class instances are derived from this.
	*/
	class DMK_API DMKObject {
	public:
		DMKObject() {}
		virtual ~DMKObject() {}
	};
}

#endif // !_DYNAMIK_OBJECT_H
