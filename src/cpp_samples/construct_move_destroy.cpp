#include <iostream>
#include <vector>
#include "object_id.hpp"
#include <string>

using namespace std;
namespace cppplayground {
  
  struct ObjectA { // Preferred way
    explicit ObjectA(int id) : obj_id_(id) {

    }

  private:
    ObjectId obj_id_;
  };

  struct ObjectB { // Usually a bad practice, not recommended
    explicit ObjectB(int id) : obj_id_(id) {

    }
    // Move are implicitly disallowed by compiler
    ~ObjectB() {}

    // Copy are implicitly implemented by compiler
    // mark as '=delete' if you do not want them
  private:
    ObjectId obj_id_;
  };

  struct ObjectC { // Make sure move semantic is really you want. Caution!
    explicit ObjectC(int id) : obj_id_(id) {

    }

    ObjectC(ObjectC&&) = default;
    ObjectC& operator=(ObjectC&&) = default;
    ~ObjectC() = default;
    // Copy are implicitly disallowed by compiler
    // since you define the move ctor and assignment.
  private:
    ObjectId obj_id_;
  };

  struct ObjectD { // Non-trivial object, inheritance, polymorphic, dynamic objects.
    explicit ObjectD(int id) : obj_id_(id) {

    }
    // Move are implicitly disallowed by compiler due to 
    virtual ~ObjectD() = default;

  private:
    ObjectD(const ObjectD&) = delete;
    ObjectD& operator=(const ObjectD&) = delete;
    ObjectId obj_id_;
  };

  struct ObjectE { // Rule of five for Non-trivial, inheritance, polymorphic, dynamic objects.
    explicit ObjectE(int id) : obj_id_(id) {

    }
    // Move are implicitly disallowed by compiler due to 
    virtual ~ObjectE() = default;
    ObjectE& operator=(ObjectE&&) = default;
    ObjectE(ObjectE&&) = default;

  private:
    ObjectE(const ObjectE&) = delete;
    ObjectE& operator=(const ObjectE&) = delete;
    ObjectId obj_id_;
  };

  template <class TObject>
  void TestObject(const string& description) {
    cout << "\n\n\nStart testing: " << description << endl;
    cout << "============ Section 1 ==================" << endl;
    vector<TObject> objs;
    objs.reserve(10);
    objs.emplace_back(0); // Only actually create one object;
    objs.emplace_back(1); // Only actually create one object;
    objs.emplace_back(2); // Only actually create one object;
    objs.push_back(TObject(3)); // Create one and move one
    objs[2] = TObject(4);
    TObject tmp(5);
    // objs[1] = tmp; // Only Work for A, B.
    objs[1] = std::move(tmp); // We have to do std::move, otherwise C, E should not compile.
    objs.pop_back();
    cout << "============ Section 2 ==================" << endl;
  }
}

int main(int argc, char** argv) {
  using namespace cppplayground;
  // Rule of Zero, you should design and write your code to make use of the 
  // default behavior.
  TestObject<ObjectA>("Object A: RuleOfZero");

  // We should not provide any destructor. Note even if you use '=default', 
  // which only means the compiler helps you fill the default implementation, 
  // it is still the user-defined. This is usually a bad practice. 
  // 1. Redesign you code to wrap or manage your resources into a wrapper of 
  // resource library, e.g. wrap FILE* with: 
  // unique_ptr<FILE, decltype(&std::fclose)>. Then you do not need to cleanup
  // Resources in destructor. 
  // 2. If you use polymorphic feature of your objects, e.g. put your Base*
  // or Base& into a container, then you destroy objects from Base*. Then
  // you have to define a virtual destructor (better with '= default').  
  // Normally these objects are non-trivial, you should disallow move and copy.
  // By your design, in some cases you can life up this rule. Note since you
  // have defined your virtual destructor, then move operations are not disallowed
  // implicitly by the compiler. **Unless** you REALLY REALLY need move semantic 
  // or move operations are much performance-efficient than copy operation,
  // you should not explicitly implement the move operations(move constructor and assignment). 
  // Even if you need them, you'd better design your code to let the default
  // implementation ('=default') work automatically. 
  TestObject<ObjectB>("Object B: User-defined Destructor");
  TestObject<ObjectC>("Object C: User-defined Destructor and Move, No Copy.");

  // Not movable and not copyable, then you can not use std::vector, try to wrap with 
  // unique_ptr/shared_ptr if you want.
  // TestObject<ObjectD>("Object D: User-defined Destructor and No Move, No Copy.");
  TestObject<ObjectE>("Object E: User-defined Destructor and Move, No Copy.");
}