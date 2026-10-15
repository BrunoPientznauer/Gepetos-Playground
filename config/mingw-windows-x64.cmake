set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc-posix)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++-posix)

set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# Force vcpkg to use the MinGW triplet instead of x64-windows
set(VCPKG_TARGET_TRIPLET x64-mingw-static CACHE STRING "")

# Adjust search paths
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)