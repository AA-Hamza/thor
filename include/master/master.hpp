#pragma once

#include "worker/worker.hpp"
#include <asio.hpp>
#include <thread>
#include <vector>

namespace http
{
namespace server
{

// The master thread that accepts all incoming requests
class Master
{
  public:
    Master(const Master &) = delete;
    Master &operator=(const Master &) = delete;

    explicit Master(const std::string &address, const std::string &port, const std::string &doc_root,
                    const std::size_t num_of_wokers = 1);

    void run();

  private:
    void accept(void);
    void await_stop(void);
    void init_threads(void);
    // std::vector<Worker> m_workers;
    // std::vector<asio::thread> m_workers;
    Worker **m_workers;

    std::size_t m_num_of_workers;

    asio::io_context m_io_context;
    // Used to register signals for process
    asio::signal_set m_signals;
    // Incoming requests listener
    asio::ip::tcp::acceptor m_acceptor;

    RequestHandler m_request_handler;
};
} // namespace server
} // namespace http
