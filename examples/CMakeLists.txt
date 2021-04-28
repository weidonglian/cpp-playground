function(add_example)
  cmake_parse_arguments(EXAM
    ""
    "NAME"
    "HDRS;SRCS;DEPS"
    ${ARGN}
  )

  if(OpenMP_CXX_FOUND)
    set(LINK_LIB_OPENMP OpenMP::OpenMP_CXX)
  endif()

  add_executable(${EXAM_NAME} ${EXAM_SRCS} ${EXAM_HDRS})
  target_link_libraries(${EXAM_NAME} Threads::Threads ${EXAM_DEPS} ${LINK_LIB_OPENMP})

  INSTALL(TARGETS ${EXAM_NAME} RUNTIME DESTINATION .)
  add_test(NAME test-${EXAM_NAME} COMMAND ${EXAM_NAME})
endfunction()

# Normal play
add_example(NAME ctor_dtor_throws SRCS ctor_dtor_throws.cpp)
add_example(NAME func_over_load_ride_hide SRCS func_over_load_ride_hide.cpp)
add_example(NAME objects_alignment SRCS objects_alignment.cpp)
add_example(NAME type_erasure SRCS type_erasure.cpp)
add_example(NAME floating_point_number SRCS floating_point_number.cpp)
add_example(NAME rule_three_five_zero SRCS rule_three_five_zero.cpp)
add_example(NAME construct_move_destroy SRCS construct_move_destroy.cpp)
add_example(NAME time_duration_clock SRCS time_duration_clock.cpp)
add_example(NAME unsigned_int_wrap SRCS unsigned_int_wrap.cpp)
add_example(NAME lock_guard SRCS lock_guard.cpp)
add_example(NAME steady_system_clock SRCS steady_system_clock.cpp)
add_example(NAME stringstream_thread_safe SRCS stringstream_thread_safe.cpp)
add_example(NAME time_generation SRCS time_generation.cpp)
add_example(NAME file_system SRCS file_system.cpp)
add_example(NAME asio_tcp_clients SRCS asio_tcp_clients.cpp DEPS asio)
add_example(NAME asio_http_client SRCS asio_http_client.cpp DEPS asio)
add_example(NAME continuable_hello_world SRCS continuable_hello_world DEPS continuable)

IF (WIN32)
  # GCC compiler supports c++ 17 but requires install tbb and linking to tbb yourself
  # this is not portable and we are not going to use `par` on Linux.
  add_example(NAME openmp_vs_std SRCS openmp_vs_std.cpp)
ENDIF()