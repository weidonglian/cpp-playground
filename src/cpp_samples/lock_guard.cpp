#include <iostream>
#include <thread>
#include <mutex>
#include <string>

std::mutex mx;
int total = 0;

void print(const std::string& text) {
    std::cout << text << std::endl;
}

class LockGuard {
public:
    LockGuard(std::mutex& mutex) :
    mutex_(mutex) {
        print("Mutex Enter");
        mutex_.lock();
    }
    ~LockGuard() {
        mutex_.unlock();
        print("Mutex Leave");
    }

private:
    std::mutex& mutex_;
};

void f() {
    print("Enter F");
    for(int i = 0; i < 10; ++i) {
        print(std::to_string(i));
        total += i;        
    }
    {
        LockGuard lg(mx);
    }
    print("Leave F");
}

int main() {
    f();
    return 0;
}