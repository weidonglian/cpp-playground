add_library(asio INTERFACE)
target_include_directories(asio
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

if (WIN32)
  target_compile_definitions(asio INTERFACE -DASIO_HAS_STD_THREAD -DASIO_STANDALONE -DASIO_SEPARATE_COMPILATION -DASIO_NO_EXCEPTIONS -D_WIN32_WINNT=0x0600)
else(WIN32)
  target_compile_definitions(asio INTERFACE -DASIO_HAS_STD_THREAD -DASIO_STANDALONE -DASIO_SEPARATE_COMPILATION -DASIO_NO_EXCEPTIONS)
  target_compile_options(asio INTERFACE -Wno-shadow -Wno-implicit-fallthrough)
endif()

