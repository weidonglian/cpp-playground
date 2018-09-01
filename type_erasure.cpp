#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class A {
public:
  explicit A(int id) : id_(id) {
    cout << "Ctor:A with " << id << endl;
  }

  ~A() {
    cout << "Dtor:A with " << id_ << endl;
  }

private:
  int id_;
};

class B { 
public:
  explicit B(int id) : id_(id) {
    cout << "Ctor:B with " << id << endl;
  }

  ~B() {
    cout << "Dtor:B with " << id_ << endl;
  }

private:
  int id_;
};

int main() {
  // shared_ptr void trick is a simple and easy solution. You should consider std::variant and std::any first. 
  vector<shared_ptr<void>> sps;
  sps.push_back(make_shared<A>(1));
  sps.push_back(make_shared<A>(2));
  sps.push_back(make_shared<A>(3));
  sps.push_back(make_shared<B>(1));
  sps.push_back(make_shared<B>(2));
  sps.push_back(make_shared<B>(3));
  sps.push_back(make_shared<A>(4));
  return 0;
}
