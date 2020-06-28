// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once
#ifndef _DYNAMIK_GUI_SHADER_H
#define _DYNAMIK_GUI_SHADER_H

/*
 Author:    Dhiraj Wishal
 Date:      24/05/2020
*/

#include "Types/DataTypes.h"
#include "Math/MathTypes.h"

#include <GLEW/glew-2.1.0/include/GL/glew.h>

namespace Dynamik
{
    /*
     GUI Shader object for the Dynamik Engine
     This object is taken from (https://learnopengl.com/Getting-started/Shaders)
    */
    class GUIShader
    {
    public:
        unsigned int ID;
        // constructor generates the shader on the fly
        // ------------------------------------------------------------------------
        GUIShader() : ID(0) {}
        GUIShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

        // activate the shader
        // ------------------------------------------------------------------------
        void use();

        // utility uniform functions
        // ------------------------------------------------------------------------
        void setBool(const STRING& name, bool value) const;

        // ------------------------------------------------------------------------
        void setInt(const STRING& name, int value) const;

        // ------------------------------------------------------------------------
        void setFloat(const STRING& name, float value) const;

        // ------------------------------------------------------------------------
        void setVec2(const STRING& name, const VEC2& value) const;
        void setVec2(const STRING& name, float x, float y) const;

        // ------------------------------------------------------------------------
        void setVec3(const STRING& name, const VEC3& value) const;
        void setVec3(const STRING& name, float x, float y, float z) const;

        // ------------------------------------------------------------------------
        void setVec4(const STRING& name, const VEC4& value) const;
        void setVec4(const STRING& name, float x, float y, float z, float w) const;

        // ------------------------------------------------------------------------
        void setMat2(const STRING& name, const MAT2F& mat) const;

        // ------------------------------------------------------------------------
        void setMat3(const STRING& name, const MAT3F& mat) const;

        // ------------------------------------------------------------------------
        void setMat4(const STRING& name, const MAT4F& mat) const;

    private:
        // utility function for checking shader compilation/linking errors.
        // ------------------------------------------------------------------------
        void checkCompileErrors(GLuint shader, STRING type);
    };
}

#endif // !_DYNAMIK_GUI_SHADER_H
