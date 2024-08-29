#include <mutex>
#include <thread>
#include <unordered_map>

std::size_t get_thread_id() noexcept {
  static std::size_t thread_idx = 0;
  static std::mutex thread_mutex;
  static std::unordered_map<std::thread::id, std::size_t> thread_ids;

  std::lock_guard<std::mutex> lock(thread_mutex);
  std::thread::id id = std::this_thread::get_id();
  auto iter = thread_ids.find(id);
  if (iter == thread_ids.end()) {
    iter = thread_ids.insert(std::pair<std::thread::id, std::size_t>(id, thread_idx++)).first;
  }
  return iter->second;
}