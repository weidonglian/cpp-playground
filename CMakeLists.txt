cmake_minimum_required(VERSION 3.2)
project(cpp-playground)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/bin)

# Set the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Default compiler settings and c++ 17 is required.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# PIC option
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# PThread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# MSVS compiler settings
if (MSVC)
    add_definitions(/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /wd4251)
else (MSVC)
# FileSystem
#    cmake_policy(SET CMP0057 NEW)
#    find_package(Filesystem REQUIRED)
endif ()

# Enable test
enable_testing()

add_subdirectory(src/asio)
add_subdirectory(src/cpp)
add_subdirectory(src/algorithm)
