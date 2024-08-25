#include <iostream>
#include <thread>

#include "coro/coro.hpp"

// Create a thread pool to execute all the tasks in parallel.
coro::thread_pool tp{coro::thread_pool::options{.thread_count = 4}};

void print_thread_id(std::string_view title)  {
  // Get and print the current thread ID
  std::cout << "[" << title << "] thread iD: " << std::this_thread::get_id() << std::endl;
}

coro::task<int> compute(int n) {
  // compute might be time-consuming, let us schedule it to the thread pool
  print_thread_id("compute before schedule");
  co_await tp.schedule();
  print_thread_id("compute after schedule");

  // simulate some time-consuming task
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  co_return n + n;
}

coro::task<int> get_data(int n) {
  print_thread_id("get_data");
  auto task_a = compute(n);
  auto result_a = co_await task_a;
  co_return result_a + result_a;
}

int main() {
  // simple facts:
  // 1. like in javascript, coroutines are functions are not allowed in the global scope.
  //    They must be defined inside another coroutine function via return type.
  // 2. co_await is used to wait for the result of another coroutine.
  // 3. co_return is used to return a value from a coroutine.
  // 4. sync_wait is used to wait for the result of a coroutine in a synchronous way, i.e. it will block
  //    the caller thread until the coroutine completed, it is normally used outside of a coroutine context.
  print_thread_id("main1");
  auto data = coro::sync_wait(get_data(20));
  std::cout << "Data:" << data << std::endl;

  print_thread_id("main2");
  data = coro::sync_wait(get_data(21));
  std::cout << "Data:" << data << std::endl;

  std::cout << std::endl;
}
