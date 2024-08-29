function(add_sample)
  cmake_parse_arguments(EXAM
    ""
    "NAME"
    "HDRS;SRCS;DEPS;DEFS"
    ${ARGN}
  )

  if(OpenMP_CXX_FOUND)
    set(LINK_LIB_OPENMP OpenMP::OpenMP_CXX)
  endif()

  add_executable(${EXAM_NAME} ${EXAM_SRCS} ${EXAM_HDRS})
  target_link_libraries(${EXAM_NAME} Threads::Threads ${EXAM_DEPS} ${LINK_LIB_OPENMP})
  target_compile_definitions(${EXAM_NAME} PUBLIC ${EXAM_DEFS})

  INSTALL(TARGETS ${EXAM_NAME} RUNTIME DESTINATION .)
  add_test(NAME test-${EXAM_NAME} COMMAND ${EXAM_NAME})
endfunction()

# c++ types and semantic
add_sample(NAME type_erasure SRCS type_erasure.cpp)
add_sample(NAME objects_alignment SRCS objects_alignment.cpp)
add_sample(NAME func_over_load_ride_hide SRCS func_over_load_ride_hide.cpp)
add_sample(NAME floating_point_number SRCS floating_point_number.cpp)
add_sample(NAME unsigned_int_wrap SRCS unsigned_int_wrap.cpp)
add_sample(NAME ctor_dtor_throws SRCS ctor_dtor_throws.cpp)
add_sample(NAME rule_three_five_zero SRCS rule_three_five_zero.cpp)
add_sample(NAME construct_move_destroy SRCS construct_move_destroy.cpp)

# c++ libraries
add_sample(NAME time_duration_clock SRCS time_duration_clock.cpp)
add_sample(NAME steady_system_clock SRCS steady_system_clock.cpp)
add_sample(NAME lock_guard SRCS lock_guard.cpp)
add_sample(NAME stringstream_thread_safe SRCS stringstream_thread_safe.cpp)
add_sample(NAME time_generation SRCS time_generation.cpp)
add_sample(NAME file_system SRCS file_system.cpp)

# logging libraries
add_sample(NAME logging_spdlog SRCS logging_spdlog.cpp DEPS spdlog)

# asio
add_sample(NAME asio_tcp_clients SRCS asio_tcp_clients.cpp DEPS asio)
add_sample(NAME asio_http_client SRCS asio_http_client.cpp DEPS asio)

# continuable
add_sample(NAME continuable_hello_world SRCS continuable_hello_world.cpp DEPS continuable)
add_sample(NAME continuable_asio SRCS continuable_asio.cpp DEPS spdlog continuable asio)

# c++ 20/23 goroutine and generator
add_sample(NAME coroutine_generator SRCS coroutine_generator.cpp DEPS libcoro)
add_sample(NAME coroutine_task SRCS coroutine_task.cpp DEPS libcoro)
add_sample(NAME coroutine_multi_task SRCS coroutine_multi_task.cpp DEPS libcoro)

# boost
add_sample(NAME fiber_shared_work SRCS fiber_shared_work.cpp DEPS Boost::boost Boost::fiber)

# parallelism
add_sample(NAME openmp_vs_std SRCS openmp_vs_std.cpp)
