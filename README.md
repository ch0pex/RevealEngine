# RevealEngine

Reveal3D is a library that aims to bring a novel approach to development in industry, focusing on system performance and versatility. This library has been developed to make easier the creation of 3D rendering applications like RevealEngine for those users with no experience in computer graphics.

To achieve this goal, generic programming has been used, giving the project a unique style compared to industry standards. Specifically, C++20 templates and concepts have been used in order to make a multi backend and multiplatform system, always avoiding any cost overruns in performance.

The platform allows users to create their own three-dimensional scenes by importing their own 3D models and placing them in the virtual space through a high-level API. This API allows them to choose between different graphics backends such as DirectX12 and OpenGL, as well as giving them the opportunity to choose between different window frameworks, namely Win32 and Glfw. In addition, Reveal3D has several support modules that can be used by the user for the development of his application. Among them, the most important are a multiplatform mathematical module, a generic input system and a module to easily import 3D models.

## Features
- Multiple rendering backends 
  - DirectX12
  - OpenGL
- Multiple window manager backends
  - Win32
  - GLFW 
- Multiplatform
  - Windows: DirectX12 and OpenGL
  - Linux: OpenGL
 - Scene
   - Entity component system with data oriented design: Transform, geometry and script components
     - Transform: Local and World
     - Geometry: Mesh and submeshes instances
     - Script: Control entity behaviour
   - Scene graph: Entity and transform dependencies
   - Adding, editing and removing entities during execution
   - Entity input controller system
  - Rendering
    - HRI (Hardware rendering interface) implemented with generic programming
    - Ambient, diffuse and specular lighting
    - Directional lights
    - Triple frame buffering
      
### TODO
- Entity picking system
- Texture viewer
- PBR 
- Shadow mapping
- GPU frustum culling
- Ambient oclussion
- Rigidbody component
- Multithreading
- Multiviewport
- RenderGraph

![Screenshot 2024-06-20 172209](https://github.com/ch0pex/RevealEngine/assets/78793330/35b48290-900d-4322-ae69-f9f94d1bce61)

![Screenshot 2024-06-20 172340](https://github.com/ch0pex/RevealEngine/assets/78793330/64295e11-610d-4f31-9d46-9452c5a28e59)
