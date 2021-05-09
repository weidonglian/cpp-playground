add_library(logger STATIC logger.hpp logger.cpp)
target_link_libraries(logger absl::str_format)
target_include_directories(logger PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)