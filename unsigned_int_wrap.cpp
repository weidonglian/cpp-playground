#include <iostream>


int main() {
    using namespace std;
    int64_t big_int64 = std::numeric_limits<int32_t>::max() + 400;
    uint32_t big_int64_mod = static_cast<uint32_t>(big_int64);
    cout << big_int64_mod << endl;
    return 0;
}