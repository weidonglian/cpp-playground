add_library(simple_svg INTERFACE)
target_include_directories(simple_svg
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)
