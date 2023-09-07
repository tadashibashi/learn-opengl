cmake_minimum_required(VERSION 3.26)
project(learn-opengl)

add_subdirectory(lib)

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(learn-opengl src/main.cpp)
target_link_libraries(learn-opengl PRIVATE
        glad
        spdlog::spdlog
        OpenGL::GL
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> SDL2::SDL2-static
)
