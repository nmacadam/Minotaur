# Minotaur
### Features
* Entity-Component System workflow
* 3D Model loading via Assimp

### Current Issues:
* Components do not support polymorphic retrieval (e.g., a BoxCollider cannot be retrieved as a Collider with getComponent\<Collider\>)
* Matrix transformation for parented transforms does not work
* Materials and lighting aren't quite finished

### WIP:
* Editor-based workflow
* Component polymorphism
* Entity/Component serializing/deserializing
* Text rendering with FreeType
* Physics integration
* Texture animation

### Roadmap:
* Skeletal animation
* Audio support
* Game demo example project
* Vulkan build

### Dependencies:
* [SDL](https://www.libsdl.org/) (using SDL2, SDL_image)
* OpenGL (using [GLEW](http://glew.sourceforge.net/))
* [Assimp](http://www.assimp.org/)
* [cereal](https://uscilab.github.io/cereal/index.html)
* [imgui](https://github.com/ocornut/imgui)
* [ReactPhysics3D](https://www.reactphysics3d.com/)
