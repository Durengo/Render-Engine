#!/bin/bash
echo "vcpkg setup"

git clone https://github.com/microsoft/vcpkg
cd vcpkg
./bootstrap-vcpkg.sh -disableMetrics
./vcpkg install opengl
./vcpkg install glfw3
./vcpkg install glew
./vcpkg install glm
./vcpkg install imgui
