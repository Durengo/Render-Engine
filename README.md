# Render-Engine

First attempt at making a rendering engine with OpenGL API.

Libraries:

1. Dependencies: opengl, glew, debugbreak, glfw, glm, stb, imgui;
2. Currently not used: imguizmo, spdlog, yaml-ccp;

Currently, project is supported only by x64 systems.

CMakeLists.txt is set up to work right out of the box, but first, the necessary libraries must be acquired first. There
is a script in utility/linux/get_libraries_linux.sh to get all the libraries on linux (git is required).

For windows builds there is a batch file in /utility/windows/get_libraries_windows_vcpkg.bat that will get all the
libraries (currently it appears to be working poorly so just open a command prompt at utility/windows and run each
command from the batch file). Copy CMakeLists.txt and CMakeSettings.json to the root of the project.

Project: Ladder Logic Simulation

Currently, all the files related to this project are located at /Application.
