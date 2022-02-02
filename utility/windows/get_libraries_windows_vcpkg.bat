@echo off
title Get Libraries for Windows
echo Everything this script does is clone all git repositories.

md ..\..\vendor
cd ..\..\vendor

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat -disableMetrics
.\vcpkg install scottt-debugbreak:x64-windows
.\vcpkg install glfw3:x64-windows
.\vcpkg install glew:x64-windows
.\vcpkg install glm:x64-windows
.\vcpkg install stb:x64-windows
.\vcpkg install imgui[glfw-binding,opengl3-binding]:x64-windows
.\vcpkg install imguizmo:x64-windows
.\vcpkg install spdlog:x64-windows
.\vcpkg install yaml-cpp:x64-windows
.\vcpkg integrate install