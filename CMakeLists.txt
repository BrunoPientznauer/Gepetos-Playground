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
add_custom_target(resources ALL 
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${PROJECT_SOURCE_DIR}/resources
                  ${PROJECT_BINARY_DIR}/resources
                  COMMENT "Copying resources into binary directory" )  

add_custom_target(assets ALL 
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${PROJECT_SOURCE_DIR}/assets
                  ${PROJECT_BINARY_DIR}/assets
                  COMMENT "Copying assets into binary directory" )  

add_dependencies(${CMAKE_PROJECT_NAME} resources)
add_dependencies(${CMAKE_PROJECT_NAME} assets)

 
#sources and headers
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${GAME_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${GAME_SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)