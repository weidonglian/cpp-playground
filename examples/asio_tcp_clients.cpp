#include <iostream>

#include "asio.hpp"

int main(int argc, char** argv) {

  using namespace asio;
  io_context ctx;
  ip::tcp::resolver resolver(ctx);
  ip::tcp::resolver::results_type results = resolver.resolve("www.boost.org", "https");

  // End points
  for (const auto& endpoint : results) {
    std::cout << endpoint.endpoint() << std::endl;
  }

  ip::tcp::socket sokt(ctx);
  async_connect(sokt, results, [](const error_code& er, const ip::tcp::endpoint& endpoint) {
    if (!er) {
      std::cout << "Connected to: " << endpoint << std::endl;
    } else {
      std::cout << "async_connect error: " << er.message() << std::endl;
    }
  });

  // Run the io_context to handle the asynchronous operations
  ctx.run();

  return 0;
}
