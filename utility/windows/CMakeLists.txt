cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
project(OpenGL)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

file(GLOB_RECURSE engine
        "${PROJECT_SOURCE_DIR}/source/Engine/*.h"
        "${PROJECT_SOURCE_DIR}/source/Engine/*.cpp"
        )

file(GLOB_RECURSE tests
        "${PROJECT_SOURCE_DIR}/source/tests/*.h"
        "${PROJECT_SOURCE_DIR}/source/tests/*.cpp"
        )

add_executable(${PROJECT_NAME}
        ${engine}
        ${tests}
        #${imgui}
        #${stb}
        )

target_include_directories(OpenGL PRIVATE ${STB_INCLUDE_DIRS} ${SCOTTT_DEBUGBREAK_INCLUDE_DIRS})
target_link_libraries(OpenGL PRIVATE OpenGL::GL glfw GLEW::GLEW imgui::imgui imguizmo::imguizmo spdlog::spdlog spdlog::spdlog_header_only yaml-cpp)