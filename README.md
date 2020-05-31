# Weight Engine Copyright &copy; KiloGram 2020. All rights reserved. Terms of use found in "LICENSE.md"

This is a game engine written in C++ which has/will have support for multiple platforms. From Desktop (Windows, Mac, Linux) to Mobile (IOS, Android) to consoles (PS4, Xbox, Nintendo Switch)

Currently the game engine uses (The licenses for these dependencies can be located within the licenses directory):
* OpenGL for graphics rendering (the only difference will be for the consoles with their different rendering API's)
* GLAD to allow for the OpenGL functions to be called
* OpenAL for audio
* GLFW for window creation and event dispatching
* GLM for maths operations such as transformation matrices
* SPDLog for logging data such as errors and information about the current runtime
* FreeType for loading fonts and generating a bitmap image

Licenses for OpenGL and OpenAL do not exist as they are standards

Features (Already written):
* Logging system
* Window with event system covering keyboard, mouse and gamepad input from a variety of different gamepads PS4 to Xbox
* 2D renderer with lighting, particles, animations
* Orthographic camera projection
* GUI system with full text rendering and support for TTF fonts
* Audio system which includes music and locational sound with abilities for dialogue
* Utilities to increase the productivity of code writing: time functions, maths, audio and profiling to help improve optimisation speed
