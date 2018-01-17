#include <iostream>
#include <algorithm>
#include <memory>
#include <utility>

class Foo
{
public:
  Foo() = default;
  Foo(Foo const &) = delete;
};

class A {
public:
  int width;
  int height;
};

A create() {
  A a;
  return a;
}

int main(int argc_, char **argv_) {
  A a = create();
  a.width = 10;
  a.height = 20;
  std::cout << a.width << ", " << a.height << std::endl;
  
  A b(std::move(a));

  Foo f;
  Foo g(std::move(f)); // compilation fails here

  return 0;
}



