#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdio>

using namespace std;
using namespace chrono_literals;
using namespace chrono;

vector<int> generate_random_number(size_t sz, int min, int max) {
  // Seed with a real random value, if available
  random_device r;
  // Choose a random mean between 1 and 6
  default_random_engine e1(r());
  uniform_int_distribution<int> uniform_dist(min, max);

  vector<int> durations;
  durations.reserve(sz);
  int cnt = 0;
  while (cnt++ < sz)
    durations.push_back(uniform_dist(e1));
  return durations;
}

string time_to_utc_str(system_clock::time_point p) {
    char buffer[100];
    const auto time_t_p = system_clock::to_time_t(p);
    if (strftime(buffer, sizeof(buffer), "UTC:%c", gmtime(&time_t_p))) {
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

time_t mktime_utc(const tm &tm_utc) {
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

system_clock::time_point utc_str_to_time(const string& t_str) {
    tm tm = {};
    stringstream ss(t_str);
    ss >> get_time(&tm, "UTC:%a %b %d %H:%M:%S %Y");
    return system_clock::from_time_t(mktime_utc(tm));
}

struct track {
    string track_id;
    string artist_id;
    string album_id;
    system_clock::time_point updated_at;
    system_clock::time_point played_at;
};

using track_list = vector<track>;

struct track_db {
    string header;
    track_list tracks;
};

track_db read_tracks_from_file(const std::string& file_name) {
    track_db db{};
    db.tracks.reserve(10000);
    ifstream ifs(file_name);
    string line;
    char track_id[1024];
    char artist_id[1024];
    char album_id[1024];
    char updated_at[1024];
    char played_at[1024];
    int line_idx = 0;
    while(ifs.good()) {
        getline(ifs, line);
        if (line_idx == 0) {
            db.header = line;
        } else {
            sscanf(line.c_str(), " %[^,] , %[^,] , %[^,] , %[^,], %[^,] ",
                   track_id, artist_id, album_id, updated_at, played_at);
            // cout << track_id << ", " << artist_id << ", " << album_id << ", "
            // << updated_at << ", " << played_at << endl;
            db.tracks.emplace_back(track{track_id, artist_id, album_id,
                                      utc_str_to_time(updated_at),
                                      utc_str_to_time(played_at)});
        }
        ++line_idx;
    }
    return db;
}

int main() {
    wcout << "User-preferred locale setting is " << locale("").name().c_str() << '\n';

    const auto db = read_tracks_from_file("simple_timeline_tracks_raw.csv");

    //const auto now = system_clock::from_time_t(1578988616);
    const auto start_time = utc_str_to_time("UTC:Tue Jan 14 07:46:29 2020");
    const int k_count_tracks = (int)db.tracks.size();
    const auto durations_updated_at = generate_random_number(k_count_tracks, -5000, 5000);
    const auto durations_played_at = generate_random_number(k_count_tracks, -4000, 4000);
    const int k_count_searches = 100000;
    const auto search_time_at = generate_random_number(k_count_searches, 2000, 7000);

    ofstream ofs("simple_timeline_tracks.csv");
    ofs << db.header << endl;
    for (int i = 0; i < k_count_tracks; ++i) {
        const auto updated_at = seconds(durations_updated_at[i]) + start_time;
        const auto played_at = seconds(durations_played_at[i]) + start_time;
        if (utc_str_to_time(time_to_utc_str(updated_at)) != updated_at) {
            cout << "utc_str_to_time and time_to_utc_str are not convertable at i:" << i;
            return 1;
        }
        if (utc_str_to_time(time_to_utc_str(played_at)) != played_at) {
            cout << "utc_str_to_time and time_to_utc_str are not convertable at i:" << i;
            return 1;
        }
        ofs << db.tracks[i].track_id << ", " << db.tracks[i].artist_id << ", " << db.tracks[i].album_id << ", " << time_to_utc_str(updated_at) << ", " << time_to_utc_str(played_at) << endl;
    }

    ofstream ofs_search("searches.csv");
    for (int j = 0; j < k_count_searches; ++j) {
        const auto search_at = seconds(search_time_at[j]) + start_time;
        if (utc_str_to_time(time_to_utc_str(search_at)) != search_at) {
            cout << "utc_str_to_time and time_to_utc_str are not convertable at i:" << j;
            return 1;
        }
        ofs_search << time_to_utc_str(search_at) << endl;
    }

    return 0;
}