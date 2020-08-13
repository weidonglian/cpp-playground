add_library(asio INTERFACE)
target_include_directories(asio
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)
target_compile_definitions(asio INTERFACE -DASIO_STANDALONE -DASIO_HAS_STD_THREAD)

