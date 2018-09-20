#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;
    using namespace std::chrono;
    const auto s = 200ms;
    const auto t = 500ms;
    const auto d_st = s - t;
    const auto d_ts = t - s;
    const seconds d_ts_sec = duration_cast<seconds>(d_ts);
    const microseconds d_ts_microsec = d_ts; // no need to duration_cast anymore

    std::cout << "d_st=" << d_st.count() << std::endl; // Negative
    std::cout << "d_ts=" << d_ts.count() << std::endl;
    std::cout << "d_ts_sec=" << d_ts_sec.count() << std::endl;

    const auto ss = steady_clock::now();    
    const auto tt = steady_clock::now();
    const seconds d_tt_ss_seconds = duration_cast<seconds>(tt-ss); // duration_cast is madatory
    const duration<double> double_seconds = tt-ss; // No need to duration_cast
    return 0;
}