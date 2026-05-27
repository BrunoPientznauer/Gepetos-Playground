cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" 
    CACHE STRING "Vcpkg toolchain file")

project(Gepetos-Playground VERSION 1.0)

add_executable(${CMAKE_PROJECT_NAME})


# Add dependencies
find_package(glfw3  CONFIG REQUIRED)
find_package(glad   CONFIG REQUIRED)
find_package(glm    CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Stb    REQUIRED)

# Link to the libs
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE 
    glfw
    glad::glad
    glm::glm
    assimp::assimp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC include)

#add resources/assets folders
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

#sources and headers
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${GAME_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${GAME_SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)