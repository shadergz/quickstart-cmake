cmake_minimum_required(VERSION 3.29)
project(SDL2Window)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL)
add_subdirectory(external/glm)
add_subdirectory(external/SDL)

add_executable(window)

target_sources(window PRIVATE
    main.cpp
)

target_link_libraries(window PRIVATE GL glm::glm SDL2-static)
