// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#define SETUP_FUNCTION_POINTER(ret, name, ...)		ret (*name) (__VA_ARGS__) = nullptr
#define SETUP_BASIC_FUNCTION_POINTER(name, ...)		SETUP_FUNCTION_POINTER(void, name, __VA_ARGS__)
