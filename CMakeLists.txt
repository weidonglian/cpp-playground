cmake_minimum_required(VERSION 3.5)
project(cpp-playground)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# enable CTest.  This will set BUILD_TESTING to ON unless otherwise specified
include(CTest)
# include the CPM package management
include(CPM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/distr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/distr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/distr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/distr)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/distr)

# Set the module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Default compiler settings and c++ 20 is required.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVS compiler settings
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # /wd4996  the compiler encountered a deprecated declaration.
  # /wd4002  too many actual parameters for macro 'identifier'
  # /wd4005  macro-redefinition
  # /wd4068  unknown pragma
  # /wd4244  conversion from 'type1' to 'type2'
  # /wd4267  conversion from 'size_t' to 'type2'
  # /wd4800  force value to bool 'true' or 'false' (performance warning)
  set( MSVC_FLAGS "/W3 /wd4996 /wd4002 /wd4005 /wd4068 /wd4800 /wd4251")
  set( CMAKE_CXX_FLAGS_RELEASE "${MSVC_FLAGS}")
  set( CMAKE_C_FLAGS_RELEASE "${MSVC_FLAGS}")
  set( CMAKE_CXX_FLAGS_DEBUG "${MSVC_FLAGS}")
  set( CMAKE_C_FLAGS_DEBUG "${MSVC_FLAGS}")
endif()

# PIC option
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# PThread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# OpenMP
find_package(OpenMP)

# MSVS compiler settings
if (MSVC)
  add_definitions(/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /wd4251)
endif ()

if(BUILD_TESTING)
  enable_testing()
endif()

add_subdirectory(third_party)
add_subdirectory(logger)
add_subdirectory(samples)
add_subdirectory(algorithms)