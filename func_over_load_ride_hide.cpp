#include <iostream>

using namespace std;

template <class T>
class Complex {
public:
  Complex(double real, double image = 0) {
    cout << "Ctor Complex:" << real << endl;
  }
};

class Base {
public:
  virtual void F(int) {
    cout << "Base::f(int)" << endl;
  }

  virtual void F(double) {
    cout << "Base::f(double)" << endl;
  }

  virtual void G(int i = 10) {
    cout << "Base::g(int):" << i << endl;
  }
};

class Derived : public Base {
public:
  void F(Complex<double>) const {
    // this will hide all the f function in base
    cout << "Derived::f(complex)" << endl;
  }

  // using Base::f; // this make a big difference

  void G(int i = 20) override {
    cout << "Derived::g(int):" << i << endl;
  }
};

int main() {
  Base b;
  Derived d;
  Base* pb = new Derived();

  b.F(1.0);
  d.F(1.0);
  d.F(1); // hide base f(int), will call the Derived::f(double)
  pb->F(1.0);
  b.G();
  d.G();
  pb->G(); // default parameters will pick from current scope, i.e. pb (Base*), but will call virtual function.
  delete pb; // operator delete will deallocate the wrong object size. Expect memory corruption.
}
