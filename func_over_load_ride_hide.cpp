#include <iostream>

using namespace std;

template<class T>
class Complex {
public:
    Complex(double real_, double image_ = 0) {
        cout << "Ctor Complex:" << real_ << endl;
    }
};

class Base {
public:
    virtual void f(int) {
        cout << "Base::f(int)" << endl;
    }

    virtual void f(double) {
        cout << "Base::f(double)" << endl;
    }

    virtual void g(int i = 10) {
        cout << "Base::g(int):" << i << endl;
    }
};

class Derived : public Base {
public:
    void f(Complex<double>) { // this will hide all the f function in base
        cout << "Derived::f(complex)" << endl;
    }

    // using Base::f; // this make a big difference

    void g(int i = 20) override {
        cout << "Derived::g(int):" << i << endl;
    }
};

int main() {
    Base b;
    Derived d;
    Base *pb = new Derived();

    b.f(1.0);
    d.f(1.0);
    d.f(1); // hide base f(int), will call the Derived::f(double)
    pb->f(1.0);
    b.g();
    d.g();
    pb->g(); // default parameters will pick from current scope, i.e. pb (Base*), but will call virtual function.
    delete pb; // operator delete will deallocate the wrong object size. Expect memory corruption.
}
