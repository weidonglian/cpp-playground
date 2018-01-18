#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>

class Foo {
public:
  Foo() = default;
  Foo(Foo const&) = delete;
};

class A {
public:
  int width = 0;
  int height = 0;
};

A Create() {
  A a;
  return a;
}

int main(int argc, char** argv) {
  A a = Create();
  a.width = 10;
  a.height = 20;
  std::cout << a.width << ", " << a.height << std::endl;

  A b(std::move(a));

  Foo f;
  // Foo g(std::move(f)); // compilation fails here

  return 0;
}
