cmake_minimum_required(VERSION 3.2)
project(cpp-playground)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${PROJECT_BINARY_DIR}/bin)

# Default compiler settings and c++ 14 is required.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PIC option
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# MSVS compiler settings
if (MSVC)
    add_definitions(/W3 -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS /wd4251)
endif ()

function(cpp_add_executable APP_NAME APP_SRC_LIST)
    add_executable(${APP_NAME} ${APP_SRC_LIST})
endfunction(cpp_add_executable)

cpp_add_executable(ctor_dtor_throws ctor_dtor_throws.cpp)
cpp_add_executable(func_over_load_ride_hide func_over_load_ride_hide.cpp)
cpp_add_executable(objects_alignment objects_alignment.cpp)
cpp_add_executable(type_erasure type_erasure.cpp)
cpp_add_executable(floating_point_number floating_point_number.cpp)
cpp_add_executable(rule_three_five_zero rule_three_five_zero.cpp)
cpp_add_executable(construct_move_destroy construct_move_destroy.cpp)
