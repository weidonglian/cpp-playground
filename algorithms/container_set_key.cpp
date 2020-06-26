#include "cpptest.hpp"
#include <array>
#include <iostream>
#include <random>
#include <set>

struct DeadlineTimer {
    int id_;
    double expired_time_;
    DeadlineTimer(int id, double expired_time)
        : id_(id), expired_time_(expired_time) {
    }
};

struct DeadlineTimerComparator {
    bool operator()(const DeadlineTimer *lhs, const DeadlineTimer *rhs) const {
        return lhs != rhs && lhs->id_ < rhs->id_;
    }
};

using DeadlineTimerSet = std::set<DeadlineTimer *, DeadlineTimerComparator>;

TEST_CASE('mutable_key', '[set]') {
    std::array<DeadlineTimer, 5> timers = {
        DeadlineTimer{0, 1.0}, DeadlineTimer{1, 2.0}, DeadlineTimer{2, 3.0},
        DeadlineTimer{4, 4.0}, DeadlineTimer{5, 5.0}};

    DeadlineTimerSet timer_set;

    for (auto &t : timers) {
        timer_set.insert(&t);
    }
    const auto nb_timers = timers.size();
    CHECK(nb_timers, timer_set.size());

    for (auto &t : timers) {
        timer_set.insert(&t);
        CHECK(nb_timers, timer_set.size());
    }

    std::random_device
        rd; // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-10010, 10000);

    for (auto &t : timers) {
        t.expired_time_ = dis(gen);
        timer_set.insert(&t);
        CHECK(nb_timers, timer_set.size());
    }

    int i = 1;
    for (auto &t : timers) {
        t.expired_time_ += dis(gen);
        timer_set.erase(&t);
        CHECK(nb_timers - i++, timer_set.size());
    }

    CHECK(0, timer_set.size());

    int j = 1;
    for (auto &t : timers) {
        t.expired_time_ += dis(gen);
        timer_set.insert(&t);
        CHECK(j++, timer_set.size());
    }

    for (auto &t : timers) {
        timer_set.erase(&t);
    }

    CHECK(0, timer_set.size());
}

TEST_CASE('mutable_key_large', '[set]') {
    std::vector<DeadlineTimer> timers;
    timers.reserve(1000);
    for (int i = 0; i < 1000; ++i) {
        timers.emplace_back(i, i);
    };

    DeadlineTimerSet timer_set;

    for (auto &t : timers) {
        timer_set.insert(&t);
    }
    const auto nb_timers = timers.size();
    CHECK(nb_timers, timer_set.size());

    for (auto &t : timers) {
        timer_set.insert(&t);
        CHECK(nb_timers, timer_set.size());
    }

    std::random_device
        rd; // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-10010, 10000);

    for (auto &t : timers) {
        t.expired_time_ = dis(gen);
        timer_set.insert(&t);
        CHECK(nb_timers, timer_set.size());
    }

    int i = 1;
    for (auto &t : timers) {
        t.expired_time_ += dis(gen);
        timer_set.erase(&t);
        CHECK(nb_timers - i++, timer_set.size());
    }

    CHECK(0, timer_set.size());

    int j = 1;
    for (auto &t : timers) {
        t.expired_time_ += dis(gen);
        timer_set.insert(&t);
        CHECK(j++, timer_set.size());
    }

    for (auto &t : timers) {
        timer_set.erase(&t);
    }

    CHECK(0, timer_set.size());
}
