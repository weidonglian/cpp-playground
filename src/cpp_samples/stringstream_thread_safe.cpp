#include <sstream>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

constexpr int kRunTimes = 10;

struct syb_ffl {
  syb_ffl() : file(nullptr), func(nullptr), line(0), tag(nullptr) {}
  syb_ffl(const char *file_, const char *func_, int line_) : file(file_), func(func_), line(line_), tag(nullptr) {}
  syb_ffl(const char *file_, const char *func_, int line_, const char *tag_) : file(file_), func(func_), line(line_), tag(tag_) {}
  const char *file;
  const char *func;
  int line;
  const char *tag;

  std::string to_string() const {
    if (!func || !file || !line)
        return "";
    std::ostringstream str;
    if (tag)
        str << func << " " << file << ":" << line << " [" << tag << "]";
    else
        str << func << " " << file << ":" << line;
    return str.str();
  }
};

#define FFL { __FILE__, __FUNCTION__, __LINE__ }

int test_async() {
    using StringFuture = std::future<std::string>;
    using namespace std::chrono_literals;
    std::vector<StringFuture> futures;
    for (int i = 0; i < kRunTimes; i++) {
        futures.emplace_back(std::async(std::launch::async, [i](){
            std::ostringstream oss;
            oss << "TestAsync[" << i << "] with thread:" << std::this_thread::get_id() << " is Running and Printg\n";
            return oss.str();
        }));
    }

    size_t cnt = 0;
    for(auto& f : futures) {
        std::cout << f.get();
        cnt++;
    }

    bool succeeded = false;
    if (cnt == futures.size()) {
        std::cout << "We are running " << cnt << " times" << std::endl;
        succeeded = true;
    }
    return succeeded ? 0 : 1;
}

std::string print_function(const syb_ffl&& ffl) {
    return ffl.to_string();
}

void test_threads_worker(int i, std::vector<std::string>& results) {
    results[i] = "TestThread:" + std::to_string(i) + " is " + print_function(FFL) + "\n";
}

int test_threads() {
    using namespace std::chrono_literals;
    std::vector<std::thread> threads;
    std::vector<std::string> results(kRunTimes);
    for (int i = 0; i < kRunTimes; i++) {
        threads.emplace_back(std::thread(test_threads_worker, i, std::ref(results)));
    }

    size_t cnt = 0;
    for(auto& t : threads) {
        t.join();
        std::cout << results[cnt++];
    }

    bool succeeded = false;
    if (cnt == threads.size()) {
        std::cout << "We are running " << cnt << " times" << std::endl;
        succeeded = true;
    }
    return succeeded ? 0 : 1;
}

int main() {
    return test_async() + test_threads();
}