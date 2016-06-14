# GaneshEngine

GaneshEngine is an early lightweight game engine, with entity-component system, openGL 4 rendering and Lua scripting sytem.

It is still in development, i'm working on it by myself on my spare time. It's my third attempt/iteration to build a
game engine. The first try was with Java but I was not convinced this language could handle high performance requirement
and good memory management, furthermore I was looking for a new language to masterize.
Then I began a new one, with C++98 and the same architecture choices...it was a mistake ([Sources here][ccompoteplusplus]).

This new engine use :
 - C++14
 - gtest
 - doxygen in order to produce comprehensive documentation without too much pain
 - Better architecture than my previous attempt


#### Features done (or almost done) :
  - Profiling (basic, no really time display profiling sample)
  - Logging (support log level, console and file output)
  - Memory tools (PoolAllocator, StackAllocator, DoubleBufferedStackAllocator)

#### Features in progress :
  - Rendering system wrapping OpenGL

#### Features to come :
  - Plugin system (to interface other rendering api like vulkan or directX)
  - By now, almost everything else

## Version
0.1

## Dependencies

Here are the third-party tools used by ganeshEngine :

* [cmake] - For building, running several others tasks like tests or documentation generation
* [glm] - For math stuff
* [gtest] - To test sources
* [doxygen] - For documentation generation
* [opengl] - render api
* [glew] - opengl stuff
* [glfw] - opengl stuff


## Installation
> to do

License
----

MIT

[ccompoteplusplus]: <https://github.com/mcamier/CCompotePlusPlus>