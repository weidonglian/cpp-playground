# Package/Project DIR.
set(GTEST_DIR ${CMAKE_CURRENT_LIST_DIR}/gtest)

message(STATUS "Using GTest - ${GTEST_DIR}")

# Include DIR List, Relative
set(GTEST_INC
${GTEST_DIR}/include
${GTEST_DIR}
)

# SRC File List, Relative
set(GTEST_SRC
${GTEST_DIR}/src/gtest_main.cc
${GTEST_DIR}/src/gtest.cc
${GTEST_DIR}/src/gtest-death-test.cc
${GTEST_DIR}/src/gtest-filepath.cc
${GTEST_DIR}/src/gtest-port.cc
${GTEST_DIR}/src/gtest-printers.cc
${GTEST_DIR}/src/gtest-test-part.cc
${GTEST_DIR}/src/gtest-typed-test.cc
)

# Generate HDR List.
foreach(DIR ${GTEST_INC})
file(GLOB_RECURSE GTEST_HDR ${GTEST_INC}/*.h)
file(GLOB_RECURSE GTEST_HDR ${GTEST_INC}/*.hpp)
endforeach()

add_definitions(-DCPP_PLAYGROUND_HAVE_GTEST)