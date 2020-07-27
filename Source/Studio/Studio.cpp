// Copyright 2020 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#include "dmkafx.h"
#include "Studio.h"

#include "Core/Types/StaticArray.h"

#include "Services/SystemLocator.h"
#include "Services/RuntimeSystems/AssetRegistry.h"
#include "Services/RuntimeSystems/ToolsRegistry.h"

#include "Renderer/Renderer.h"

#include "Window/Windows/WindowsWindow.h"

namespace Dynamik
{
	DMKStudio::DMKStudio()
	{
		DMK_INFO("Welcome to the Dynamik Studio!");
		imGuiWrapper.initialize();

		/* Create the runtime systems. */
		DMKSystemLocator::createSystem<DMKRenderer>();
		DMKSystemLocator::getSystem<DMKRenderer>()->initializeThread();

		/* Initialize the event pool. */
		myEventPool.initialize();

		/* Initialize the window. */
		pActiveWindow = createWindowHandle(1280, 720, "Dynamik Studio");

		/* Set the default asset registry path. */
		{
			STRING _thisFilePath = __FILE__;
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			DMKAssetRegistry::setDefaultAssetBasePath(_thisFilePath + TEXT("\\Assets"));
			DMKAssetRegistry::initializeDefaultAssets();
		}

		/* Set the default tool registry path. */
		{
			STRING _thisFilePath = __FILE__;
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			_thisFilePath = _thisFilePath.substr(0, _thisFilePath.find_last_of("\\"));
			DMKToolsRegistry::setDefaultToolsBasePath(_thisFilePath + TEXT("\\Dependencies\\ThirdParty\\Binaries"));
			DMKToolsRegistry::initializeDefaultTools();
		}

		/* Initialize the runtime systems. */
		initializeRuntimeSystems();
	}

	DMKStudio::~DMKStudio()
	{
		DMK_INFO("Shutting down the Dynamik Studio!");
		imGuiWrapper.terminate();
	}

	void DMKStudio::initialize()
	{
	}

	void DMKStudio::execute()
	{
		/* Issue the pre draw call command to initialize all the rendering objects */
		DMKSystemLocator::getSystem<DMKRenderer>()->initializeFinalsCMD();

		struct UISettings {
			bool displayModels = true;
			bool displayLogos = true;
			bool displayBackground = true;
			bool animateLight = false;
			float lightSpeed = 0.25f;
			StaticArray<float, 50> frameTimes{};
			float frameTimeMin = 9999.0f, frameTimeMax = 0.0f;
			float lightTimer = 0.0f;
		} uiSettings;

		while (true)
		{
			/* TODO: Im gui commands. */
			{
				ImGui::NewFrame();


				ImGui::PlotLines("Frame Times", &uiSettings.frameTimes[0], 50, 0, "", uiSettings.frameTimeMin, uiSettings.frameTimeMax, ImVec2(0, 80));

				ImGui::Text("Camera");

				ImGui::SetNextWindowSize(ImVec2(200, 200));
				ImGui::Begin("Example settings");
				ImGui::Checkbox("Render models", &uiSettings.displayModels);
				ImGui::Checkbox("Display logos", &uiSettings.displayLogos);
				ImGui::Checkbox("Display background", &uiSettings.displayBackground);
				ImGui::Checkbox("Animate light", &uiSettings.animateLight);
				ImGui::SliderFloat("Light speed", &uiSettings.lightSpeed, 0.1f, 1.0f);
				ImGui::End();

				ImGui::SetNextWindowPos(ImVec2(650, 20));
				ImGui::ShowDemoWindow();

				// Render to generate draw buffers
				ImGui::Render();
			}

			imGuiWrapper.update();
		}
	}

	void DMKStudio::terminate()
	{
	}
	
	void DMKStudio::initializeRuntimeSystems()
	{
		/* Initialize the rendering engine. */
		{
			/* Set the window handle. */
			DMKSystemLocator::getSystem<DMKRenderer>()->setWindowHandleCMD(pActiveWindow);

			/* Issue the basic initialize command. */
			DMKSystemLocator::getSystem<DMKRenderer>()->initializeCMD();

			/* Create the rendering context */
			DMKSystemLocator::getSystem<DMKRenderer>()->createContextCMD(pActiveWindow->createViewport(512, 512, 0, 0), DMKRenderContextType::DMK_RENDER_CONTEXT_DEFAULT);
		}

		/* Initialize im gui. */
		{
			/* Initialize the basic context. */
			imGuiWrapper.initialize();

			/* Initialize the backend. */
			imGuiWrapper.initializeBackend();
		}
	}
	
	DMKWindowHandle* DMKStudio::createWindowHandle(I32 width, I32 height, STRING title)
	{
#ifdef DMK_PLATFORM_WINDOWS
		DMKWindowHandle* pHandle = StaticAllocator<WindowsWindow>::allocateInit(WindowsWindow(title, width, height));
		pHandle->initialize();
		pHandle->setEventBoard(&myEventPool);
		pHandle->initializeKeyBindings();
		pHandle->setEventCallbacks();

		return pHandle;

#endif // DMK_PLATFORM_WINDOWS

		return nullptr;
	}
}
