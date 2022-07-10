cmake_minimum_required(VERSION 3.16)
project("T3Vtech-3")

#BASICALLY RELEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_CXX_FLAGS "-g -ggdb -fsanitize=address")
#SET(CMAKE_CXX_FLAGS "-g -Werror -Wall -Wextra")
SET(CMAKE_C_FLAGS "-O0 -g")
SET(CMAKE_CXX_FLAGS "-O0 -g -debug expr-source-pos")


#PROFILERMODE
#SET(CMAKE_CXX_FLAGS "-g -pg")

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_library(SDL2_mixer SDL2_mixer)
find_package(GLEW REQUIRED)
if (WIN32)
    find_package(OPENGL REQUIRED)
else()
    find_package(OpenGL REQUIRED)
endif()

find_package(OpenAL REQUIRED)

#creating the library
include_directories(src/engine/)
include_directories(vendor/stb/)
include_directories(vendor/Tlib/)
file(GLOB_RECURSE "engine" SRC src/engine/*.c)
add_library(T3Vtech STATIC ${engine})

target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_LIBRARIES}")
target_link_libraries(T3Vtech LINK_PRIVATE "${GLEW_LIBRARIES}")
target_link_libraries(T3Vtech LINK_PRIVATE "${OPENGL_LIBRARIES}")
target_link_libraries(T3Vtech LINK_PRIVATE "${OPENAL_LIBRARY}")
if (NOT MSVC)
    target_link_libraries(T3Vtech LINK_PRIVATE m)
endif()
target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_TTF_LIBRARY}")
#target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_mixer}")

include_directories("${SDL2_INCLUDE_DIRS}")
include_directories("${SDL2_TTF_INCLUDE_DIRS}")
include_directories("${GLEW_INCLUDE_DIR}")
include_directories("${OPENAL_INCLUDE_DIR}")

#creating the tests
file(GLOB_RECURSE "audio" SRC src/tests/audio/audio.c)
add_executable(audio WIN32 ${audio})
target_link_libraries(audio LINK_PRIVATE T3Vtech)

file(GLOB_RECURSE "input" SRC src/tests/input/input.c)
add_executable(input WIN32 ${input})
target_link_libraries(input LINK_PRIVATE T3Vtech)

file(GLOB_RECURSE "3d_textures" SRC src/tests/textures/3d_textures.c)
add_executable(3d_textures WIN32 ${3d_textures})
target_link_libraries(3d_textures LINK_PRIVATE T3Vtech)

file(GLOB_RECURSE "batch_rendering" SRC src/tests/batch_rendering/batch_rendering.c)
add_executable(batch_rendering WIN32 ${batch_rendering})
target_link_libraries(batch_rendering LINK_PRIVATE T3Vtech)

file(COPY shaders DESTINATION .)
file(COPY assets DESTINATION .)
file(COPY settings DESTINATION .)


#creating TTMV (T3Vtech-3 model viewer)
#file(GLOB_RECURSE "ttmv" SRC src/ttmv/*.cpp)
#include_directories(src/ttmv/)
#add_executable(TTMV WIN32 ${ttmv})
#target_link_libraries(TTMV LINK_PRIVATE T3Vtech)

#shooting range demo
#file(GLOB_RECURSE "shooting_range" SRC src/demo-shooting-range/*.cpp)
#include_directories(src/demo-shooting-range/)
#add_executable(shooting_range WIN32 ${shooting_range})
#target_link_libraries(shooting_range LINK_PRIVATE T3Vtech)
