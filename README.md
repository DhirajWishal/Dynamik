![Dynamik Engine Logo](https://github.com/DhirajWishal/Dynamik/blob/master/Dependencies/Assets/icons/Samples/DynamikL.png)
# 
Dynamik Engine is a community driven, high performance, game engine currently at its early stages and 
is primarily targeted on 3D FPS games.
The engine is intended to support Windows, Linux and MacOS.

#### The engine is currently at its very early stages and is not guaranteed to run on any other platforms and/or devices.

### Basic Repository Structure
- Application: A test application to test client side programming.
- Builds: An automatically created folder which contains all the build outputs.
- Dependencies: This folder contains all the dependencies (Assets, Libraries, ...) used by the engine.
  - Assets: Contains all the assets (icons, ...) the engine requires.
  - Libraries: Contains all the third party libraries.
    - Binaries: Binaries of some libraries.
    - External: Git cloned repositories.
    - Local: Locally stored copies of libraries.
  - Programs: Local programs which are not specific to the engine, but are developed by the author.
- Developer: This contains debug information generated from different applications.
- Documentation: All the engine documentation is stored here.
- Source: The source code of the engine is in this folder.
  - Engine: Contains all the engine source and header files.
  - Runtime: Contains all the runtime source and header files.
  - Studio: Contains all the studio source and header files.
- ThirdParty: Third party libraries which are built by the engine build system are stored here.

### First Run:
1. Double click (run/ execute) the GenProject.bat file.
2. Open the Dynamik.sln file in Visual Studio.
3. Select "Application" in the Solution Explorer as the StartUp Project if not selected by default.
4. Run the Build and Run the solution. 

### Developer notice
If anyone is interested to support this engine, please make sure to send me an email (wishaldhiraj@gmail.com)
and you can be a contributor of this engine.