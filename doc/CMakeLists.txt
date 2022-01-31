#example CMakeLists.txt
#it can be used to easily start a new project with T3Vtech-3

cmake_minimum_required(VERSION 3.16)
project("res-racer") #the project's name

#BASICALLY RELEASE MODE
#SET(CMAKE_CXX_FLAGS  "-m64 -Ofast -flto -march=native -funroll-loops")

#DEBUGMODE
#SET(CMAKE_CXX_FLAGS "-g -ggdb -fsanitize=address")
#SET(CMAKE_CXX_FLAGS "-g")

#PROFILERMODE
SET(CMAKE_CXX_FLAGS "-g -pg")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(FindPkgConfig)
#the necessary libraries
find_library(SDL2 SDL2)
find_package(SDL2 REQUIRED)
find_library(GLEW GLEW)
find_library(GL GL)


#creating the executable
include_directories(src/) #where are your own headers?
include_directories(vendor/T3Vtech-3/src/engine/) #the engine headers
include_directories(vendor/T3Vtech-3/vendor/stb/) #an engine dependency
file(GLOB_RECURSE "engine" SRC vendor/T3Vtech-3/src/engine/*.c) #the engine source files
file(GLOB_RECURSE "game" SRC src/*.cpp) #where are your game source files
add_executable(res-racer ${engine} ${game}) #use the name of your game instead of res-racer

#linking all necessary libraries with the executable
target_link_libraries(res-racer LINK_PRIVATE "${SDL2}")
target_link_libraries(res-racer LINK_PRIVATE m)
target_link_libraries(res-racer LINK_PRIVATE "${GLEW}")
target_link_libraries(res-racer LINK_PRIVATE "${GL}")

#copy engine shaders
file(COPY vendor/T3Vtech-3/shaders DESTINATION .) #the engine shaders need to be copied
#file(COPY assets DESTINATION .) #where are your assets?
file(COPY vendor/T3Vtech-3/settings DESTINATION .)
 #a directory for engine settings that needs to be copied
