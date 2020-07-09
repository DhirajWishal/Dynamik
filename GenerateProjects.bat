REM Build third party libraries
REM Build GLFW
call cmake "ThirdParty/glfw/CMakeLists.txt"

REM Build Vulkan
call cmake "ThirdParty/Vulkan/CMakeLists.txt"

call Dependencies\Libraries\Local\premake5\premake5.exe vs2019
PAUSE