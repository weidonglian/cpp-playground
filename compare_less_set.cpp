#include <iostream>
#include <set>
#include <array>
#include <random>


struct DeadlineTimer {
  int id_;
  double expired_time_;
  DeadlineTimer(int id, double expired_time) :
    id_(id),
    expired_time_(expired_time) {
    std::cout << "Ctor: " << id_ << std::endl;
  }

  ~DeadlineTimer() {
    std::cout << "Dtor: " << id_ << std::endl;
  }
};

struct DeadlineTimerComparator {
  bool operator()(const DeadlineTimer* lhs, const DeadlineTimer* rhs) const {
    return lhs != rhs && lhs->id_ < rhs->id_;
  }
};

using DeadlineTimerSet = std::set<DeadlineTimer*, DeadlineTimerComparator>;

int main() {
  std::array<DeadlineTimer, 5> timers = {
      DeadlineTimer{0, 1.0},
      DeadlineTimer{1, 2.0},
      DeadlineTimer{2, 3.0},
      DeadlineTimer{4, 4.0},
      DeadlineTimer{5, 5.0}
  };

  DeadlineTimerSet timer_set;

  for (auto& t : timers) {
    timer_set.insert(&t);
    std::cout << "A: timer_set size is " << timer_set.size() << std::endl;
  }

  for (auto& t : timers) {
    timer_set.insert(&t);
    std::cout << "Insert1: timer_set size is " << timer_set.size() << std::endl;
  }

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(-10010, 10000);

  for (auto& t : timers) {
    t.expired_time_ = dis(gen);
    timer_set.insert(&t);
    std::cout << "Insert2: timer_set size is " << timer_set.size() << std::endl;
  }

  for (auto& t : timers) {
    t.expired_time_ += dis(gen);
    timer_set.erase(&t);
    std::cout << "Erase1: timer_set size is " << timer_set.size() << std::endl;
  }

  for (auto& t : timers) {
    t.expired_time_ += dis(gen);
    timer_set.insert(&t);
    std::cout << "Insert3: timer_set size is " << timer_set.size() << std::endl;
  }

  for (auto& t : timers) {
    timer_set.erase(&t);
    std::cout << "Erase2: timer_set size is " << timer_set.size() << std::endl;
  }

  return 0;
}
