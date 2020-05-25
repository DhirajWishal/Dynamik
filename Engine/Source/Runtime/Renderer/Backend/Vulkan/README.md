# Dynamik Engine
## Vulkan Renderer Backend Layer

The Vulkan RBL consists of 3 major parts:
- Common (Contain common classes and functions for both conpute and graphics APIs)
- Compute (Contains the Dynamik Vulkan Compute API)
- Graphics (Contains the Dynamik Vulkan Graphics API)
  - Context
  - Primitives

This does not contain a deep inheritance hierarchy but contains a set of systems which manages components (PODs). This
way the RBL does not lose time in looking up virtual tables and will be much cache friendly.

The Dynamik Vulkan RBL Graphics API consists of 4 major systems:
- Vulkan Graphics Core
  - Vulkan Instance
  - Vulkan Queues
  - Vulkan Command Pool
  - Vulkan Devices (logical, physical)
- Vulkan Render Context
  - Vulkan SwapChain
  - Vulkan Render Pass
  - Vulkan Frame Buffer
  - Vulkan Frame Buffer Attachments
- Vulkan Renderables (Primitives)
  - Vulkan Render Component
    - Resource Buffers (Vertex, Index, Uniform)
    - Texture Resources 
  - Vulkan Descriptors
    - Descriptor Set Layout
    - Descriptor Pool
    - Descriptor Sets
  - Vulkan Render Pipeline
    - Pipeline Layout
    - Graphics Pipeline
- Vulkan Render Commands
  - One Time Command Buffer
  - Main Command Buffer
    - InFlight Command Buffer
    - Submit Pending Command Buffer

The draw call is devided into 3 phases:
- Frame Initialization
  - Select the current Rendering Context
  - Acquire next image from the Swap Chain
- Update Renderables
  - Update Vertex Buffers
  - Update Index Buffers
  - Update Uniform Buffers
  - Update Textures
- Submit Renderables

The termination of the RBL has 3 phases:
- Terminate Renderables
- Terminate Rendering Context
- Terminate Graphics Core

## Naming Convention
All the classes are in PascalCase. Member variables are in camelCase. Function paramters contain a "v" prefix to 
indicate that it is a Vulkan Base Component.