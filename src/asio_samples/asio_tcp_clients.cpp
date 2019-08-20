#include <iostream>
#include "asio.hpp"


int main(int argc, char ** argv) {

    using namespace asio;
    io_context ctx;
    ip::tcp::resolver resolver(ctx);
    ip::tcp::resolver::query query("www.boost.org", "https");

    // End points    
    {
        ip::tcp::resolver::iterator iter = resolver.resolve(query);
        ip::tcp::resolver::iterator end; // End marker.
        
        while (iter != end) {
            ip::tcp::endpoint endpoint = *iter++;
            std::cout << endpoint << std::endl;
        }
    }

    ip::tcp::socket sokt(ctx);
    async_connect(sokt, resolver.resolve(query), [](const error_code& er, const ip::tcp::endpoint& endpoint) {
        if (!er) {

        } else {
            std::cout << "async_connect error:" << er.message() << std::endl;
        }
    });
    return 0;
}