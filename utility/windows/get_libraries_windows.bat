@echo off
title Get Libraries for Windows
echo Everything this script does is clone all git repositories.

md ..\..\vendor
cd ..\..\vendor

Rem Get glew
git clone https://github.com/nigels-com/glew.git
Rem Get debugbreak
git clone https://github.com/scottt/debugbreak.git
Rem Get glfw
git clone https://github.com/glfw/glfw.git
Rem Get glm
git clone https://github.com/g-truc/glm.git
Rem Get stb
git clone https://github.com/nothings/stb.git
Rem Get imgui
git clone https://github.com/ocornut/imgui
move imgui\backends\imgui_impl_opengl3.cpp imgui
move imgui\backends\imgui_impl_opengl3.h imgui
move imgui\backends\imgui_impl_opengl3_loader.h imgui
move imgui\backends\imgui_impl_glfw.cpp imgui
move imgui\backends\imgui_impl_glfw.h imgui
rmdir imgui\backends /s/q
rmdir imgui\examples /s/q
rmdir imgui\misc /s/q
Rem Get imguizmo
git clone https://github.com/CedricGuillemet/ImGuizmo
Rem Get spdlog
git clone https://github.com/gabime/spdlog
Rem Get yaml-cpp
git clone https://github.com/jbeder/yaml-cpp