// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "DAIObject.h"

#define GET_SUB_STR		_line.substr(2, _line.size() - 2)

void DAIObject::load()
{
	if (myPath.find(".dai") == STRING::npos)
	{
		myBasePath = myPath;
		if ((myBasePath[myBasePath.size() - 1] != '/') || (myBasePath[myBasePath.size() - 1] != '\\'))
		{
			if (myBasePath.find('\\') != STRING::npos)
				myBasePath.push_back('\\');
			else
				myBasePath.push_back('/');
		}

		if (myPath[myPath.size() - 1] == '/')
			myPath.append("/modelData.dai");
		else if (myPath[myPath.size() - 1] == '\\')
			myPath.append("\\modelData.dai");
		else
			myPath.append("/modelData.dai");
	}

	myFile.open(myPath);

	if (!myFile.is_open())
	{
		DMKErrorManager::issueErrorBox("Unable to open the requested file! (@" + myPath + ")");
		return;
	}

	_loadContent();
}

inline void DAIObject::_loadContent()
{
	STRING _line = TEXT("");
	while (std::getline(myFile, _line))
	{
		if (_line[0] == '#') continue;
		else if (_line.size() < 2) continue;
		else if (_line[0] == 'M')	/* A model element has been found. Load that data to the store */
			meshes.push_back(myBasePath + GET_SUB_STR);
		else if (_line[0] == 'I')	/* A texture element has been found */
			textures.push_back(myBasePath + GET_SUB_STR);
		else if (_line[0] == 'V')	/* A vertex shader path has been found*/
			vertexShaders.push_back(myBasePath + GET_SUB_STR);
		else if (_line[0] == 'T')	/* A tessellation shader path has been found */
			tessellationShaders.push_back(myBasePath + GET_SUB_STR);
		else if (_line[0] == 'G')	/* A geometry shader path has been found */
			geometryShaders.push_back(myBasePath + GET_SUB_STR);
		else if (_line[0] == 'F')	/* A fragment shader path has been found */
			fragmentShaders.push_back(myBasePath + GET_SUB_STR);
	}
}
