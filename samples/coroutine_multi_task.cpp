#include <iostream>
#include <thread>

#include "coro/coro.hpp"

void print_thread_id(std::string_view title) {
  // Get and print the current thread ID
  std::cout << "[" << title << "] thread iD: " << std::this_thread::get_id() << std::endl;
}

int main() {
  // Create a thread pool to execute all the tasks in parallel.
  coro::thread_pool tp{coro::thread_pool::options{.thread_count = 4}};

  print_thread_id("main1");
  auto make_task = [&tp](int n) -> coro::task<int> {
    // compute might be time-consuming, let us schedule it to the thread pool
    print_thread_id("compute before schedule");
    co_await tp.schedule();
    print_thread_id("compute after schedule");

    // simulate some time-consuming task
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    co_return n* n;
  };

  std::vector<coro::task<int>> tasks;
  for (int i = 0; i < 10; i++) {
    tasks.emplace_back(make_task(i));
  }

  print_thread_id("main2");
  auto results = coro::sync_wait(coro::when_all(std::move(tasks)));

  print_thread_id("main3");
  for (const auto& result : results) {
    std::cout << "Result:" << result.return_value() << std::endl;
  }

  std::cout << std::endl;
}
