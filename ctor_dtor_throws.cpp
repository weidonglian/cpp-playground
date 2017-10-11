#include <iostream>
#include <algorithm>
#include <memory>

int A_ID = 1;
int B_ID = 1;

class A {
public:
    A() : c_id(A_ID++) {
        if (c_id == 3) {
            throw std::runtime_error("Failed to construct object A");
        }
        std::cout << "Construct Object A " << c_id << std::endl;
    }

    ~A() {
        std::cout << "Deconstruct Object A " << c_id << std::endl;
    }

    int getId() const {
        return c_id;
    }

private:
    const int c_id;
};

class B {
public:
    B() : c_id(B_ID++) {
        std::cout << "Construct Object B " << c_id << std::endl;
    }

    ~B() {
        std::cout << "Deconstruct Object B " << c_id << std::endl;
        if (c_id == 3) {
            throw std::runtime_error("Failed to deconstruct object B");
        }
    }

    int getId() const {
        return c_id;
    }

private:
    const int c_id;
};

int main(int argc_, char **argv_) {
    // Exception safe and exception neutral.
    std::cout << "Testing the exception safety when throwing exception from a constructor and you can catch it. No leak"
              << std::endl;
    try {
        /* Quoting the C++03 standard
         * §5.3.4/8:
         * A new-expression obtains storage for the object by calling an allocation function. If the new-expression
         * terminates by throwing an exception, it may release storage by calling a deallocation function. If the
         * allocated type is a non-array type, the allocation function’s name is operator new and the deallocation
         * function’s name is operator delete. If the allocated type is an array type, the allocation function’s name
         *  is operator new[] and the deallocation function’s name is operator delete[].
         * §5.3.4/17:
         * If any part of the object initialization described above terminates by throwing an exception and a suitable
         * deallocation function can be found, the deallocation function is called to free the memory in which the object
         * was being constructed, after which the exception continues to propagate in the context of the new-expression. */
        auto p = new A[5]; // <===> void* vp = operator new[](sizeof(A)*5); A* p = (A*) vp; for (int i = 0; i < 5; i++) new(p+i) A;
        std::for_each(p, p + 5, [](const A &a) {
            std::cout << "A with Id:" << a.getId() << std::endl;
        });
        delete[] p;
    } catch (const std::exception &ex) {
        std::cout << "Caught exception:" << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Caught Unknown exception" << std::endl;
    }


    std::cout << "\nTesting the evil of throwing exception from a deconstructor and you can not catch it. Leak."
              << std::endl;
    try {
        auto p = new B[5];
        std::for_each(p, p + 5, [](const B &a) {
            std::cout << "B with Id:" << a.getId() << std::endl;
        });
        delete[] p;
    } catch (const std::exception &ex) {
        std::cout << "Caught exception:" << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Caught Unknown exception" << std::endl;
    }

    std::cout << "Exit main function" << std::endl;

    // Change above code with std::shared_ptr to see if the resource is leak.
    return 0;
}


