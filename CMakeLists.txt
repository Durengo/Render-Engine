cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
project(OpenGL)

set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(VCPKG_TARGET_TRIPLET x64-windows CACHE STRING "VCPKG Target Triplet to use")

include_directories(C:/vcpkg/installed/x64-windows/include)
LINK_DIRECTORIES(C:/vcpkg/installed/x64-windows/lib)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(imguizmo CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
#find_package(fmt CONFIG REQUIRED)

file(GLOB_RECURSE engine
        "${PROJECT_SOURCE_DIR}/source/Engine/*.h"
        "${PROJECT_SOURCE_DIR}/source/Engine/*.cpp"
        )

file(GLOB_RECURSE tests
        "${PROJECT_SOURCE_DIR}/source/tests/*.h"
        "${PROJECT_SOURCE_DIR}/source/tests/*.cpp"
        )

# file(GLOB_RECURSE ladderlogic
#         #executable
#         "${PROJECT_SOURCE_DIR}/source/apps/main.cpp"
#         #ladderlogic source
#         "${PROJECT_SOURCE_DIR}/source/apps/ladderlogic/*.h"
#         "${PROJECT_SOURCE_DIR}/source/apps/ladderlogic/*.cpp"
#         )

add_executable(${PROJECT_NAME}
        ${engine}
        ${tests}
        )
        
        # add_executable(LadderLogic
        # ${ladderlogic}
        # )

find_path(STB_INCLUDE_DIRS "stb_c_lexer.h")
find_path(SCOTTT_DEBUGBREAK_INCLUDE_DIRS "debugbreak.h")
target_include_directories(OpenGL PRIVATE ${STB_INCLUDE_DIRS} ${SCOTTT_DEBUGBREAK_INCLUDE_DIRS})
target_link_libraries(OpenGL PRIVATE OpenGL::GL glfw GLEW::GLEW glm::glm imgui::imgui imguizmo::imguizmo spdlog::spdlog spdlog::spdlog_header_only yaml-cpp)

# add_custom_target(run
#         COMMAND ${PROJECT_NAME}
#         DEPENDS ${PROJECT_NAME}
#         WORKING_DIRECTORY ${CMAKE_PORJECT_DIR}
# )