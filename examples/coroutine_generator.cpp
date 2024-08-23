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
    for (int i : fibonacci(10)) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

