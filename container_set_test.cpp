#include <iostream>
#include <set>
#include <array>
#include <random>
#include "cpptest.hpp"

ADD_TEST_SUITE(ContainerSet);

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



TEST(ContainerSet, mutable_key) {
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
  }
  const auto nb_timers = timers.size();
  EXPECT_EQ(nb_timers, timer_set.size());

  for (auto& t : timers) {
    timer_set.insert(&t);
    EXPECT_EQ(nb_timers, timer_set.size());
  }

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> dis(-10010, 10000);

  for (auto& t : timers) {
    t.expired_time_ = dis(gen);
    timer_set.insert(&t);
    EXPECT_EQ(nb_timers, timer_set.size());
  }

  int i = 1;
  for (auto& t : timers) {
    t.expired_time_ += dis(gen);
    timer_set.erase(&t);
    EXPECT_EQ(nb_timers-i++, timer_set.size());
  }

  EXPECT_EQ(0, timer_set.size());

  int j = 1;
  for (auto& t : timers) {
    t.expired_time_ += dis(gen);
    timer_set.insert(&t);
    EXPECT_EQ(j++, timer_set.size());
  }

  for (auto& t : timers) {
    timer_set.erase(&t);
  }

  EXPECT_EQ(0, timer_set.size());
}