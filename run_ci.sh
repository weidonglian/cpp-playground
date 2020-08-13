export CTEST_OUTPUT_ON_FAILURE=1
mkdir -p build && cd build && cmake .. && make -j4 && ctest