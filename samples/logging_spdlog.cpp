#include "spdlog/spdlog.h"
#include "thread_id.hpp"

int main(int, char**) {
  // this format works
  spdlog::info("main thread id: {}", get_thread_id());
  // this does not work, since only fmt compatible is supported
  spdlog::info("Hello, %s with %d!", "World", 42);
  return 0;
}