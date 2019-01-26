#include <iostream>
#include "asio.hpp"


int main(int argc, char ** argv) {

    using namespace asio;
    io_context ctx;
    ip::tcp::resolver resolver(ctx);
    ip::tcp::resolver::query query("www.boost.org", "https");
    ip::tcp::resolver::iterator iter = resolver.resolve(query);
    ip::tcp::resolver::iterator end; // End marker.
    
    while (iter != end) {
        ip::tcp::endpoint endpoint = *iter++;
        std::cout << endpoint << std::endl;
    }

    return 0;
}