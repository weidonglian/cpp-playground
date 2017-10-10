#include <iostream>
#include <algorithm>

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
    std::cout << "Testing the exception safety when throwing exception from a constructor and you can catch it."
              << std::endl;
    try {
        auto p = new A[5];
        std::for_each(p, p + 5, [](const A &a) {
            std::cout << "A with Id:" << a.getId() << std::endl;
        });
        delete[] p;
    } catch (const std::exception &ex) {
        std::cout << "Caught exception:" << ex.what() << std::endl;
    } catch (...) {
        std::cout << "Caught Unknown exception" << std::endl;
    }


    std::cout << "\nTesting the evil of throwing exception from a deconstructor and you can not catch it." << std::endl;
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


