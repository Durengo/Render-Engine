#!/bin/bash
echo "Everything this script does is clone all git repositories."

cd ../vendor
#Get glew
#git clone https://github.com/nigels-com/glew.git
#Get debugbreak
git clone https://github.com/scottt/debugbreak.git
#Get glfw
git clone https://github.com/glfw/glfw.git
#Get glm
git clone https://github.com/g-truc/glm.git
#Get stb
git clone https://github.com/nothings/stb.git
#Get imgui
git clone https://github.com/ocornut/imgui
mv imgui/backends/imgui_impl_opengl3.cpp imgui
mv imgui/backends/imgui_impl_opengl3.h imgui
mv imgui/backends/imgui_impl_opengl3_loader.h imgui
mv imgui/backends/imgui_impl_glfw.cpp imgui
mv imgui/backends/imgui_impl_glfw.h imgui
rm -r imgui/backends
rm -r imgui/examples
rm -r imgui/misc
#Get imguizmo
git clone https://github.com/CedricGuillemet/ImGuizmo
#Get spdlog
git clone https://github.com/gabime/spdlog
#Get yaml-cpp
git clone https://github.com/jbeder/yaml-cpp

