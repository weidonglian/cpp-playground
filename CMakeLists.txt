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

# Use gtest
include(${PROJECT_SOURCE_DIR}/third_party/gtest/gtest.cmake)
set(SRC_GTEST_CASES_LIST
    ${GTEST_SRC}
    ${GTEST_HDR})

function(add_play APP_NAME APP_SRC_LIST)
    add_executable(${APP_NAME} ${APP_SRC_LIST})
    add_test(NAME test-${APP_NAME} COMMAND ${APP_NAME})
endfunction(add_play)

function(add_gtest_play TEST_SRC)
    list(APPEND SRC_GTEST_CASES_LIST ${TEST_SRC})
endfunction(add_gtest_play)

function(add_asio_play APP_NAME APP_SRC_LIST)
    add_executable(${APP_NAME} ${APP_SRC_LIST})
    target_include_directories(${APP_NAME} PUBLIC third_party/asio)
    target_compile_definitions(${APP_NAME} PUBLIC -DASIO_STANDALONE)
    add_test(NAME test-${APP_NAME} COMMAND ${APP_NAME})
endfunction(add_asio_play)

add_play(ctor_dtor_throws ctor_dtor_throws.cpp)
add_play(func_over_load_ride_hide func_over_load_ride_hide.cpp)
add_play(objects_alignment objects_alignment.cpp)
add_play(type_erasure type_erasure.cpp)
add_play(floating_point_number floating_point_number.cpp)
add_play(rule_three_five_zero rule_three_five_zero.cpp)
add_play(construct_move_destroy construct_move_destroy.cpp)
add_play(time_duration_clock time_duration_clock.cpp)
add_play(unsigned_int_wrap unsigned_int_wrap.cpp)
add_play(lock_guard lock_guard.cpp)
add_play(steady_system_clock steady_system_clock.cpp)
add_play(stringstream_thread_safe stringstream_thread_safe.cpp)
add_play(compare_less_set compare_less_set.cpp)

add_asio_play(asio_tcp_clients asio_tcp_clients.cpp)
add_asio_play(asio_http_client asio_http_client.cpp)

# Finalize to create a cpp-gtest
add_play(cpp-test ${SRC_GTEST_CASES_LIST})
add_test(NAME cpp-test COMMAND cpp-test)