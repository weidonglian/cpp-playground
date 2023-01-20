# cpp-playground ![cpp-playground](https://github.com/weidonglian/cpp-playground/workflows/cpp-playground/badge.svg)

Cpp samples for testing and learning C++ 11/14/17/20

## LLVM Clang Linux/WSL

install llvm version 15

```bash
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 15
sudo apt install libomp-15-dev // for openmp
```

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

Standalone `asio` and `continuable` libraries are the best libraries to handle the async programming. Both `asio` and `continuable` still use the
pattern of `callback` and `future-then` pattern respectively. The drawback is that if a function requires `callback`/`future-then`/`coroutine` then
the caller function also needs to provide a `callback/then/coroutine`, personally I do not really like this requirement. It behaves like a `virus`.
We need to change the whole app that might cross many layers of the whole application. In order to mutigate this, we still would like to `block`
the caller to wait for the async results, e.g. `future.get()`, however it will block the caller's thread. Threads are expensive resources, thus
this solution is not scalable. How to solve this? The boost::fiber to rescue. `fiber` is user-land thread and thus it is cheaper to block, e.g.
fiber's `yeild` which will let the fiber scheduler to run other ready fibers, there is no os thread context switch and won't block the os thread.

The drawback of using `boost` is that your application will have to compile the boost on different platforms which are not portable. Boost does not
provide a way of compile `boost` with `cmake`. We should try to avoid using boost library at the first place. There is no other alternative similar
to `boost::fiber` that shares the same quality. `boost::fiber` also includes `bounded channel` and `unbounded channel` as `channels` in `golang` which
is really an elegant way when writing a pipeline with different stages.

Now I solve how to use boost fiber in your project by inventing your own cmakelists.txt to compile the boost fiber and easily reference it in your app,
see `fiber_shared_work.cpp` for example.

* continuable example in `continuable_asio.cpp` if you want to go with `continuable`.

* fiber example in `fiber_shared_work.cpp`.
