![Dynamik Logo](https://github.com/DhirajWishal/Dynamik/blob/new-architecture/Dependencies/Assets/icons/Samples/DynamikL.png)
Dynamik is a set of tools/ APIs which can be used to build a custom game engine. 

## Why Dynamik?
Dynamik allows game developers to build a fully functional game engines, targeting multiple platforms, in as little time as possible. The Dynamik Studio (which is yet to be made) will automate certain key areas and help developers to build something which before would be impossible.

## When to use Dynamik?
As a quick note, if your goal is to build a game in a short period of time, with a very limited budget, we don't recommend using Dynamik. For that purpose we recommend using a well reputed game engine. 
But if your product requires you to harness almost all the performance available, we definitely recommend using Dynamik. 

## How to use Dynamik?
Mainly there are two ways to use Dynamik,
- As a framework.
- Using the Dynamik Studio (currently unavailable).

### Dynamik as a Framework
To use Dynamik as a Framework, clone the release branch to the working directory of your project.
For this you need the GitHub Desktop application or the Git Bash application.

#### GitHub Desktop
File -> Clone repository -> Enter the URL and enter the path to clone the repository to -> Clone.

#### Git Bash
```bash
git clone https://github.com/DhirajWishal/Dynamik Dynamik
```

After cloning the repository, set the include file path of your project to the root path/ solution path of Dynamik. After building the repository or by downloading the binaries, place the include library path to `Builds/<Configuration>/`.  We **highly recommend** you including only the files and libraries that are used by your application.

## Build
Note: To build or use Dynamik, you are required to have Visual Studio installed with the C++ development modules pre installed. We highly recommend using [Visual Studio 2019](https://visualstudio.microsoft.com/vs/).

After cloning the repository to a local directory, run the `GenerateProjects.bat` file. This creates the required `.sln` and `.vcxproj` files. Then open the `Dynamik.sln` file in Visual Studio.

There are 3 project configurations that can be used,
- Debug.
- Release.
- Distribution.

We recommend building Dynamik in the `Release` configuration. The output binaries are stored in `Builds/<Configuration>/<Module name>/` directory.

##  Community 
 Join the [Discord](https://discord.gg/Tw5pQns) community to talk to me personally and to help:
