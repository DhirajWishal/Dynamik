# Dynamik Engine
## Rendering Engine Architecture

The rendering engine is intended to support Vulkan, OpenGL, and DirectX 12. 
The rendering engine has two main parts:
- Renderer Abstraction Layer (RAL) - API agnostic.
- Renderer Backend Layer (RBL) - API specific.
  - Core Object
    - Instance
    - Device
      - Physical
      - Logical
    - Surface/ Window
    - Debugger
    - Sync Objects
  - Render Context
    - Render Target
      - Render Pass
      - Swap Chain
      - Frame Buffer
        - Attachments
  - Render Asset (Entity)
    - Index Buffer
    - Vertex Buffer
    - Textures
    - Uniform Buffer
    - Pipeline Object
      - Shader Module
      - Descriptors


### Vulkan RBL
...
...
...
Every Vulkan Shader module has its own descriptor set layout, a descriptor pool, and a descriptor set.
This means that every shader module has its own descriptor. These descriptor set layouts are passes to the 
pipeline layout to create the required pipeline using the shader code.