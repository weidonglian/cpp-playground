#include <iostream>
#include <limits>

int main() {
    using namespace std;
    int64_t big_int64 = std::numeric_limits<int32_t>::max();
    cout << big_int64 << endl;
    big_int64 += 400;
    cout << big_int64 << endl;
    uint32_t big_int64_mod1 = static_cast<uint32_t>(big_int64%std::numeric_limits<int32_t>::max());
    cout << big_int64_mod1 << endl;
    
    uint32_t big_int64_mod2 = static_cast<uint32_t>(big_int64);
    cout << big_int64_mod2 << endl;
    
    return 0;
}