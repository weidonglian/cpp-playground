#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std::chrono_literals;
using namespace std::chrono;

std::vector<int> generate_random_number(size_t sz, int min, int max) {
  // Seed with a real random value, if available
  std::random_device r;
  // Choose a random mean between 1 and 6
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(min, max);

  std::vector<int> durations;
  durations.reserve(sz);
  int cnt = 0;
  while (cnt++ < sz)
    durations.push_back(uniform_dist(e1));
  return durations;
}

std::string time_to_utc_str(system_clock::time_point p) {
    char buffer[100];
    const auto time_t_p = system_clock::to_time_t(p);
    if (std::strftime(buffer, sizeof(buffer), "UTC:%c", std::gmtime(&time_t_p))) {
        return buffer;
    }
    return {};
}

const int SecondsPerMinute = 60;
const int SecondsPerHour = 3600;
const int SecondsPerDay = 86400;
const int DaysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is_leap_year(short year)
{
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400) == 0;
}

time_t mktime_utc(const std::tm &tm_utc) {
    time_t secs = 0;
    int year = tm_utc.tm_year + 1900;
    for (short y = 1970; y < year; ++y)
        secs += (is_leap_year(y)? 366: 365) * SecondsPerDay;
    for (short m = 1; m < tm_utc.tm_mon; ++m) {
        secs += DaysOfMonth[m - 1] * SecondsPerDay;
        if (m == 2 && is_leap_year(year)) secs += SecondsPerDay;
    }
    secs += (tm_utc.tm_mday - 1) * SecondsPerDay;
    secs += tm_utc.tm_hour * SecondsPerHour;
    secs += tm_utc.tm_min * SecondsPerMinute;
    secs += tm_utc.tm_sec;
    return secs;
}

system_clock::time_point utc_str_to_time(const std::string& t_str) {
    std::tm tm = {};
    std::stringstream ss(t_str);
    ss >> std::get_time(&tm, "UTC:%a %b %d %H:%M:%S %Y");
    return system_clock::from_time_t(mktime_utc(tm));
}

int main() {
    std::wcout << "User-preferred locale setting is " << std::locale("").name().c_str() << '\n';
    const auto now = system_clock::from_time_t(1578988616);
    const int k_count = 1479;
    const auto durations_updated_at = generate_random_number(k_count, -5000, 5000);
    const auto durations_played_at = generate_random_number(k_count, -4000, 4000);
    char mbstr[100] = {};
    for (int i = 0; i < k_count; ++i) {
        const auto updated_at = seconds(durations_updated_at[i]) + now;
        const auto played_at = seconds(durations_played_at[i]) + now;
        if (utc_str_to_time(time_to_utc_str(updated_at)) != updated_at) {
            std::cout << "utc_str_to_time and time_to_utc_str are not convertable at i:" << i;
        }
        if (utc_str_to_time(time_to_utc_str(played_at)) != played_at) {
            std::cout << "utc_str_to_time and time_to_utc_str are not convertable at i:" << i;
        }

        std::cout << time_to_utc_str(updated_at) << ", " << time_to_utc_str(played_at) << std::endl;
    }
    return 0;
}