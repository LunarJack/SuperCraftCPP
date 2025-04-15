cmake_minimum_required(VERSION 3.15...3.31)

set(GLM_SHARED OFF)
set(GLM_STATIC ON)

project(SuperCraftCPP VERSION 0.1 LANGUAGES CXX C)

add_subdirectory(lib/glfw)

add_executable(SuperCraft src/main.cpp src/shader.cpp)

set_property(TARGET SuperCraft PROPERTY CXX_STANDARD 23)

target_link_libraries(SuperCraft glm glfw glew_s)

add_subdirectory(lib/glm/)

add_subdirectory(lib/glew-2.1.0/build/cmake)

target_include_directories(SuperCraft PUBLIC include lib/glfw/include lib/glew-2.1.0/include lib/glm)