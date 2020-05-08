# cpp-playground ![cpp-playground](https://github.com/weidonglian/cpp-playground/workflows/cpp-playground/badge.svg)
Cpp samples for testing and learning C++ 14

# Useful command

```bash
mkdir build
cd build
cmake ..
make
make test
python ../third_party/gtest-parallel/gtest-parallel -r 100 -w 10 ./bin/cpptest.exe
```

On Windows GitBash

```bash
mkdir build
cd build
cmake ..
cmake --build . --parallel 4 --config Debug
cmake --build . --target RUN_TESTS --config Debug
python ../third_party/gtest-parallel/gtest-parallel -r 100 -w 10 ./bin/cpptest.exe
```
