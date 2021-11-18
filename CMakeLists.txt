cmake_minimum_required(VERSION 3.16)
project("T3Vtech-3")

#BASICALLY RELEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_CXX_FLAGS "-g -ggdb -fsanitize=address")
SET(CMAKE_CXX_FLAGS "-g -Werror -Wall -Wextra")

#PROFILERMODE
#SET(CMAKE_CXX_FLAGS "-g -pg")

#SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
find_library(SDL2 SDL2)
find_library(SDL2_ttf SDL2_ttf)
find_library(SDL2_mixer SDL2_mixer)
find_library(GLEW GLEW)
find_library(GL GL)


#creating the library
include_directories(src/engine/)
include_directories(vendor/stb/)
file(GLOB_RECURSE "engine" SRC src/engine/*.c)
add_library(T3Vtech STATIC ${engine})

target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2}")
target_link_libraries(T3Vtech LINK_PRIVATE "${GLEW}")
#target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_ttf}")
#target_link_libraries(T3Vtech LINK_PRIVATE "${SDL2_mixer}")
#target_link_libraries(T3Vtech LINK_PRIVATE m)
#target_link_libraries(T3Vtech LINK_PRIVATE "${GL}")

#creating library test
file(GLOB_RECURSE "test" SRC src/test.c)
add_executable(test ${test})
target_link_libraries(test LINK_PRIVATE T3Vtech)
#file(COPY shaders DESTINATION .)
#file(COPY assets DESTINATION .)