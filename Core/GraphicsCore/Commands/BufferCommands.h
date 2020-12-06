// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "CommandBase.h"
#include "GraphicsCore/Backend/DeviceHandle.h"
#include "GraphicsCore/Objects/BufferHandle.h"

namespace DMK
{
	namespace GraphicsCore
	{
		namespace Commands
		{
			/**
			 * Create Buffer Command.
			 * This command creates a stagging buffer and returns its handle.
			 */
			struct CreateBufferCommand : public CommandBase {
				/**
				 * Construct the handle using the size and the handle pointer.
				 *
				 * @param type: The buffer type.
				 * @param size: The size of the buffer. This size should not be 0.
				 * @param deviceHandle: The device which the buffer is bound to.
				 * @param pHandle: The handle pointer to store data. Default is nullptr.
				 */
				CreateBufferCommand(BufferType type, UI64 size, DeviceHandle deviceHandle, BufferHandle* pHandle = nullptr)
					: CommandBase(CommandType::CREATE_BUFFER), mType(type), mSize(size), mDeviceHandle(deviceHandle), pHandle(pHandle) {}

				DeviceHandle mDeviceHandle = {};	// The device the buffer is bound to.
				UI64 mSize = 0;	// The size of the buffer.
				BufferHandle* pHandle = nullptr;	// The handle object pointer.
				BufferType mType = BufferType::UNDEFINED;	// The buffer type.
			};

			/**
			 * Submit Data To Buffer Command.
			 * Using this command, data can be submitted to a perticular buffer.
			 */
			struct SubmitDataToBufferCommand : public CommandBase {
				/**
				 * Construct the command using the handle, data pointer, size and offset.
				 *
				 * @param handle: The buffer handle.
				 * @param deviceHandle: The device which the buffer is bound to.
				 * @param pData: The data pointer.
				 * @param size: The data size in bytes.
				 * @param offset: The offset in the buffer to store the data to. Default is 0.
				 */
				SubmitDataToBufferCommand(BufferHandle handle, DeviceHandle deviceHandle, void* pData, UI64 size, UI64 offset = 0)
					: CommandBase(CommandType::SUBMIT_DATA_TO_BUFFER), mHandle(handle), mDeviceHandle(deviceHandle), pData(pData), mSize(size), mOffset(offset) {}

				DeviceHandle mDeviceHandle = {};	// The device the buffer is bound to.
				BufferHandle mHandle = {};	// The buffer handle.
				UI64 mSize = 0;	// The size of the payload in bytes.
				UI64 mOffset = 0;	// The offset in the buffer to store the data.
				void* pData = nullptr;	// The data pointer.
			};
		}
	}
}