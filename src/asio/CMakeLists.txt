project(asio-samples)

function(add_play_asio APP_NAME APP_SRC_LIST)
  add_executable(${APP_NAME} ${APP_SRC_LIST})
  target_link_libraries(${APP_NAME} Threads::Threads)
  target_include_directories(${APP_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/third_party/asio)
  target_compile_definitions(${APP_NAME} PUBLIC -DASIO_STANDALONE)
  add_test(NAME test-${APP_NAME} COMMAND ${APP_NAME})
endfunction(add_play_asio)

# Asio play
add_play_asio(asio_tcp_clients asio_tcp_clients.cpp)
add_play_asio(asio_http_client asio_http_client.cpp)
