# Notes

* Don't worry can use static lib's with Xcode and IOS just need wrappers https://www.chilkatsoft.com/xcode-link-static-lib.asp

# Plan for Game Engine

* Write for 2D first, mainly focusing on OpenGL for computers->However keeping in mind IOS
* Premake?
* Logging->SPD log ✅
* Window system ✅
* Event system ✅
* Renderer
  - Batch rendering ✅
  - QuadData ✅
    - Vertex arrays ✅
    - Vertex buffers ✅
    - Shaders ✅
    - Textures ✅
    - Texture atlas ✅
    - Position stuff->MVP ✅
  - Camera->Link to MVP ✅
  - Scenes
    - Contain entities
    - Basic lighting? ✅
  - Particle system ✅
  - GUI ✅
    - Widgets ✅
    - TextRenderer ✅
  - Cleanup system (delete OpenGL stuff in destructors etc)
* Clock->Like kivy
* Need different compilation things for each platform Windows, mac (can use .dylib's on IOS), linux->probably same as mac
* Need 2 versions for production and development->this contains logging stuff
* Support for IOS systems->still keep 2D->Objective C wrappers use: https://stackoverflow.com/questions/19229574/calling-c-from-objective-c
* Animation ✅
* Sound ✅
* Networking
* AI
* Profiling functions ✅
* Then optimise code->using char instead of string when possible for example
* Logging of stuff->go through and see->success as well as failure
* 3D support->Basically repeat above but for 3D system*
* Testing->Make a game best way

### MAY DO SUPPORT FOR CONSOLES IDK
