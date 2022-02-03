cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
project(OpenGL)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/vendor/debugbreak)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/glm)
include_directories(${PROJECT_SOURCE_DIR}/vendor/glm)
include_directories(${PROJECT_SOURCE_DIR}/vendor/stb)
include_directories(${PROJECT_SOURCE_DIR}/vendor/imgui)
include_directories(${PROJECT_SOURCE_DIR}/vendor/ImGuizmo)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/spdlog)
include_directories(${PROJECT_SOURCE_DIR}/vendor/spdlog/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/vendor/yaml-cpp)
include_directories(${PROJECT_SOURCE_DIR}/vendor/yaml-cpp/include)

file(GLOB_RECURSE main
        "${PROJECT_SOURCE_DIR}/source/Engine/main.cpp"
        )

file(GLOB_RECURSE engine
        "${PROJECT_SOURCE_DIR}/source/Engine/*.h"
        "${PROJECT_SOURCE_DIR}/source/Engine/*.cpp"
        )

file(GLOB_RECURSE tests
        "${PROJECT_SOURCE_DIR}/source/Engine/tests/*.h"
        "${PROJECT_SOURCE_DIR}/source/Engine/tests/*.cpp"
        )

file(GLOB_RECURSE imgui
        "${PROJECT_SOURCE_DIR}/vendor/imgui/*.h"
        "${PROJECT_SOURCE_DIR}/vendor/imgui/*.cpp"
        )

file(GLOB_RECURSE stb
        "${PROJECT_SOURCE_DIR}/vendor/std_image/*.h"
        )

file(GLOB_RECURSE app
        "${PROJECT_SOURCE_DIR}/source/Application/LadderLogic/*.h"
        "${PROJECT_SOURCE_DIR}/source/Application/LadderLogic/*.cpp"
        )

add_executable(App
        ${app}
        ${imgui}
        ${stb}
        )

add_executable(OpenGL
        ${main}
        ${engine}
        ${imgui}
        ${tests}
        ${stb}
        )

target_link_libraries(OpenGL PRIVATE OpenGL::GL glfw GLEW::GLEW)
target_link_libraries(App PRIVATE OpenGL::GL glfw GLEW::GLEW)