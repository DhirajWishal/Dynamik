// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main() 
{
    outColor = vec4(fragColor, 1.0f);
}