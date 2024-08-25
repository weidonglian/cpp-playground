#include <iostream>

#include "coro/generator.hpp"

coro::generator<int> fibonacci(int n) {
  int a = 0, b = 1;
  while (n-- > 0) {
    co_yield a;
    auto next = a + b;
    a = b;
    b = next;
  }
}

int main() {
  // simple facts:
  // co_yield is used to return a value from a coroutine, and it pauses the
  // execution of the coroutine util the next value is requested.
  // There is no waiting for any other async task like coro::task.

  // use it with a range-for loop
  std::cout << "Fibonacci sequence 1: ";
  for (auto i : fibonacci(10)) {
    std::cout << i << ' ';
  }

  // use with iterator
  std::cout << "\nFibonacci sequence 2: ";
  auto gen_fib = fibonacci(6);
  auto it = gen_fib.begin();
  while (it != gen_fib.end()) {
    std::cout << *it << ' ';
    ++it;
  }

  std::cout << std::endl;
}
