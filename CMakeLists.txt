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

# Enable test
enable_testing()

function(add_play_case APP_NAME APP_SRC_LIST)
    add_executable(${APP_NAME} ${APP_SRC_LIST})
    add_test(NAME test-${APP_NAME}
             COMMAND ${APP_NAME})
endfunction(add_play_case)

add_play_case(ctor_dtor_throws ctor_dtor_throws.cpp)
add_play_case(func_over_load_ride_hide func_over_load_ride_hide.cpp)
add_play_case(objects_alignment objects_alignment.cpp)
add_play_case(type_erasure type_erasure.cpp)
add_play_case(floating_point_number floating_point_number.cpp)
add_play_case(rule_three_five_zero rule_three_five_zero.cpp)
add_play_case(construct_move_destroy construct_move_destroy.cpp)
add_play_case(time_duration_clock time_duration_clock.cpp)
add_play_case(unsigned_int_wrap unsigned_int_wrap.cpp)
add_play_case(lock_guard lock_guard.cpp)
