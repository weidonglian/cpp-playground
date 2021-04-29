# cpp-playground ![cpp-playground](https://github.com/weidonglian/cpp-playground/workflows/cpp-playground/badge.svg)

Cpp samples for testing and learning C++ 11/14/17/20

## Useful Commands

```bash
mkdir build
cd build
cmake ..
make
make test
```

We use `catch2` testing framework in this repo, the corresponding executable is `test-algorithms`. run below command to check how to list and filter tests.

```bash
test-algorithms --help
```

On Windows GitBash

```bash
mkdir build
cd build
cmake ..
cmake --build . --parallel 4 --config Debug
cmake --build . --target RUN_TESTS --config Debug
```

## CI/CD with github action

In this repo, we use `github` action to run all the tests when we push changes to `master` branch.
The action will build and run tests using docker, see `Dockerfile` where we use alphine:latest.

## Learning notes

### Asynchrous programming

Standalone `asio` and `continuable` libraries are the best libraries to handle the async programming.
