cmake_minimum_required(VERSION 3.15)
project(myproject CXX)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

include_directories(src external/AMGCL)

file(GLOB SOURCES "src/*.cpp")
file(GLOB CFDSOURCES "src/CFD/*.cpp")
file(GLOB CONTROLSSOURCES "src/Controls/*.cpp")
file(GLOB GFXSOURCES "src/GFX/*.cpp")
file(GLOB PHYSICSSOURCES "src/Physics/*.cpp")
add_executable(game ${SOURCES} ${CFDSOURCES} ${CONTROLSSOURCES} ${GFXSOURCES} ${PHYSICSSOURCES})


find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIRS})
target_link_libraries(game PRIVATE ${SDL_LIBRARIES})


