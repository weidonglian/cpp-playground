#include <iostream>

using namespace std;

class Y {
public:
  explicit Y(double val) : value_(val) {
    cout << "Construct A:" << val << endl;
  }

  ~Y() {
    cout << "Deconstruct A: " << value_ << endl;
  }

  double GetValue() const {
    return value_;
  }

private:
  double value_;

};


int main() {
  // Why Alignment?
  // Any memory that's allocated dynamically via new and malloc is guaranteed to be properly aligned for objects of any
  // type, but buffers that are not allocated dynamically have no such guarantee.
  char* buffer1 = new char[sizeof(Y)]; // Or malloc
  char buffer2[sizeof(Y)];
  aligned_storage_t<sizeof(Y), alignof(Y)> buffer3[1];

  // Align object Y into the allocated memory
  Y* y1 = new(buffer1) Y(10.0);
  Y* y2 = new(buffer2) Y(20.0);
  Y* y3 = new(buffer3) Y(30.0);

  cout << "Y1: " << y1->GetValue() << endl;
  cout << "Y2: " << y2->GetValue() << endl;
  cout << "Y3: " << y3->GetValue() << endl;

  y1->~Y(); // OK
  y3->~Y(); // OK
  y2->~Y(); // Problematic

  // It is encouraged to code in this way. You can use all kinds of allocators to avoid nuances.
  cout << "Exit:main" << endl;
}
