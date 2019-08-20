#include <iostream>
#include <chrono>
#include <thread>

int64_t SystemClockTicks() {
    return std::chrono::system_clock::now().time_since_epoch().count();
}

int64_t SteadyClockTicks() {
    return std::chrono::steady_clock::now().time_since_epoch().count();
}
int main() {
    // Printing the system and steady ticks and you can change the system time at the same time to see what happened
    int64_t last_sys = 0;
    int64_t last_sty = 0;

    for (int i = 0; i < 1000; ++i) {
        auto sys_ticks = SystemClockTicks();
        auto sty_ticks = SteadyClockTicks();
        if (i > 0) {
            if (sys_ticks < last_sys) { // This will hit if you change back the system time, since the current computer's UTC time will change anyway.

                std::cout << "================ Warning: sys_ticks " << sys_ticks << " < last_sys " << last_sys << std::endl;
                break;
            }
            if (sty_ticks < last_sty) { // This will never hit.
                std::cout << "Warning: sty_ticks " << sty_ticks << " < last_sty " << last_sty << std::endl;
                break;
            }            
        }
        std::cout << "hhSystemClockTicks " << i << " = " << sys_ticks << std::endl;
        std::cout << "SteadyClockTicks " << i << " = " << sty_ticks << std::endl;
        // Do not do this, since windows' sleep for is implemented using system_clock, 
        // If you change the system back to one day, it will sleep for 1 day.
        // std::this_thread::sleep_for(std::chrono::seconds(1)); 
        last_sys = sys_ticks;
        last_sty = sty_ticks;
    }
    return 0;
}